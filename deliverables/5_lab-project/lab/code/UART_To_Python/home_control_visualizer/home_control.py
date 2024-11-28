import tkinter as tk
from tkinter import ttk, font
import threading
import serial
import serial.tools.list_ports_windows as list_ports

'''
Config
'''
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

SELECTED_PORT = None
SELECTED_BAUD_RATE = None
ROOM_INDEX = 0

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
        print('Established connection!')
        while True:
            if uart.in_waiting:
                received_data = uart.readline().decode('utf-8').replace('\n', '')
                print(f'Received: {received_data}')
    except serial.SerialException:
        create_popup('Error', 'Could not connect to Arduino. Ensure that Arduino IDE is closed\nand that the port name matches the port in device manager and is not being currently used.')

def connect_to_ardunio():
    thread = threading.Thread(target=arduino_uart_thread, daemon=True)
    thread.start()

def list_comports():
    return [(x.name,x.device) for x in list_ports.comports()]


root = tk.Tk()
root.title('Introduction to Microcontrollers - Home Control System')
root.resizable(False, False)

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

canvas = tk.Canvas(main_frame, width=400, height=350, background='#f4f4f4', highlightbackground='#000', highlightcolor='#000', highlightthickness=0)
canvas.grid(row=1, column=0, sticky=(tk.N,tk.E,tk.W), pady=10)

def draw_bedroom_1(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x, y, x, y+120, width=w) # left line
    canvas.create_line(x, y, x+135, y, width=w) # top line
    canvas.create_line(x+135, y, x+135, y+60, width=w) # right line stick
    canvas.create_line(x+95, y+60, x+135, y+60,width=w) # bottom line stick
    canvas.create_line(x+95, y+60, x+95, y+120, width=w) # right line inner
    canvas.create_line(x, y+120, x+95, y+120, width=w) # bottom line

def draw_west_hallway(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+20, y+120, x+200, y+120, width=w) # top line
    canvas.create_line(x+20, y+120, x+20, y+160, width=w) # left line
    canvas.create_line(x+20, y+160, x+200, y+160, width=w) # bottom line
    canvas.create_line(x+200, y, x+200, y+120, width=w) # left inner line
    canvas.create_line(x+200, y, x+240, y, width=w) # top outer line
    canvas.create_line(x+240, y, x+240, y+160, width=w) # right line

def draw_master_bedroom(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+20, y+160, x+115, y+160, width=w) # top line
    canvas.create_line(x+20, y+160, x+20, y+280, width=w) # left line
    canvas.create_line(x+20, y+280, x+150, y+280, width=w) # bottom line
    canvas.create_line(x+150, y+220, x+150, y+280, width=w) # right outer line
    canvas.create_line(x+115, y+220, x+150, y+220, width=w) # bottom inner line
    canvas.create_line(x+115, y+160, x+115, y+220, width=w) # left inner line

def draw_master_bathroom(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+115, y+220, x+180, y+220, width=w) # bottom line
    canvas.create_line(x+115, y+160, x+115, y+220, width=w) # left line
    canvas.create_line(x+115, y+160, x+180, y+160, width=w) # top line
    canvas.create_line(x+180, y+160, x+180, y+220, width=w) # right line

def draw_bedroom_2(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+135, y, x+200, y, width=w) # top line
    canvas.create_line(x+135, y, x+135, y+60, width=w) # left line
    canvas.create_line(x+95, y+60, x+135, y+60, width=w) # inner top line
    canvas.create_line(x+95, y+60, x+95, y+120, width=w) # left outer line
    canvas.create_line(x+95, y+120, x+200, y+120, width=w) # left outer line
    canvas.create_line(x+200, y, x+200, y+120, width=w) # right line

def draw_main_living_room(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+150, y+280, x+270, y+280, width=w) # bottom line
    canvas.create_line(x+150, y+220, x+150, y+280, width=w) # left outer
    canvas.create_line(x+150, y+220, x+180, y+220, width=w) # inner top
    canvas.create_line(x+180, y+160, x+180, y+220, width=w) # left inner
    canvas.create_line(x+180, y+160, x+270, y+160, width=w) # top line
    canvas.create_line(x+270, y+160, x+270, y+280, width=w) # right line

def draw_kitchen(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+270, y+160, x+270, y+280, width=w) # left line
    canvas.create_line(x+270, y+280, x+350, y+280, width=w) # bottom line
    canvas.create_line(x+350, y+115, x+350, y+280, width=w) # right line
    canvas.create_line(x+270, y+160, x+300, y+160, width=w) # top inner line
    canvas.create_line(x+300, y+115, x+300, y+160, width=w) # left inner line
    canvas.create_line(x+300, y+115, x+350, y+115, width=w) # top outer line

def draw_dining_room(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+240, y+160, x+300, y+160, width=w) # bottom line
    canvas.create_line(x+300, y+115, x+330, y+115, width=w) # top line
    canvas.create_line(x+300, y+115, x+300, y+160, width=w) # right line
    canvas.create_line(x+240, y+55, x+240, y+160, width=w) # left line
    canvas.create_line(x+330, y+55, x+330, y+115, width=w) # right above
    canvas.create_line(x+240, y+55, x+330, y+55, width=w) # top above
    
def draw_hallway_bathroom(canvas, x, y, highlight=False):
    w = 3 if highlight else 1
    canvas.create_line(x+240, y, x+330, y, width=w) # top line
    canvas.create_line(x+240, y, x+240, y+55, width=w) # left line
    canvas.create_line(x+240, y+55, x+330, y+55, width=w) # bottom line
    canvas.create_line(x+330, y, x+330, y+55, width=w) # right line

def draw_home_layout(canvas, active=None, x=10, y=10):
    canvas.delete('all')
    draw_bedroom_1(canvas, x, y, active==ROOMS[0])
    draw_west_hallway(canvas, x, y, False)
    draw_master_bedroom(canvas, x, y, active==ROOMS[1])
    draw_master_bathroom(canvas, x, y, active==ROOMS[2])
    draw_bedroom_2(canvas, x, y, active==ROOMS[3])
    draw_main_living_room(canvas, x, y, active==ROOMS[4])
    draw_kitchen(canvas, x, y, active==ROOMS[5])
    draw_dining_room(canvas, x, y, active==ROOMS[6])
    draw_hallway_bathroom(canvas, x, y, active==ROOMS[7])

room_var = tk.StringVar(main_frame, 'Selected Room:')

room_label = ttk.Label(main_frame, textvariable=room_var, font=info_font)
room_label.grid(row=2, column=0, sticky=(tk.W), padx=10)
temp_label = ttk.Label(main_frame, text='Temperature:', font=info_font)
temp_label.grid(row=3, column=0, sticky=(tk.W), padx=10)

draw_home_layout(canvas, active=ROOMS[ROOM_INDEX], x=20)
room_var.set(f'Selected Room: {ROOMS[ROOM_INDEX]}')

def next_room():
    global ROOM_INDEX
    ROOM_INDEX += 1
    if ROOM_INDEX >= len(ROOMS):
        ROOM_INDEX = 0
    draw_home_layout(canvas, active=ROOMS[ROOM_INDEX], x=20)
    room_var.set(f'Selected Room: {ROOMS[ROOM_INDEX]}')

test_button = ttk.Button(main_frame, text='switch', command=next_room)
test_button.grid(row=4, column=0, sticky=(tk.W), padx=10)


def update_selected_room(room_num):
    room_label.config(text=f'Selected Room: {room_num}')

def update_temperature(temp):
    temp_label.config(text=f'Temperature: {temp}')

def create_popup(title, text, width=300, height=100):
    popup = tk.Toplevel(root, padx=10, pady=10, width=width, height=height)
    x = root.winfo_x() + (root.winfo_width() - width) // 2
    y = root.winfo_y() + (root.winfo_height() - height) // 2
    popup.geometry(f'+{x}+{y}')
    popup.title(title)
    popup.transient()
    popup.attributes('-topmost', 1)
    popup.grab_set()
    ttk.Label(popup, text=text).grid(row=0, column=0)
    ttk.Button(popup, text='OK', command=lambda: popup.destroy()).grid(row=1, column=0)

root.mainloop()
