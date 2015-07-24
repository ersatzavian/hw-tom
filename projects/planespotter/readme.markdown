# Planespotter Open ADS-B Receiver
Planespotter is a side project by [Tom Byrne](https://github.com/ersatzavian). The goal is a small, low-cost ADS-B receiver that includes the RF front end and decoder stages. RF comes in, decoded traffic messages come out over USB. 

## Summary
The RF front-end on planespotter is heavily based upon the [miniadsb](http://miniadsb.web99.de/homepage/index.php?way=1&site=READOUT&DERNAME=miniADSB%20Tutorial&dm=miniadsb&USER=miniadsb&goto=1&XURL=web99.de&WB=&EXTRAX=X&PIDX=63606) receiver by jetvision. I'm grateful to them for being willing to sell me just one or two SAW filters. They're the best place to find the TA1090EC and TA0232A required by this design unless you're buying thousands of them. 

Planespotter uses an STM32F030K6 MCU as the decoder. The STM32 family of microprocessors includes a very useful embedded bootloader, so the device can be reprogrammed over UART, elminating the need for an expensive in-system programmer. This design also includes an FT230X USB-to-Serial bridge, so the MCU can be reprogrammed right from a PC with just a binary image file. 

![planespotter](images/planespotter.jpg)

## Programming
To write a new image to the onboard flash on the STM32F030K6:

1. You may need to install [FTDI's Virtual Com Port Driver](http://www.ftdichip.com/Drivers/VCP.htm) if you're not on OS X. 
2. Download and install STM's [Flash Loader Demonstrator](http://www.st.com/web/en/catalog/tools/PF257525). It may also be possible to use [stm32loader](https://github.com/jsnyder/stm32loader), though it appears STM32F030 is not yet supported and I haven't gotten it working yet. 
3. Plug planespotter into your PC over USB. If you're using a VM, make sure to share the FTDI USB-to-Serial Device with the VM from the host machine. 
4. Open the Windows Device Manager and determine the COM port number Planespotter is using. You'll see the FTDI USB-to-Serial device listed among your COM ports.
5. Place the STM32 in Device Firmware Upgrade (DFU) Mode by holding S50 (BOOT0), tapping S20 (RESET_L), and releasing S50.
5. Open the STM Flash Loader Demonstrator and connect to the target. 
6. Point the Flash Loader Demonstrator at your target file and check the "jump to user code" box. 
7. Program! Your image should begin running immediately. 

## Software
Software for this project will be posted here as it is developed. This is currently at the "hello world" / "how do I toolchain" stage, and will be updated shortly. 

## Design Files
For the actual files used to produce fabricated boards, see the releases folder. Every release will include a schematic PDF, Bill of Materials (BOM), and set of Gerber files used to fab the PCB. 

## ECOs
### Rev 1.0
| Problem | Fix | Notes |
| ------- | --- | ----- |

## License

All material in this repository (unless otherwise specificed in the file) is licensed under the MIT License.

See LICENSE.md for more information.
