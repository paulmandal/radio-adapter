#!/bin/bash
avrdude -c usbtiny -p m328p -U lfuse:w:0xff:m -U hfuse:w:0xda:m -U efuse:w:0xfd:m

