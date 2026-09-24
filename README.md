Tormach USBIO emulator
=============================
This is a modified version of https://github.com/jwatte/teensy_tormach_usbio specifically for the SparkFun ProMicro AT32U4
Big thanks to JWatte for figuring this out and providing a solid base to modify.

This project implements the USB I/O board protocol for the Tormach / PathPilot 
controller. It supports both the input and output directions, mapping them to 
pins on the 32U4
The output pins are configured for a relay board the has active low inputs. If your relay board is active high, then remove the !'s from the appropriate place. The same applies to inputs... I am using the ubiquitous 817-based optoisolator board, it also required inverting the pins value from the Teensy version.

Build using PlatformIo and upload. You can test the code and pins using the Terminal (preset to 38400)

By default, this shows up as board 0 but you can change the ID to 1/2/3 if you 
want to support the multiple-boards support of PathPilot.

You also need to install the udev rule (as root, with sudo) in /etc/udev/rules.d 
on the PathPilot, found here in file 40-usbio.rules. The udev file is specific to the ProMicro, if it doesn't appear in PathPilot, use 'lsusb' to determine the correct codes and mofify 40-usbio_rules.d
Original copyright 2019 Jon Watte; Changes by Gerrit Visser (2026); released under MIT license; no warranty given or 
liability accepted.
