import tkinter as tk
from tkinter import ttk, font
import threading
import serial
import serial.tools.list_ports_linux as list_ports
# import serial.tools.list_ports_windows as list_ports

AVAILABLE_BAUD_RATES = [9600, 115200]

SELECTED_PORT = None
SELECTED_BAUD_RATE = None

def set_port(port):
    global SELECTED_PORT 
    SELECTED_PORT = port

def set_baudrate(rate):
    global SELECTED_BAUD_RATE
    SELECTED_BAUD_RATE = rate

def arduino_uart_thread():
    if SELECTED_PORT is None or SELECTED_BAUD_RATE is None:
        create_popup('Error', 'Both port and baud rate need to be set!')
        return
    try:
        print(f'Attempting connection on port {SELECTED_PORT} at {SELECTED_BAUD_RATE}...')
        uart = serial.Serial(port=SELECTED_PORT, baudrate=SELECTED_BAUD_RATE, timeout=0.1)
        while True:
            if uart.in_waiting:
                received_data = uart.readline().decode('utf-8').replace('\n', '')
                data = [int(x) for x in received_data.split(',')]
                print(f'Received: {data}')
                # update_temperature(data[0])
                # update_selected_room(data[0])
    except serial.SerialException:
        create_popup('Error', 'Could not connect to Arduino.\nEnsure that Arduino IDE is closed and\nthat the port name matches the port in device manager.')

def connect_to_ardunio():
    thread = threading.Thread(target=arduino_uart_thread, daemon=True)
    thread.start()

def list_comports():
    return [(x.name,x.device) for x in list_ports.comports()]


root = tk.Tk()
root.title('Introduction to Microcontrollers - Home Control System')

'''
Menus
'''
menu_bar = tk.Menu(root, tearoff=tk.FALSE)
options_menu = tk.Menu(menu_bar, tearoff=tk.FALSE)
ports_submenu = tk.Menu(options_menu, tearoff=tk.FALSE)
for port,device in list_comports():
    ports_submenu.add_checkbutton(label=f'{port} - {device}', command=lambda: set_port(port))
options_menu.add_cascade(label='Set Port', menu=ports_submenu)
baud_submenu = tk.Menu(options_menu, tearoff=tk.FALSE)
for rate in AVAILABLE_BAUD_RATES:
    baud_submenu.add_checkbutton(label=rate, command=lambda: set_baudrate(rate))
options_menu.add_cascade(label='Set Baud Rate', menu=baud_submenu)
options_menu.add_separator()
options_menu.add_command(label='How To Use', command=lambda: create_popup('How To Use', 'Set the baud rate and port, then connect to Arduino.\nThe program should automatically update with the arduino program.'))
options_menu.add_command(label='Quit Program', command=root.destroy)
menu_bar.add_cascade(label='Options', menu=options_menu)
menu_bar.add_command(label='Connect to Arduino', command=connect_to_ardunio)
root.config(menu=menu_bar)

'''
Main Frame
'''
main_frame = ttk.Frame(root)
main_frame.grid(column=0, row=0, padx=10, pady=10)

title_font = font.Font(family='Helvetica', size=16, weight='bold')
info_font = font.Font(family='Sans', size=12, weight='normal')

title_label = ttk.Label(main_frame, text='Home View', font=title_font)
title_label.grid(row=0, column=0, sticky=(tk.N), padx=10)

canvas = tk.Canvas(main_frame, width=500, height=350, background='#f4f4f4', highlightbackground='#000', highlightcolor='#000', highlightthickness=1)
canvas.grid(row=1, column=0, sticky=(tk.N,tk.E,tk.W), pady=10)

# manually draw interior
for i in range(10, 410, 100):
    canvas.create_rectangle(i, 10, i + 100, 60)
    canvas.create_rectangle(i, 60, i + 100, 110)

room_label = ttk.Label(main_frame, text='Selected Room:', font=info_font)
room_label.grid(row=2, column=0, sticky=(tk.W), padx=10)
temp_label = ttk.Label(main_frame, text='Temperature:', font=info_font)
temp_label.grid(row=3, column=0, sticky=(tk.W), padx=10)

def update_selected_room(room_num):
    room_label.config(text=f'Selected Room: {room_num}')

def update_temperature(temp):
    temp_label.config(text=f'Temperature: {temp}')

def create_popup(title, text):
    popup = tk.Toplevel(root, padx=10, pady=10)
    popup.title(title)
    popup.transient()
    popup.attributes('-topmost', 1)
    ttk.Label(popup, text=text).grid(row=0, column=0)
    ttk.Button(popup, text='OK', command=lambda: popup.destroy()).grid(row=1, column=0)


root.mainloop()
