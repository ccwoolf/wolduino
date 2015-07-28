# WOLduino - a Wake On LAN program for the Arduino Ethernet
Use your Arduino Ethernet to wake up a device which is on your LAN.

## Features
* LED status output
* Static or DHCP IP address aquisition
* Wake up at a push of a button, or when the Arduino is powered on (or reset)

## Prerequisites
* Arduino IDE
* Arduino Ethernet (not tested with any Ethernet shields, though any shield compatible with the `Ethernet` and `EthernetUDP` libraries should work)
* Setting your computer to be able to wake on LAN (you may need to enable this in your computer's BIOS)

## Setting up the Arduino
Start by opening the INO file in your text editor of choice.

1. Remove or comment out any of the `USE_` lines to disable that particular piece of functionality.
2. Modify `delay_time` to change the wait between packets and DHCP reattampts.
3. If you're using LEDs, make sure to change the configuration to use the right pins.
4. If you're using a button, make sure to change the configuration to use the right pin.
5. Modify `arduino_mac` to use your Arduino's assigned MAC address (or make one up if your Arduino does not have one).
6. If you're not using DHCP, modify `static_ip` to assign your Arduino an IP address.
7. Finally, change `target_mac` to the target computer's MAC address.

## License
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
