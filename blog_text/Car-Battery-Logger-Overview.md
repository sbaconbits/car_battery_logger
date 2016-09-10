+++
date = "2016-08-20T15:26:52+01:00"
draft = true
title = "Overview"
tags = ["avr"]
categories = ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

This post outlines the problem i'm trying to solve and some basic requirements.
<!--more-->


# A new car with a problem
We bought a new (old) car, a Land Rover Discovery series II. The car had a few problems when it arrived, the most annoying of which was it's ability to flatten batteries. We assumed it was probably a bad battery as it was quite old so we replaced it, this didn't help.

I hooked up a multi-meter in line with the battery and measured the current being used, it did draw several amps when locking the doors, but then it dropped to the expected quiescent current of around 30mA after that. With this power usage level it should take over 100 days to drain the 100Ah battery, so why was it draining the battery in a couple of days?

I wanted to get to the root cause of this battery draining problem and this seemed like a perfect excuse for a project. I needed the ability to record the power consumption from the battery over a couple of days. The device would be even more useful if it could measure separate circuits in the car to narrow down the problem.


# The requirements
- Cheap, if I wanted something expensive I would have bought a current logger :)
- Simple to build and use.
- Easily accessible parts.
- Accuracy isn't very important as I want to find a "large" current draw.
- Sample rate can be relatively slow 10/sec should be fine.
- Must have local storage (I plan to leave this device attached in the engine bay).
- A minimal method of extracting the data once recorded.
- Low power consumption, the simplest way to power this device would be from the battery i'm measuring so I don't want effect the measurement too much.
