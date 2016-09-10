+++
date = "2016-08-28T15:26:52+01:00"
draft = true
title = "Future improvements"
tags = ["avr","fire"]
categories= ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

Areas that I would like to improve, but I probably will not get around to doing as i'm ready for the next project.
<!--more-->
#mounting holes, fuses in the car

# PC software
At the moment to get data from the device you need to use the menu system over the serial connection and select which log entry to print, then take this log from the serial port and pass it to a simple python script to generate some graphs. To make this a bit more usable it would be good to have a GUI based application to interact with the device, set some trigger thresholds, extract the logs and present them. If I were building this system for someone else this would probably be the first thing I did.

# Firmware
## Reduce power consumption
It would be good to sleep the micro-controller while the INA226 is performing the averaging of samples, the INA226 could wake the atmega every time a batch of samples are ready.

Using lower power LED's would also save a high percentage of the power.

## Code layout
It would be good to separate the test code that is used for testing the separate components and driven by the menu system out from the main application. This code was useful during development and debugging hardware issues, but would only really be useful in a production test or self test situation now, but i've left it in place in case it interests anyone to read it.

## Improvements
I have added some test code to exercise the watchdog, but it isn't being used yet and it should be. It would also be good to use the brown out detection.

# Hardware
Here is a list of improvements to the circuit that would be required to make it more robust and user friendly.
## Protection
The circuit is really lacking any form of protection apart from the reverse voltage protection diode going into the LDO, here is a list of areas that need to be considered:

- Reverse and over voltage protection for the INA226.
- Over current conditions for the circuit (a fuse).
- Over voltage protection in front of the LDO.

If this circuit was ever fitted to a car it would be extremely important to add a fuse somewhere in case of a short, due to the very low ESR of car batteries a short could very easily cause a **fire** unless a fuse was fitted.

## Improvements
It would be good to remove the voltage drop across the input protection diode, this could be done with a FET based circuit as described [here](http://www.wa0itp.com/revpro.html). Currently the board doesn't have any mounting holes which means to fit the board into the case i've had to use sticky pads, mounting holes would be much better.

## Back fed power via the UART
If the UART cable i'm using (TTL-232R-RPI) is plugged into the board before the board is powered, the board it back fed power via the UART, this is bad for the micro-controller and can lead to some odd behaviour. This could probably be solved with a FET or some buffering.




