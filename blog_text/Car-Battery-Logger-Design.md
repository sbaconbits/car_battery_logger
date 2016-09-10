+++
date = "2016-08-21T15:26:52+01:00"
draft = true
title = "Design"
tags = ["avr","INA226"]
categories= ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

A look at the system level design of the project.
<!--more-->


# Data acquisition
The simplest way to measure current is by measuring a voltage across a shunt resistor. There are a number of chips that can do all of the hard work for you, I went for this one [INA226](http://www.ti.com/product/INA226). The INA226 has many great attributes:

- Has a simple [I2C](https://en.wikipedia.org/wiki/I%C2%B2C) interface.
- Can perform high or low side [current measurements](https://en.wikipedia.org/wiki/Shunt_(electrical)#Use_in_current_measuring)
- Can take multiple measurements and locally average them, both bus voltage and shunt voltage.
- Consumes very little power and can assert an alert pin when measurements are taken.

For this project there are only two down sides to this part, it's a little pricey and it only comes in a small (when soldering with an iron) package (0.5mm pin pitch).

# Data storage
The bus and shunt voltage readings from the INA226 are 16-bits each. A configuration of 1024 samples every second (averaged) seems like more than enough. We need to store 4 bytes every second, seconds in a day 86,400 (60*60*24), two days would be 172,800, number of bytes without checksums or file system related data is 691,200 bytes (172,800 * 4) that's only 675KB.

I was considering using an SD card, loads of space and can then remove the card and plug it into a PC. A much simpler solution would be to use a SPI flash chip and extract the data over a serial connection, the SPI flash device used was the S25FL164K0XMFI011 which is 8MB (mega bytes) and only costs 0.65p in one off quantities, **the SD card socket alone would cost twice that**. Using an SD card could also cause mechanical problems, the engine bay of a car is unforgiving place. Also writing to an SD is more complex and would require the processor to be "awake" for longer using more power.


# Data extraction
Once the data has been acquired the simplest way to get that data from the device and onto a PC for processing must be via a serial connection, so I will use a UART. I've used a cables like this one [TTL-232R-RPI](http://www.ftdichip.com/Products/Cables/RPi.htm) in the past to connect a PC's USB port directly to a microcontrollers UART at TTL voltage levels and that will be fine for this project.

# Assumptions about the use of the device
I'm assuming the user will want to measure power usage at the car battery, and one other circuit. On the Land Rover the fuse box is not close to the battery, having one INA226 per board simplifies the overall design and the other components aren't very expensive so it makes sense to have one device measuring power from one source and have multiple devices to measure multiple sources.

# User interface
I want to keep this as simple as possible, there's no need for an LCD, a few LED's and buttons should be fine. I would like to have one LED to show the current mode of the device: powered, logging, in the menu etc. I would also like to have another LED to indicate an "event" has been triggered. Two buttons should make for a simple interface, one to change the mode and one to clear the notification of the triggered event.

## Triggered events
It would be very useful if a user could set up a power consumption level in the menu system what would trigger a notification to be shown on an LED. If a user wants to know if the power consumption went over 12W for example this could be set in the menu and if that event occurred the indication LED would flash, the user could then reset this trigger by pressing a button.

# Power
## Usage
Here are some very rough power usage calculations for the circuit, absolute worse case. The following assumes both LEDs are on all the time, the flash is being written to constantly, and the power measurement chip is fully awake all of the time. Pull up resistors haven't been included.

| Part          | Current     | Count | Total current  |
| ------------- |-------------|-------|----------------|
| INA226        | 330uA       | 1     | 330uA          |
| Atmega328p @ 8MHZ   | 9mA         | 1     | 9mA            |
| S25FL164K     | 35mA        | 1     | 35mA           |
| LED           | 20mA        | 2     | 40mA           |
| **TOTAL**     |             |       | **84mA**       |

When the device is in normal operation the flash will be written to once a second and the LED's will only be flashing for very short durations, so the power usage will be much lower than this. All of the components in this circuit will be running at 3.3V so the absolute maximum power usage will be 84mA * 3.3V = 277mW. I estimate the power consumption will be closer to 25mA * 3.3V = 82mW

## Components
The simplest way to regulate the voltage for this circuit (from the car power) would be using an [LDO](https://en.wikipedia.org/wiki/Low-dropout_regulator), as well as being simple to implement it's also doesn't generate the electrical noise a [switching regulator](https://en.wikipedia.org/wiki/Buck_converter) would. The down side of using an LDO is the wasted power, which is calculated by multiplying the input to output voltage difference multiplied by the current used, which in the absolute worse case would be (14.2V-3.3V)*84mA = 915mW, and estimated case (14.2V-3.3V)*25mA = 272mW.

The first version of this board had absolutely no input protection, the second version had a diode before the regulator, again this is a waste of power which is calculated my multiplying the diode voltage drop with the current going through it 0.7V * 25mA = 17mW (not forgetting this voltage drop can be subtracted from the LDO calculation above) . This is detailed in a later post (Future Improvements).

# Other uses for this board
After building v0.1 of this board I realised it could be used for measuring smaller circuits if I could install a smaller shunt resistor, so v0.2 has a footprint for a shunt on the back of the board.

