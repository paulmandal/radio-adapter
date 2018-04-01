#!venv/bin/python
import serial
import signal
import sys

USB_SERIAL = '/dev/ttyACM1'

total_msgs = 0

def signal_handler(signal, frame):
    print('total msgs: {}'.format(total_msgs))
    serial_port.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

unique_msgs = []

while True:
    serial_port = serial.Serial(USB_SERIAL, 9600)
    line = serial_port.readline()
    line = line.decode()
    if len(line) > 6:
        msg_type = line[:6]
        if msg_type not in unique_msgs:
            unique_msgs.append(msg_type)
            print('{}    -    {}'.format(msg_type, line[:len(line) - 2]))
    total_msgs = total_msgs + 1
