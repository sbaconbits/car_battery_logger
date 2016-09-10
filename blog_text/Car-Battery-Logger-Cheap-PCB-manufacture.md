+++
date = "2016-08-24T15:26:52+01:00"
draft = true
title = "Cheap PCB Manufacture"
tags = ["avr"]
categories= ["car-battery-logger"]
banner = "banners/land_rover_low_battery.png"
+++

My experiences with a cheap board manufacturer, they look great, but the first one needed a tweak.
<!--more-->

# The board manufacturer
I've chosen to use [dirtypcbs](http://dirtypcbs.com/) the value for money at these places is amazing, making your own boards these days is so easy and cheap. I used to build all of my home project on [veroboard](https://en.wikipedia.org/wiki/Veroboard), which I think I will still use for some prototyping, but with the availability of these services and tools it makes a lot of sense to just make real PCB's. The only real down side of this service for me is that it took 3 weeks to get the boards back, but that could have been a lot faster if I was willing to pay for it.

# The first board back
I received 10 of these boards in the post, nicely wrapped in bubble wrap, they looked great! Once the board was populated everything seemed to work fine. The manufacturer added a job number to the bottom of the board, I was expecting this as it was mentioned on their site. As you can see the board has red soldermask which is the default (I forgot to select the one I wanted, but red was fine).
![V0.1 Bare board front](/images/car_battery_logger_v0.1_bare_board_front.jpg)
The back of the board is very minimal as expected.
![V0.1 Bare board back](/images/car_battery_logger_v0.1_bare_board_back.jpg)


# Solder mask alignment problem
As i've mentioned in my previous post the clearance that i'd left between pads and the copper pour was way too small, the result of this was that the small misalignment of the solder mask as seen in the diagram below could cause some problems. To correct this I just had to update my boards design rules for the next board.

![V0.1 Board solder mask alignment](/images/car_battery_logger_v0.1_solder_mask_misalignment.png)

It's not easy to see in this picture but the pad in the middle of the picture has a small bit of the copper pour to the right of it exposed, I could have easily bridged that with solder resulting in a short. This only appeared to be a problem on 2 out of the 10 boards I had made.

# The second board back
I'm much happier with this board and I really like the blue :). For me the writing in the copper pour hasn't really worked as there seems to be an offset around each letter, they loose their definition. Again the job number added by the manufacturer has been put in a sensible place.
![V0.2 Bare board front](/images/car_battery_logger_v0.2_bare_board_front.jpg)
And on the back there is only one optional component (the internal shunt resistor).
![V0.2 Bare board back](/images/car_battery_logger_v0.2_bare_board_back.jpg)
