#!venv/bin/python
"""
Tester for microcontroller transformation of GPS message.  Writes GPS NMEA messages contained in a file to a serial
 port, then reads the responses from another serial port and writes them to the console.
"""
import serial
import signal
import sys

if len(sys.argv) < 4:
    print('Usage {cmd} <file> <output serial device> <response serial device> [--output-expected]'.format(cmd=sys.argv[0]))
    sys.exit(1)

INPUT_FILE = sys.argv[1]
GPS_SERIAL = sys.argv[2]
RADIO_SERIAL = sys.argv[3]
OUTPUT_EXPECTED = len(sys.argv) > 4 and sys.argv[4] == '--output-expected'

gps_port = serial.Serial(GPS_SERIAL, 4800)
radio_port = serial.Serial(RADIO_SERIAL, 9600, timeout=0.3)

message_formats = {
    '$GPGGA': '$GPGGA,hhmmss.sss,llll.llll,a,yyyyy.yyyy,a,x,xx,xx.x,xxxxx.x,M,xxxx.x,M,xxx.x,xxxx*hh',
    '$GPGLL': '$GPGLL,llll.llll,a,llll.llll,a,nnnnnn.nnn,a,a*hh',
    '$GPGSA': '$GPGSA,a,n,nn,nn,nn,nn,nn,,,,,,,,n.n,n.n,n.n*hh',
    '$GPGSV': '$GPGSV,n,n,nn,nn,nn,nnn,nn,nn,,,nn,nn,nn,nnn,nn,nn,nn,nnn,*hh',
    '$GPRMC': '$GPRMC,hhmmss.sss,a,llll.llll,a,yyyyy.yyyy,a,xxxx.xx,xxx.xx,xxxxxx,,*hh',
    '$GPVTG': '$GPVTG,,a,,a,n.nn,a,n.n,a,a*hh',
    '$GPZDA': '$GPZDA,hhmmss.sss,xx,xx,xxxx,,*hh',
}


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
    line = line.rstrip()
    gps_port.write('{line}\n'.format(line=line).encode())
    print('   wrote: {line}'.format(line=line))

    while True:
        response = radio_port.readline()
        response = response.decode('ascii').rstrip()
        if len(response) > 0:
            print('    read: {response}'.format(response=response))
            if OUTPUT_EXPECTED:
                expected = message_formats[response[:6]]
                print('expected: {expected}'.format(expected=expected))
                response_fields = response.split(',')
                expected_fields = expected.split(',')
                if len(response_fields) != len(expected_fields):
                    print('Error!  Response and expected field counts differ, response: {response_fields_len}, '
                          'expected: {expected_fields_len}'.format(response_fields_len=len(response_fields),
                                                                   expected_fields_len=len(expected_fields)))
                else:
                    for idx, field in enumerate(response_fields):
                        if len(response_fields[idx]) != len(expected_fields[idx]):
                            print('Error!  Field #{idx} lengths differ, response: {response_field_len}, '
                                  'expected: {expected_field_len}'.format(idx=idx,
                                                                          response_field_len=len(response_fields[idx]),
                                                                          expected_field_len=len(expected_fields[idx])))

        else:
            break
    print('')

gps_port.close()
radio_port.close()
