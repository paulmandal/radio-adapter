#!venv/bin/python
"""
Live tester for GPS integration -- connect the GPS to the microcontroller board and verify output messages
"""
import serial
import signal
import sys

if len(sys.argv) < 2:
    print('Usage {cmd} <input serial device>'.format(cmd=sys.argv[0]))
    sys.exit(1)

RADIO_SERIAL = sys.argv[1]

radio_port = serial.Serial(RADIO_SERIAL, 9600)

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
    radio_port.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

while True:
    response = radio_port.readline()
    response = response.decode('ascii').rstrip()
    if len(response) > 0:
        print('    read: {response}'.format(response=response))
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

radio_port.close()
