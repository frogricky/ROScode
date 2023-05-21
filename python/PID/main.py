# -*- coding: utf-8 -*-
"""
Created on Sun Apr 23 09:50:49 2023

@author: HungYing
"""

import tkinter as tk
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# 设置串口
serial_port = 'COM6'  # 请将此替换为您的串口名称
baud_rate = 9600
ser = serial.Serial(serial_port, baud_rate, timeout=1)

# 创建GUI窗口
root = tk.Tk()
root.title("Teensy PID Controller")

# 创建输入框和标签
p_label = tk.Label(root, text="P:")
p_label.grid(row=0, column=0)
p_entry = tk.Entry(root)
p_entry.grid(row=0, column=1)

i_label = tk.Label(root, text="I:")
i_label.grid(row=1, column=0)
i_entry = tk.Entry(root)
i_entry.grid(row=1, column=1)

d_label = tk.Label(root, text="D:")
d_label.grid(row=2, column=0)
d_entry = tk.Entry(root)
d_entry.grid(row=2, column=1)

setpoint_label = tk.Label(root, text="Setpoint:")
setpoint_label.grid(row=3, column=0)
setpoint_entry = tk.Entry(root)
setpoint_entry.grid(row=3, column=1)

variable_label = tk.Label(root, text="Variable:")
variable_label.grid(row=4, column=0)
variable_entry = tk.Entry(root)
variable_entry.grid(row=4, column=1)

# 发送数据到Teensy的函数
def send_data():
    try:
        p = float(p_entry.get())
        i = float(i_entry.get())
        d = float(d_entry.get())
        setpoint = float(setpoint_entry.get())
        variable = float(variable_entry.get())

        data_string = f"P:{p} I:{i} D:{d} S:{setpoint} V:{variable}\n"
        ser.write(data_string.encode('utf-8'))
    except ValueError:
        pass

# 创建发送按钮
send_button = tk.Button(root, text="Send", command=send_data)
send_button.grid(row=5, column=0, columnspan=2)

# 设置缓冲区和图表
buffer_size = 100
time_data = deque(maxlen=buffer_size)
variable_data = deque(maxlen=buffer_size)

fig, ax = plt.subplots()

# 初始化图表
def init():
    ax.set_xlim(0, buffer_size - 1)
    ax.set_ylim(0, 100)  # 根据需要调整Y轴范围
    line, = ax.plot([], [], lw=2)
    return line,

# 更新图表数据
def update(frame):
    line, = ax.plot(time_data, variable_data, lw=2)
    return line,


# 读取串口数据并添加到缓冲区
def read_serial_data():
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            try:
                time, variable = map(float, line.split(','))
                time_data.append(time)
                variable_data.append(variable)
            except ValueError:
                pass
        yield

# 设置动画
ani = animation.FuncAnimation(fig, update, frames=read_serial_data, init_func=init, blit=True, interval=10)

# 显示GUI和图表
root.after(1, plt.show)
root.mainloop()

