# -*- coding: utf-8 -*-
"""
Created on Wed May 31 19:40:11 2023

@author: HungYing
"""

import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QComboBox, QLineEdit, QTextEdit
import serial

class SerialApp(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

        self.serialPort = None

    def initUI(self):
        self.setWindowTitle('Serial Communication')

        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.portSelector = QComboBox()
        self.refreshPorts()
        self.layout.addWidget(self.portSelector)

        self.refreshButton = QPushButton("Refresh Ports")
        self.refreshButton.clicked.connect(self.refreshPorts)
        self.layout.addWidget(self.refreshButton)

        self.inputLine = QLineEdit()
        self.layout.addWidget(self.inputLine)

        self.sendButton = QPushButton("Send")
        self.sendButton.clicked.connect(self.sendData)
        self.layout.addWidget(self.sendButton)

        self.outputText = QTextEdit()
        self.layout.addWidget(self.outputText)

    def refreshPorts(self):
        self.portSelector.clear()
        for port in serial.tools.list_ports.comports():
            self.portSelector.addItem(port.device)

    def sendData(self):
        if self.serialPort and self.serialPort.isOpen():
            self.serialPort.close()

        self.serialPort = serial.Serial(self.portSelector.currentText(), 9600)
        self.serialPort.write(self.inputLine.text().encode())
        response = self.serialPort.read_until().decode()
        self.outputText.append(response)
        self.serialPort.close()

app = QApplication(sys.argv)
ex = SerialApp()
ex.show()
sys.exit(app.exec_())
