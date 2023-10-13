# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 20:22:13 2023

@author: HungYing
"""

def record_integers():
    integers = []

    while True:
        try:
            value = int(input("请输入一个整数 (输入非整数以退出): "))
            integers.append(value)
        except ValueError:
            break

    with open("integers.txt", "w") as file:
        file.write("[" + ",".join(map(str, integers)) + "]")
        print("整数已记录并保存到文件 integers.txt")

# 主程序
record_integers()