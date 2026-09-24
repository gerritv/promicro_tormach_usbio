Tormach USBIO emulator
=============================
This is a modified version of https://github.com/jwatte/teensy_tormach_usbio specifically for the SparkFun ProMicro AT32U4

This project implements the USB I/O board protocol for the Tormach / PathPilot 
controller. It supports both the input and output directions, mapping them to 
pins on the 32U4

Build using PlatformIo and upload. You can test the  code and pins using hte Terminal (preset to 38400)

By default, this shows up as board 0 but you can change the ID to 1/2/3 if you 
want to support the multiple-boards support of PathPilot.

You also need to install the udev rule (as root, with sudo) in /etc/udev/rules.d 
on the PathPilot, found here in file 40-teensy.rules. The udev file is specific to the ProMicro, if it doesn't appear in PathPilot, use 'lsusb' to determine the correct codes and mofify 40-Teensyrules.d
Original copyright 2019 Jon Watte; Changes by Gerrit Visser (2026); released under MIT license; no warranty given or 
liability accepted.
