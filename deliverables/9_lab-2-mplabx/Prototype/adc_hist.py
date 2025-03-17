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
            with serial.Serial(port=self._port, baudrate=self._baudrate, timeout=0.1) as uart:
                self._is_connected = True
                while self._is_connected:
                    if uart.in_waiting:
                        uart_incoming_data = uart.readline().decode('utf-8').replace('\n', '')
                        uart_match = re.findall(self._pattern, uart_incoming_data)
                        if uart_match is not None:
                            try:
                                channel_reads = [int(x) for x in uart_match[:2]]
                                logger.info(f'Received data: {channel_reads}')
                                if len(channel_reads) >= 2:
                                    self.channel_1.append(channel_reads[0])
                                    self.channel_2.append(channel_reads[1])
                                else:
                                    logger.warning('Unable to parse channel readings, are you using the right baudrate?')
                            except ValueError:
                                logger.warning('Failed to parse channel readings, is the pattern valid?')
        except serial.SerialException as e:
            logger.error(f'Failed to open connection to {self._port}: {e}')
        finally:
            logger.info('Exiting ADC data thread...')
            self._is_connected = False

    def start(self):
        if self._pattern is None or self._baudrate is None or self._port is None:
            raise ValueError()
        self._uart_thread = threading.Thread(target=self.read_adc_thread, daemon=True)
        self._uart_thread.start()

    def is_connected(self):
        return self._is_connected

    def stop(self):
        self._is_connected = False

class ADCApplication:
    def __init__(self):
        self.uart_reader = UARTDataReader()
        self.__root = tk.Tk()
        # configurable settings
        self._BAUDRATES = [9600, 115200]
        self._selected_port = None
        self._selected_rate = None
        self.__init_gui()
        self._refresh_menus()
    
    def _refresh_menus(self):
        logger.info('Refreshing ports and options menus...')
        self.__port_options.delete(0, self.__port_options.index('end'))
        if len(ports := [x.name for x in list_ports.comports()]):
            for port in ports:
                self.__port_options.add_checkbutton(label=port, command=lambda port=port: self.__set_port(port))
        else:
            self.__port_options.add_checkbutton(label='No Ports Connected', state='disabled')
        self.__rate_options.delete(0, self.__rate_options.index('end'))
        for rate in self._BAUDRATES:
            self.__rate_options.add_cascade(label=str(rate), command=lambda rate=rate: self.__set_rate(rate))

    def __set_port(self, port):
        if self.uart_reader.set_port(port):
            logger.info(f'Set port: {port}')
            self.__options_menu.entryconfig(0, label=f'Port: {port}')
        else:
            logger.warning('Cannot set port, please stop the live graphing first')

    def __set_rate(self, rate):
        if self.uart_reader.set_baudrate(rate):
            logger.info(f'Set baudrate: {rate}')
            self.__options_menu.entryconfig(1, label=f'Baudrate: {rate}')
        else:
            logger.warning('Cannot set baudrate, please stop the live graphing first')

    def __init_gui(self):
        # Root config
        self.__root.title(APP_NAME)
        self.__root.option_add('*tearOff', tk.FALSE)
        # Menubar setup
        self.__menubar = tk.Menu(self.__root)
        self.__options_menu = tk.Menu(self.__menubar)
        self.__port_options = tk.Menu(self.__options_menu)
        self.__rate_options = tk.Menu(self.__options_menu)
        self.__options_menu.add_cascade(label='Port', menu=self.__port_options)
        self.__options_menu.add_cascade(label='Baudrate', menu=self.__rate_options)
        self.__options_menu.add_command(label='Refresh Ports', command=self._refresh_menus)
        self.__options_menu.add_command(label='Set Pattern (Advanced)', command=self.__set_pattern)
        self.__menubar.add_cascade(menu=self.__options_menu, label='Options')
        self.__menubar.add_command(label='Start', command=self.__run_uart)
        self.__menubar.add_command(label='Stop', state='disabled', command=self.__stop_uart)
        self.__root.config(menu=self.__menubar)
        # App frame setup
        app = tk.Frame(self.__root)
        # TK Graph setup
        self.__chart1 = Figure(figsize=(10,5), dpi=100)
        self.__g1_axes = self.__chart1.add_subplot()
        self.__chart2 = Figure(figsize=(10,5), dpi=100)
        self.__g2_axes = self.__chart2.add_subplot()
        self.__canvas1 = FigureCanvasTkAgg(figure=self.__chart1, master=app)
        self.__canvas2 = FigureCanvasTkAgg(figure=self.__chart2, master=app)
        self.__canvas1.get_tk_widget().pack()
        self.__canvas2.get_tk_widget().pack()
        app.pack()

    def __graph_1_animation_func(self, frame_index, data):
        self.__g1_axes.clear()
        dataplot = sns.histplot(data=data, bins=100, kde=False, ax=self.__g1_axes, color='gray')
        dataplot.set_xlabel('Reading')
        dataplot.set_ylabel('Count')
        dataplot.set_title('Channel 1')

    def __graph_2_animation_func(self, frame_index, data):
        self.__g2_axes.clear()
        dataplot = sns.histplot(data=data, bins=100, kde=False, ax=self.__g2_axes, color='gray')
        dataplot.set_xlabel('Reading')
        dataplot.set_ylabel('Count')
        dataplot.set_title('Channel 2')

    def __set_pattern(self):
        def __pattern__on_submit():
            new_pattern = self.__pattern__store.get()
            if len(new_pattern) == 0:
                self.__pattern__message.set('Pattern cannot be empty.')
            elif new_pattern.count('(') != 1 or new_pattern.count(')') != 1:
                self.__pattern__message.set('Pattern must contain exactly one group.')
            else:
                self.uart_reader.set_pattern(rf'{new_pattern}')
                popup.destroy()
                
        popup = tk.Toplevel(self.__root)
        popup.title('Set Pattern (Advanced)')
        self.__pattern__message = tk.StringVar(value='Enter Python Regex, UART reader will attempt to group ALL occurrences.')
        self.__pattern__store = tk.StringVar(value=self.uart_reader._pattern)
        tk.Label(popup, textvariable=self.__pattern__message).grid(row=0, column=0, pady=(10,0), padx=10)
        tk.Entry(popup, text=self.__pattern__store).grid(row=1, column=0, pady=10)
        tk.Button(popup, text='Set Pattern', command=__pattern__on_submit).grid(row=2, column=0, pady=(0,10))

    def __run_uart(self):
        if not self.uart_reader.is_connected():
            try:
                self.uart_reader.start()
                self.__menubar.entryconfig(0, state='disabled')
                self.__menubar.entryconfig(1, state='disabled')
                self.__menubar.entryconfig(2, state='normal')
                logger.info('Started UART process.')
            except ValueError:
                logger.error('Cannot start UART process, please set port, baudrate, and pattern.')
        else:
            logger.error('Unable to start UART process, is process stopped or one or more settings unset?')

    def __stop_uart(self):
        if self.uart_reader.is_connected():
            self.uart_reader.stop()
            self.__menubar.entryconfig(0, state='normal')
            self.__menubar.entryconfig(1, state='normal')
            self.__menubar.entryconfig(2, state='disabled')
            logger.info('Stopped UART process.')
        else:
            logger.error('Unable to stop UART process, is process running?')

    def run(self):
        logger.info('Starting application...')
        self.__graph_1_animation = animation.FuncAnimation(self.__chart1, func=self.__graph_1_animation_func, fargs=[self.uart_reader.channel_1], frames=1, blit=False, interval=1000)
        self.__graph_2_animation = animation.FuncAnimation(self.__chart2, func=self.__graph_2_animation_func, fargs=[self.uart_reader.channel_2], frames=1, blit=False, interval=1000)
        self.__root.mainloop()


if __name__ == "__main__":
    app = ADCApplication()
    app.run()
