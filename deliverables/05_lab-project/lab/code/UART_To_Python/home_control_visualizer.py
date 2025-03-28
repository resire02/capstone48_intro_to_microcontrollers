import tkinter as tk
from tkinter import ttk, font, scrolledtext
import threading
import serial
import serial.tools.list_ports_windows as list_ports
import re

'''
Config
'''
# PROGRAM_LOGO = 'home_control_system_logo.ico'
AVAILABLE_BAUD_RATES = [9600, 115200]
ROOMS = [
    'Bedroom 1',
    'Master Bedroom',
    'Master Bathroom',
    'Bedroom 2',
    'Living Room',
    'Kitchen',
    'Dining Room',
    'Hallway Bathroom',
]
COLOR_RED = '#ff0000'
COLOR_GREEN = '#00ff00'
COLOR_BLUE = '#0000ff'

SELECTED_PORT = None
SELECTED_BAUD_RATE = None
ROOM_INDEX = 0

###### ARDUINO PORT ROUTING

def set_port(port):
    global SELECTED_PORT
    print('Selected Port:', port)
    SELECTED_PORT = port

def set_baudrate(rate):
    global SELECTED_BAUD_RATE
    print('Selected Baud Rate:', rate)
    SELECTED_BAUD_RATE = rate

def arduino_uart_thread():
    if SELECTED_PORT is None or SELECTED_BAUD_RATE is None:
        create_popup('Error', 'Both port and baud rate need to be set!')
        return
    try:
        print(f'Attempting connection on port {SELECTED_PORT} at {SELECTED_BAUD_RATE}...')
        uart = serial.Serial(port=SELECTED_PORT, baudrate=SELECTED_BAUD_RATE, timeout=0.1)
        print('Established connection!')
        while True:
            if uart.in_waiting:
                received_data = uart.readline().decode('utf-8').replace('\n', '')
                arduino_update_ui(received_data, uart)
    except serial.SerialException:
        create_popup('Error', 'Could not connect to Arduino. Ensure that Arduino IDE is closed\nand that the port name matches the port in device manager and is not being currently used.')
    finally:
        UART_CONNECTED = False

def connect_to_ardunio():
    thread = threading.Thread(target=arduino_uart_thread, daemon=True)
    thread.start()

def list_comports():
    return [(x.name,x.device) for x in list_ports.comports()]

def set_port_func(port):
    def _inner():
        set_port(port)
    return _inner

def set_baudrate_func(baud_rate):
    def _inner():
        set_baudrate(baud_rate)
    return _inner

###### CANVAS DRAW OPERATIONS

def draw_bedroom_1(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x, y, x, y+120, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x, y, x+135, y, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+135, y, x+135, y+60, width=w, fill=color if highlight else None) # right line stick
    canvas.create_line(x+95, y+60, x+135, y+60,width=w, fill=color if highlight else None) # bottom line stick
    canvas.create_line(x+95, y+60, x+95, y+120, width=w, fill=color if highlight else None) # right line inner
    canvas.create_line(x, y+120, x+95, y+120, width=w, fill=color if highlight else None) # bottom line

def draw_west_hallway(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+20, y+120, x+200, y+120, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+20, y+120, x+20, y+160, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+20, y+160, x+200, y+160, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+200, y, x+200, y+120, width=w, fill=color if highlight else None) # left inner line
    canvas.create_line(x+200, y, x+240, y, width=w, fill=color if highlight else None) # top outer line
    canvas.create_line(x+240, y, x+240, y+160, width=w, fill=color if highlight else None) # right line

def draw_master_bedroom(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+20, y+160, x+115, y+160, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+20, y+160, x+20, y+280, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+20, y+280, x+150, y+280, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+150, y+220, x+150, y+280, width=w, fill=color if highlight else None) # right outer line
    canvas.create_line(x+115, y+220, x+150, y+220, width=w, fill=color if highlight else None) # bottom inner line
    canvas.create_line(x+115, y+160, x+115, y+220, width=w, fill=color if highlight else None) # left inner line

def draw_master_bathroom(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+115, y+220, x+180, y+220, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+115, y+160, x+115, y+220, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+115, y+160, x+180, y+160, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+180, y+160, x+180, y+220, width=w, fill=color if highlight else None) # right line

def draw_bedroom_2(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+135, y, x+200, y, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+135, y, x+135, y+60, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+95, y+60, x+135, y+60, width=w, fill=color if highlight else None) # inner top line
    canvas.create_line(x+95, y+60, x+95, y+120, width=w, fill=color if highlight else None) # left outer line
    canvas.create_line(x+95, y+120, x+200, y+120, width=w, fill=color if highlight else None) # left outer line
    canvas.create_line(x+200, y, x+200, y+120, width=w, fill=color if highlight else None) # right line

def draw_main_living_room(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+150, y+280, x+270, y+280, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+150, y+220, x+150, y+280, width=w, fill=color if highlight else None) # left outer
    canvas.create_line(x+150, y+220, x+180, y+220, width=w, fill=color if highlight else None) # inner top
    canvas.create_line(x+180, y+160, x+180, y+220, width=w, fill=color if highlight else None) # left inner
    canvas.create_line(x+180, y+160, x+270, y+160, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+270, y+160, x+270, y+280, width=w, fill=color if highlight else None) # right line

def draw_kitchen(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+270, y+160, x+270, y+280, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+270, y+280, x+350, y+280, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+350, y+115, x+350, y+280, width=w, fill=color if highlight else None) # right line
    canvas.create_line(x+270, y+160, x+300, y+160, width=w, fill=color if highlight else None) # top inner line
    canvas.create_line(x+300, y+115, x+300, y+160, width=w, fill=color if highlight else None) # left inner line
    canvas.create_line(x+300, y+115, x+350, y+115, width=w, fill=color if highlight else None) # top outer line

def draw_dining_room(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+240, y+160, x+300, y+160, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+300, y+115, x+330, y+115, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+300, y+115, x+300, y+160, width=w, fill=color if highlight else None) # right line
    canvas.create_line(x+240, y+55, x+240, y+160, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+330, y+55, x+330, y+115, width=w, fill=color if highlight else None) # right above
    canvas.create_line(x+240, y+55, x+330, y+55, width=w, fill=color if highlight else None) # top above
    
def draw_hallway_bathroom(canvas, x, y, highlight=False, color=COLOR_BLUE):
    w = 3 if highlight else 1
    canvas.create_line(x+240, y, x+330, y, width=w, fill=color if highlight else None) # top line
    canvas.create_line(x+240, y, x+240, y+55, width=w, fill=color if highlight else None) # left line
    canvas.create_line(x+240, y+55, x+330, y+55, width=w, fill=color if highlight else None) # bottom line
    canvas.create_line(x+330, y, x+330, y+55, width=w, fill=color if highlight else None) # right line

def draw_home_layout(canvas, active=None, x=20, y=20, color=COLOR_BLUE):
    canvas.delete('all')
    draw_bedroom_1(canvas, x, y, active==ROOMS[0], color=color)
    draw_west_hallway(canvas, x, y, False)
    draw_master_bedroom(canvas, x, y, active==ROOMS[1], color=color)
    draw_master_bathroom(canvas, x, y, active==ROOMS[2], color=color)
    draw_bedroom_2(canvas, x, y, active==ROOMS[3], color=color)
    draw_main_living_room(canvas, x, y, active==ROOMS[4], color=color)
    draw_kitchen(canvas, x, y, active==ROOMS[5], color=color)
    draw_dining_room(canvas, x, y, active==ROOMS[6], color=color)
    draw_hallway_bathroom(canvas, x, y, active==ROOMS[7], color=color)

###### Tkinter Screen Setup

root = tk.Tk()
root.title('Home Control System')
root.resizable(False, False)
# root.iconbitmap(PROGRAM_LOGO)

'''
Menus
'''
menu_bar = tk.Menu(root, tearoff=tk.FALSE)
options_menu = tk.Menu(menu_bar, tearoff=tk.FALSE)
ports_submenu = tk.Menu(options_menu, tearoff=tk.FALSE)
for port,device in list_comports():
    ports_submenu.add_checkbutton(label=f'{port} - {device}', command=set_port_func(port))
options_menu.add_cascade(label='Set Port', menu=ports_submenu)
baud_submenu = tk.Menu(options_menu, tearoff=tk.FALSE)
for rate in AVAILABLE_BAUD_RATES:
    baud_submenu.add_checkbutton(label=rate, command=set_baudrate_func(rate))
options_menu.add_cascade(label='Set Baud Rate', menu=baud_submenu)
options_menu.add_separator()
options_menu.add_command(label='How To Use', command=lambda: create_popup('How To Use', 'Set the baud rate and port, then connect to Arduino.\nThe program should automatically update with the arduino program.'))
options_menu.add_command(label='About', command=lambda: create_popup('About', 'Intro to Microcontrollers - Home Control System, for Arduino Nano Explorer EV58G97A'))
options_menu.add_command(label='Quit', command=root.destroy)
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

canvas = tk.Canvas(main_frame, width=400, height=350, background='#f7f7f7', highlightbackground='#f0f0f0', highlightcolor='#f0f0f0', highlightthickness=1)
canvas.grid(row=1, column=0, sticky=(tk.N,tk.E,tk.W), pady=10)

# labels
room_var = tk.StringVar(main_frame, 'Selected Room:')
temperature_var = tk.StringVar(main_frame, 'Temperature:')
proximity_var = tk.IntVar(main_frame, value=0)
info_var = tk.StringVar(main_frame, 'Message:')

proximity_indicator = ttk.Progressbar(main_frame, variable=proximity_var)
proximity_indicator.grid(row=2, column=0, padx=10, pady=10)
room_label = ttk.Label(main_frame, textvariable=room_var, font=info_font)
room_label.grid(row=3, column=0, sticky=(tk.W), padx=10)
temp_label = ttk.Label(main_frame, textvariable=temperature_var, font=info_font)
temp_label.grid(row=4, column=0, sticky=(tk.W), padx=10)
info_label = ttk.Label(main_frame, textvariable=info_var, font=info_font)
info_label.grid(row=5, column=0, sticky=(tk.W), padx=10)


# draw canvas and set values
draw_home_layout(canvas, active=None)

def update_temperature(temperature):
    print(f'Updating with temperature {temperature}C...')
    global temperature_var
    temperature_var.set(f'Temperature: {temperature}')

def update_selected_room(room, color):
    print(f'Updating room {room} with color {color}!')
    global ROOM_INDEX
    if room is not None:
        ROOM_INDEX = room
    global canvas
    if color == 'red':
        draw_home_layout(canvas, active=ROOMS[ROOM_INDEX], color=COLOR_RED)
    elif color == 'green':
        draw_home_layout(canvas, active=ROOMS[ROOM_INDEX], color=COLOR_GREEN)
    elif color == 'blue':
        draw_home_layout(canvas, active=ROOMS[ROOM_INDEX], color=COLOR_BLUE)
    room_var.set(f'Selected Room: {ROOMS[ROOM_INDEX]}')

def update_message_label(message):
    global info_var
    info_var.set(f'Message: {message}')

def update_proximity(value):
    global proximity_var
    progress = round(value / 4095 * 100)
    proximity_var.set(progress)

def arduino_update_ui(text_input, serial_port):
    print('Received Data:', text_input)
    text_input_lowered = text_input.lower()
    try:
        if (match := re.search(r"temperature: (.+)", text_input_lowered)) is not None:
            temperature = str(match.group(1))
            update_temperature(temperature.upper())
        elif (match := re.search(r"moving to room (\d+) with color ([a-z]+)", text_input_lowered)) is not None:
            room = int(match.group(1))
            color = str(match.group(2))
            if 0 <= room <= 7 and color in {'blue', 'green', 'red'}:
                update_selected_room(room, color)
        elif (match := re.search(r"changing room color to ([a-z]+)", text_input_lowered)) is not None:
            color = str(match.group(1))
            if color in {'blue', 'green', 'red'}:
                update_selected_room(None, color)
        elif (match := re.search(r"prox data: (\d+)", text_input_lowered)) is not None:
            proximity = int(match.group(1))
            update_proximity(proximity)
        elif (match := re.search(r"proximity: (\d+)", text_input_lowered)) is not None:
            proximity = int(match.group(1))
            update_proximity(proximity)
        elif (match := re.search(r"pushing|released", text_input_lowered)) is not None:
            update_message_label(text_input)
        elif (match := re.search(r"password found.", text_input_lowered)) is not None:
            create_input_popup(text_input, serial_port)
        elif (match := re.search(r"try again.", text_input_lowered)) is not None:
            create_input_popup(text_input, serial_port)
        elif (match := re.search(r"no password found.", text_input_lowered)) is not None:
            create_input_popup(text_input, serial_port)
    except Exception as e:
        print('An error occurred while parsing: ', e)

def create_popup(title, text, width=300, height=100):
    global root
    popup = tk.Toplevel(root, padx=10, pady=10, width=width, height=height)
    # popup.iconbitmap(PROGRAM_LOGO)
    x = root.winfo_x() + (root.winfo_width() - width) // 2
    y = root.winfo_y() + (root.winfo_height() - height) // 2
    popup.geometry(f'+{x}+{y}')
    popup.title(title)
    popup.transient()
    popup.attributes('-topmost', 1)
    popup.grab_set()
    ttk.Label(popup, text=text).grid(row=0, column=0)
    ttk.Button(popup, text='OK', command=lambda: popup.destroy()).grid(row=1, column=0)

def send_password(popup, password, serial_port):
    serial_port.write(password.encode('utf-8'))
    popup.destroy()

def create_input_popup(text, serial_port, width=300, height=100):
    global root
    popup = tk.Toplevel(root, padx=10, pady=10, width=width, height=height)
    # popup.iconbitmap(PROGRAM_LOGO)
    x = root.winfo_x() + (root.winfo_width() - width) // 2
    y = root.winfo_y() + (root.winfo_height() - height) // 2
    popup.geometry(f'+{x}+{y}')
    popup.title('UART')
    popup.transient()
    popup.attributes('-topmost', 1)
    popup.grab_set()
    ttk.Label(popup, text=text).grid(row=0, column=0)
    input_field = tk.Entry(popup, width=30)
    input_field.grid(row=1, column=0, pady=10)
    ttk.Button(popup, width=30, command=lambda: send_password(popup, input_field.get(), serial_port), text='Submit').grid(row=2, column=0)

root.mainloop()
