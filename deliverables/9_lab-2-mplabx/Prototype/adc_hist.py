from cProfile import label
import tkinter as tk
import serial
import serial.tools.list_ports_windows as list_ports
import re
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import seaborn as sns
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
import threading

incoming_data = []

def read_adc_thread() -> None:
    # print('Available Ports:', ''.join([x.name for x in list_ports.comports()]))
    uart = serial.Serial(port='COM6', baudrate=115200, timeout=0.1)
    while True:
        if uart.in_waiting:
            uart_incoming_data = uart.readline().decode('utf-8').replace('\n', '')
            uart_match = re.findall(r'chan \d{1} (\d+)', uart_incoming_data)
            if uart_match is not None:
                channel_reads = [int(x) for x in uart_match]
                incoming_data.append(channel_reads[0])


def gui_thread() -> None:
    root = tk.Tk()
    root.title('ADC Live Plotter')
    root.option_add('*tearOff', tk.FALSE)
    root.geometry('500x500')

    menubar = tk.Menu(root)
    options_menu = tk.Menu(menubar)
    port_options = tk.Menu(options_menu)
    for port in [x.name for x in list_ports.comports()]:
        port_options.add_checkbutton(label=port, command=lambda: print(port))
    options_menu.add_cascade(label='Select Port', menu=port_options)
    rate_options = tk.Menu(options_menu)
    rate_options.add_cascade(label='9600', command=lambda: print(9600))
    rate_options.add_cascade(label='115200', command=lambda: print(115200))
    options_menu.add_cascade(label='Select Baudrate', menu=rate_options)
    menubar.add_cascade(menu=options_menu, label='Options')
    root.config(menu=menubar)

    app = tk.Frame(root)
    chart = Figure(figsize=(5,5), dpi=100)
    axes = chart.add_subplot()
    def animate(frame_count, data):
        axes.clear()
        sns.histplot(data=data, kde=False, ax=axes, color='gray')
    canvas = FigureCanvasTkAgg(figure=chart, master=root)
    canvas.get_tk_widget().pack()
    hold = animation.FuncAnimation(chart, func=animate, fargs=[incoming_data], frames=1, interval=100)
    
    app.pack()
    root.mainloop()


if __name__ == "__main__":
    adc_thread = threading.Thread(target=read_adc_thread, daemon=True)
    adc_thread.start()
    gui_thread()