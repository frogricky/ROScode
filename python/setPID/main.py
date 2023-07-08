# -*- coding: utf-8 -*-
"""
Created on Wed May 31 14:50:42 2023

@author: HungYing
"""

import sys
import serial.tools.list_ports
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QComboBox, QTextEdit, QPushButton

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.serial_port = None

        self.setWindowTitle("Teensy Communication")
        self.setGeometry(100, 100, 400, 300)

        self.com_label = QLabel("COM Port:", self)
        self.com_label.move(20, 20)

        self.com_combo = QComboBox(self)
        self.com_combo.move(100, 20)

        self.send_text = QTextEdit(self)
        self.send_text.move(20, 60)
        self.send_text.setPlaceholderText("Enter text to send")

        self.receive_text = QTextEdit(self)
        self.receive_text.move(20, 120)
        self.receive_text.setReadOnly(True)

        self.send_button = QPushButton("Send", self)
        self.send_button.move(20, 240)
        self.send_button.clicked.connect(self.send_data)

        self.open_serial_port()

    
    def open_serial_port(self):
        ports = list(serial.tools.list_ports.comports())
        for port in ports:
            self.com_combo.addItem(port.device)

        self.serial_port = serial.Serial()

    def send_data(self):
        if self.serial_port.is_open:
            data = self.send_text.toPlainText().encode()
            self.serial_port.write(data)

    def read_data(self):
        if self.serial_port.is_open:
            while self.serial_port.in_waiting > 0:
                data = self.serial_port.readline()
                self.receive_text.append(data.decode().strip())

    def start_reading(self):
        if self.serial_port.is_open:
            self.serial_port.flushInput()
            self.serial_port.flushOutput()
            self.serial_port.timeout = 1
            self.serial_port.baudrate = 9600
            self.serial_port.port = self.com_combo.currentText()

            self.serial_port.open()

            self.read_data()

    def closeEvent(self, event):
        if self.serial_port.is_open:
            self.serial_port.close()

        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.start_reading()
    sys.exit(app.exec_())
