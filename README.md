# Radio Adapter Board
Adapter board to connect a Yaesu VX-8DR with a Garmin GPSmap64 and various .mil microphones

![alt text](https://github.com/paulmandal/radio-adapter/raw/master/pictures/finished_pcb.jpg "PCB")

# Requirements

- [Arduino](https://www.arduino.cc/en/Main/Software)
- [Eagle](https://www.autodesk.com/products/eagle/free-download)
- You must copy `ucontroller-code/platform.local.txt` to your `$ARDUINO_HOME/hardware/arduino/avr` directory to enable printf formatting of floats

# Table of Contents

| Directory | Contents |
|---|----|
| ucontroller-code | Arduino sketch to translate Garmin GPS NMEA sentences into the fixed-length that the Yaesu VX-8DR expects |
| circuit-board | Eagle circuit diagrams and PCB layouts for the adapter board |
| dev-tools | Various Python scripts that were useful during development |

# Important Note

The ATmega328p chips I got needed to have their fuses set, there is a script `set-fuses.sh` that will do this for you.  You may need to change the programmer from `usbtiny` to whatever you have on hand.

# References

This project borrows heavily from these sources:

[Reverse Engineering the Yaesu VX-8DR GPS Interface](http://lingnik.com/2013/02/09/reverse-engineering-yaesu-vx-8dr-gps-interface.html)

[Dynamic microphone to electret microphone input](http://www.epanorama.net/circuits/dynamic_to_electretinput.html)

