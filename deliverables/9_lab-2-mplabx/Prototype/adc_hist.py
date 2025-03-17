import itertools
from multiprocessing import Value
from operator import mul
import stat
import tkinter as tk
import serial
import serial.tools.list_ports_windows as list_ports
import re
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import seaborn as sns
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import threading
import logging

APP_NAME = 'ADC Live Plotter'
logger = logging.getLogger(APP_NAME)
logging.basicConfig(
    filename='adc.log', 
    level=logging.INFO, 
    format='[%(asctime)s - %(name)s]: [%(levelname)s] %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)


class UARTDataReader:
    def __init__(self):
        self._pattern = r'chan \d{1} (\d+)'
        self._baudrate = None
        self._port = None
        self.channel_1 = []
        self.channel_2 = []
        self._uart_thread = None
        self._is_connected = False

    def set_port(self, port):
        if not self._is_connected:
            self._port = port
            return True
        return False

    def set_baudrate(self, rate):
        if not self._is_connected:
            self._baudrate = rate
            return True
        return False

    def set_pattern(self, pattern):
        if not self._is_connected:
            self._pattern = pattern
            return True
        return False

    def read_adc_thread(self):
        try:
            logger.info(f'Attempting connection on {self._port} with a {self._baudrate} rate.')
            if self._pattern is None or self._baudrate is None or self._port is None:
                raise ValueError()
            with serial.Serial(port=self._port, baudrate=self._baudrate, timeout=0.1) as uart:
                self._is_connected = True
                while self._is_connected:
                    if uart.in_waiting:
                        uart_incoming_data = uart.readline().decode('utf-8').replace('\n', '')
                        uart_match = re.findall(self._pattern, uart_incoming_data)
                        if uart_match is not None:
                            channel_reads = [int(x) for x in uart_match[:2]]
                            logger.info(f'Received data: {channel_reads}')
                            if len(channel_reads) >= 2:
                                self.channel_1.append(channel_reads[0])
                                self.channel_2.append(channel_reads[1])
                            else:
                                logger.warning('Unable to parse channel readings, are you using the right baudrate?')
        except serial.SerialException as e:
            logger.error(f'Failed to open connection to {self._port}: {e}')
        except ValueError:
            logger.error('Failed to open serial connection: Did you set baudrate and port?')
        finally:
            logger.info('Exiting ADC data thread...')
            self._is_connected = False

    def start(self):
        self._uart_thread = threading.Thread(target=self.read_adc_thread, daemon=True)
        self._uart_thread.start()

    def is_connected(self):
        return self._is_connected

    def stop(self):
        self._is_connected = False

class ADCApplication:
    def __init__(self):
        self.uart_reader = UARTDataReader()
        self.root = tk.Tk()
        # configurable settings
        self._BAUDRATES = [9600, 115200]
        self._selected_port = None
        self._selected_rate = None
        self._init_gui()
        self._refresh_menus()
    
    def _refresh_menus(self):
        logger.info('Refreshing ports and options menus...')
        self.port_options.delete(0, self.port_options.index('end'))
        for port in [x.name for x in list_ports.comports()]:
            self.port_options.add_checkbutton(label=port, command=lambda port=port: self._set_port(port))
        self.rate_options.delete(0, self.rate_options.index('end'))
        for rate in self._BAUDRATES:
            self.rate_options.add_cascade(label=str(rate), command=lambda rate=rate: self._set_rate(rate))

    def _set_port(self, port):
        if self.uart_reader.set_port(port):
            logger.info(f'Set port: {port}')
            self.options_menu.entryconfig(0, label=f'Port: {port}')
        else:
            logger.warning('Cannot set port, please stop the live graphing first')

    def _set_rate(self, rate):
        if self.uart_reader.set_baudrate(rate):
            logger.info(f'Set baudrate: {rate}')
            self.options_menu.entryconfig(1, label=f'Baudrate: {rate}')
        else:
            logger.warning('Cannot set baudrate, please stop the live graphing first')

    def _init_gui(self):
        # Root config
        self.root.title(APP_NAME)
        self.root.option_add('*tearOff', tk.FALSE)
        # self.root.geometry('500x500')
        # Menubar setup
        self.menubar = tk.Menu(self.root)
        self.options_menu = tk.Menu(self.menubar)
        self.port_options = tk.Menu(self.options_menu)
        self.rate_options = tk.Menu(self.options_menu)
        self.options_menu.add_cascade(label='Port', menu=self.port_options)
        self.options_menu.add_cascade(label='Baudrate', menu=self.rate_options)
        self.options_menu.add_command(label='Refresh Ports', command=self._refresh_menus)
        self.menubar.add_cascade(menu=self.options_menu, label='Options')
        self.menubar.add_command(label='Start', command=self._run_uart)
        self.menubar.add_command(label='Stop', state='disabled', command=self._stop_uart)
        self.root.config(menu=self.menubar)
        # App frame setup
        app = tk.Frame(self.root)
        # TK Graph setup
        self.chart1 = Figure(figsize=(10,5), dpi=100)
        self.g1_axes = self.chart1.add_subplot()
        self.chart2 = Figure(figsize=(10,5), dpi=100)
        self.g2_axes = self.chart2.add_subplot()
        self.canvas1 = FigureCanvasTkAgg(figure=self.chart1, master=app)
        self.canvas2 = FigureCanvasTkAgg(figure=self.chart2, master=app)
        self.canvas1.get_tk_widget().pack()
        self.canvas2.get_tk_widget().pack()
        app.pack()

    def graph_1_animation_func(self, frame_index, data):
        self.g1_axes.clear()
        dataplot = sns.histplot(data=data, bins=100, kde=False, ax=self.g1_axes, color='gray')
        dataplot.set_xlabel('Reading')
        dataplot.set_ylabel('Count')
        dataplot.set_title('Channel 1')

    def graph_2_animation_func(self, frame_index, data):
        self.g2_axes.clear()
        dataplot = sns.histplot(data=data, bins=100, kde=False, ax=self.g2_axes, color='gray')
        dataplot.set_xlabel('Reading')
        dataplot.set_ylabel('Count')
        dataplot.set_title('Channel 2')

    def _run_uart(self):
        if not self.uart_reader.is_connected():
            self.uart_reader.start()
            self.menubar.entryconfig(1, state='disabled')
            self.menubar.entryconfig(2, state='normal')
            logger.info('Started UART process.')
        else:
            logger.error('Unable to start UART process, is process stopped or one or more settings unset?')

    def _stop_uart(self):
        if self.uart_reader.is_connected():
            self.uart_reader.stop()
            self.menubar.entryconfig(1, state='normal')
            self.menubar.entryconfig(2, state='disabled')
            logger.info('Stopped UART process.')
        else:
            logger.error('Unable to stop UART process, is process running?')

    def run(self):
        logger.info('Starting application...')
        self.graph_1_animation = animation.FuncAnimation(self.chart1, func=self.graph_1_animation_func, fargs=[self.uart_reader.channel_1], frames=1, blit=False, interval=1000)
        self.graph_2_animation = animation.FuncAnimation(self.chart2, func=self.graph_2_animation_func, fargs=[self.uart_reader.channel_2], frames=1, blit=False, interval=1000)
        self.root.mainloop()


if __name__ == "__main__":
    app = ADCApplication()
    app.run()
