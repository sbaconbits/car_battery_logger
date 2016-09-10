+++
date = "2016-08-25T15:26:52+01:00"
draft = true
title = "Board assembly"
tags = ["avr"]
categories= ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

Building up the first and second board, this post also includes a list of all the components used (BOM) with links to Farnell (where I bought the components that I used).
<!--more-->

# Building the first board
The only part that I thought would be a bit tricky to solder with an iron was the INA226, but I found the massively extender pads helped with this a lot and any bridging was easily removed with flux. First I checked there were no shorts between vcc and ground on the board due to manufacturing problems and there weren't. Then I started to build the board up, testing each component one at a time, everything seemed to work fine.

I found the SMD Aluminium Electrolytic Capacitor really hard to put on the board with my soldering iron, it had trouble getting enough heat into the board to slide the capacitor on top, so I had two options for the next board either get a better soldering iron or change the component for one that could be placed on the board with a basic soldering iron. If in the future anyone else wants to build this board i'm assuming they may have tools as bad as mine so I changed the component :).

![V0.1 Board populated](/images/car_battery_logger_populated_board_v0.1.jpg)

# Building the second board
Was easier than building the first, but it took a bit longer as there were more components.
![V0.1 Board populated](/images/car_battery_logger_populated_board_v0.2.jpg)


# Bill Of Materials (BOM)
Here is the BOM for the components used on the final board and the farnell order codes I used when ordering.

| Part                  | Description                           | Farnell code|
| ----------------------|---------------------------------------|-------------|
| ATMEGA328P-AU         | 8 Bit Microcontroller                 | [1715486](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1715486) |
| INA226AIDGST          | Current Sense Amplifier               | [1924807](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1924807) |
| S25FL164K0XMFI011     | FLASH, 64MBIT                         | [2363323](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=2363323) |
| CFS206 32.768KDZB-UB  | CRYSTAL, WATCH, 32.768KHZ             | [1457085](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1457085) |
| L4931CD33-TR          | Fixed LDO Voltage Regulator           | [1094211](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1094211) |
| C0805C104K5RACTU      | Cap 0.1uF 50V                         | [1414664](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1414664) |
| ECA-1CM100            | Electrolytic Capacitor, M Series, 10 µF | [9693548](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=9693548) |
| CRCW0805150RFKEA      | Res 150R 1W                           | [1469877](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1469877) |
| CRCW080510K0JNEA      | Res 10K 125mW                         | [1469857](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1469857) |
| CRCW08050000Z0EA      | Res 0R 1W                             | [1469846](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1469846) |
| CRCW08051K00FKEA      | Res 1K 125mW                          | [1469847](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1469847) |
| LUMBERG  KLB 4        | Phone Audio Connector Chassis mount   | [1200144](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1200144) |
| LUMBERG  KLS 40       | Phone Audio Connector cable mount     | [1243266](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1243266) |
| Red Button            | Pushbutton Switch, SPST-NO            | [1634684](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1634684) |
| Black Button          | Pushbutton Switch, SPST-NO            | [1634682](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1634682) |
| CRM2512-FX-1R00ELF    | SMD Current Sense Resistor, CRM Series, 1 ohm | [2328172](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=2328172) |
| MULTICOMP  ES1A       | Fast / Ultrafast Diode, Single, 50 V, 1 A | [1625028](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?st=1625028) |




