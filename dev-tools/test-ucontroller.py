#!venv/bin/python
"""
Tester for microcontroller transformation of GPS message.  Writes GPS NMEA messages contained in a file to a serial
 port, then reads the responses from another serial port and writes them to the console.
"""
import serial
import signal
import sys

if len(sys.argv) < 4:
    print('Usage {cmd} <file> <output serial device> <response serial device>'.format(cmd=sys.argv[0]))
    sys.exit(1)

INPUT_FILE = sys.argv[1]
INPUT_SERIAL = sys.argv[2]
GPS_SERIAL = sys.argv[3]
RADIO_SERIAL = sys.argv[4]

gps_port = serial.Serial(GPS_SERIAL, 4800)
radio_port = serial.Serial(RADIO_SERIAL, 9600)


def signal_handler(signal, frame):
    """
    Handle signals from the operating system -- used to close cleanly on Ctrl+C
    """
    gps_port.close()
    radio_port.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

with open(INPUT_FILE, 'r') as f:
    input_lines = f.readlines()

for line in input_lines:
    gps_port.write(line)
    print('wrote: {line}'.format(line=line))

    response = radio_port.readline()
    print(' read: {response}'.format(response=response))
    print('')
