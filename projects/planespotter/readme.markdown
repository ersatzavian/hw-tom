# Planespotter Open ADS-B Receiver
Planespotter is a side project by [Tom Byrne](https://github.com/ersatzavian). The goal is a small, low-cost ADS-B receiver that includes the RF front end and decoder stages. RF comes in, decoded traffic messages come out over USB. 

## Summary
The RF front-end on planespotter is heavily based upon the [miniadsb](http://miniadsb.web99.de/homepage/index.php?way=1&site=READOUT&DERNAME=miniADSB%20Tutorial&dm=miniadsb&USER=miniadsb&goto=1&XURL=web99.de&WB=&EXTRAX=X&PIDX=63606) receiver by jetvision. I'm grateful to them for being willing to sell me just one or two SAW filters. They're the best place to find the TA1090EC and TA0232A required by this design unless you're buying thousands of them. 

Planespotter uses an STM32F030K6 MCU as the decoder. The STM32 family of microprocessors includes a very useful embedded bootloader, so the device can be reprogrammed over UART, elminating the need for an expensive in-system programmer. This design also includes an FT230X USB-to-Serial bridge, so the MCU can be reprogrammed right from a PC with just a binary image file. 

![planespotter](images/planespotter.jpg)

## Programming
To write a new image to the onboard flash on the STM32F030K6:

1. You may need to install [FTDI's Virtual Com Port Driver](http://www.ftdichip.com/Drivers/VCP.htm) if you're not on OS X. 
2. Download and install Python, required for [stm32loader](https://github.com/jsnyder/stm32loader).
3. Plug planespotter into your PC over USB. If you're using a VM, make sure to share the FTDI USB-to-Serial Device with the VM from the host machine. 
4. Find the device name for the usb-serial adapter on your planespotter:

    ```
    $ ls /dev/tty.usbserial*
    /dev/tty.usbserial-DB00KYMI
    ```
5. Place the STM32 in Device Firmware Upgrade (DFU) Mode by holding S50 (BOOT0), tapping S20 (RESET_L), and releasing S50.
6. Make sure planespotter and the binary you are flashing are in the same directory (they are, if you're using a binary provided at planespotter/software/).
7. Use stm32loader to load the binary onto Planespotter:

    ```
    $ ./stm32loader.py -e -w -v -p /dev/tty.usbserial-DB00KYMI -b 57600 <image_name>
    Bootloader version 31
    Chip id: 0x444 (Unknown)
    Extended erase (0x44), this can take ten seconds or more
    Writing: 100% Time: 0:00:13 |#################################################|
    Reading: 100%, Time: 0:00:07 |################################################|
    Verification OK
    ```
8. When programming has finished, tap the Reset button (S20). 

## Software
Software for this project will be posted here as it is developed. This project doesn't have working ADS-B detector software yet as I wasn't able to located a signal with any of the crappy antennas I already have and I'm trying to get my hands on a signal generator to prove out the detector.

After much messing around with Keil and STM32Cube, I determined that my life will be too short to spend it making obtuse directory structures for a simple project, and yours is probably too short to spend it parsing said crap. So everything here now based on the [mbed platform](https://www.mbed.com/en/).

To use the mbed online compiler, go to [https://developer.mbed.org/compiler](https://developer.mbed.org/compiler).

Planespotter software is built using the [NUCLEO-F031K6 target](https://developer.mbed.org/platforms/ST-Nucleo-F031K6/) in the mbed compiler, which is effectively just a breakout board for the STM32F031. This is close enough to write software for Planespotter.

Source files from the mbed compiler will be posted here. To import the full mbed project, use the mbed compiler and pick up the project from its [Mercurial Repository](https://developer.mbed.org/users/tombrew/code/planespotter_adc_logger/).

## Design Files
For the actual files used to produce fabricated boards, see the releases folder. Every release will include a schematic PDF, Bill of Materials (BOM), and set of Gerber files used to fab the PCB. 

## ECOs
### Rev 1.0
| Problem | Fix | Notes |
| ------- | --- | ----- |
| Allow onboard FTDI to toggle BOOT0 for easier target programming | | |
| Add labels to S20 and S50, J50 | | |

## License

All material in this repository (unless otherwise specificed in the file) is licensed under the MIT License.

See LICENSE.md for more information.
