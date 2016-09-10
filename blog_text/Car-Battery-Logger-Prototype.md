+++
date = "2016-08-22T15:26:52+01:00"
draft = true
title = "Prototype"
tags = ["avr"]
categories= ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

My approach to building the prototype.
<!--more-->

# Time to get the soldering iron out
I like to prototype anything I work on, it helps to remove most of the unknowns and solidify ideas. I intent to get my PCBs made from one of those cheap board manufacturers, the only catch is they take many weeks to deliver (for free) so a prototype should reduce the number of board spins and allow me to proceed with writing the firmware.

I find prototyping with through hole packages easiest, but many device only come in surface mount packages these days so I have used adapter/converter boards that you can see below. I have put decoupling capacitors close as possible to parts they are decoupling and it doesn't seem to cause any problems.

The 6-pin header in the top left of the picture is being used to program and power the circuit with a [AVR-ISP-MK2](https://www.olimex.com/Products/AVR/Programmers/AVR-ISP-MK2/open-source-hardware) programmer.

![The prototype board](/images/car_battery_logger_prototype.jpg)

The wiring is a bit of a mess, but at the speed the signals are going (low), the added capacitance and inductance introduced will not be a problem.

This prototype was good enough to prove the design and write most of the firmware.
