from tkinter import *
from tkinter import ttk, font
import threading
import serial

root = Tk()
root.title('Introduction to Microcontrollers - Home Control System')

main_frame = ttk.Frame(root)
main_frame.grid(column=0, row=0)

title_font = font.Font(family='Helvetica', size=16, weight='bold')
info_font = font.Font(family='Sans', size=12, weight='normal')

title_label = ttk.Label(main_frame, text='Home View', font=title_font)
title_label.grid(row=0, column=0, sticky=(N), padx=10)

canvas = Canvas(main_frame, width=500, height=350, background='#a4a4a4', highlightbackground='#000', highlightcolor='#000', highlightthickness=2)
canvas.grid(row=1, column=0, sticky=(N,E,W), padx=10, pady=10)

# manually draw interior
for i in range(10, 410, 100):
    canvas.create_rectangle(i, 10, i + 100, 60)
    canvas.create_rectangle(i, 60, i + 100, 110)

room_label = ttk.Label(main_frame, text='Selected Room:', font=info_font)
room_label.grid(row=2, column=0, sticky=(W), padx=10)
temp_label = ttk.Label(main_frame, text='Temperature:', font=info_font)
temp_label.grid(row=3, column=0, sticky=(W), padx=10)

def update_selected_room(room_num):
    room_label.config(text=f'Selected Room: {room_num}')

def update_temperature(temp):
    temp_label.config(text=f'Temperature: {temp}')

def arduino_uart_loop():
    print('Starting serial loop...')
    try:
        uart = serial.Serial(port='COM7', baudrate=115200, timeout=0.1)
        while True:
            if uart.in_waiting:
                received_data = uart.readline().decode('utf-8').replace('\n', '')
                data = [int(x) for x in received_data.split(',')]
                print(f'Received: {data}')
                update_temperature(data[0])
                update_selected_room(data[0])
    except serial.SerialException:
        raise RuntimeError('Could not connect to Arduino. Ensure that Arduino IDE is closed and that the port name matches the port in device manager.')

serial_thread = threading.Thread(target=arduino_uart_loop, daemon=True)
root.after(0, serial_thread.start)
root.mainloop()
