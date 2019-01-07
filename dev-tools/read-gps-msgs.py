#!venv/bin/python
"""
Records GPS messages from a Garmin handheld, this is facilitated by a microcontroller configured as a pass-through
 writing messages to a USB serial device
"""
import serial
import signal
import sys

if len(sys.argv) < 2:
    print('Usage {cmd} <serial device>'.format(cmd=sys.argv[0]))
    sys.exit(1)

USB_SERIAL = sys.argv[1]

serial_port = serial.Serial(USB_SERIAL, 9600)

total_msgs = 0


def signal_handler(signal, frame):
    """
    Handle signals from the operating system -- used to close cleanly on Ctrl+C
    """
    print('total msgs: {}'.format(total_msgs))
    serial_port.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

unique_msgs = []

while True:
    line = serial_port.readline()
    line = line.decode('ascii')
    if len(line) > 6:
        msg_type = line[:6]
        if msg_type not in unique_msgs:
            unique_msgs.append(msg_type)
            print('{}    -    {}'.format(msg_type, line[:len(line) - 2]))
    total_msgs += 1

