#!/usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
import math
import re
import sys
import struct

FILE=sys.argv[1]

print "file:" + FILE

search_str_start="------- start of session print -------"
search_str_end="------- end of session print -------"
search_str_start_pos=0
search_str_end_pos=0
shunt_res=75.0E-3 / 10
vbus_v_LSB = 1.25E-3
vshunt_v_LSB = 2.5E-6

f = open(FILE, 'r')
# read the entire contents into a buffer
contents = f.readlines();

# remove some lines of debug from log
for index, line in enumerate(contents):
    if "Found smaller at addr" in line:
        del contents[index]

# find the start we are looking for
for index, line in enumerate(contents):
    if search_str_start in line:
        search_str_start_pos = index

# find the end we are looking for
for index, line in enumerate(contents):
    if search_str_end in line:
        search_str_end_pos = index

# did the search fail
if (search_str_start_pos == 0) or (search_str_end_pos == 0):
    print "failed to find start and/or end"
    f.close()
    quit()

# move to the start and end of data
search_str_start_pos += 1;
#search_str_end_pos -= 1;

print "Start pos: " + str(search_str_start_pos)
print "End pos: " + str(search_str_end_pos)
print "Count: " + str(search_str_end_pos - search_str_start_pos)

# create graph data
count_list = []
vbus_list = []
vshunt_list = []
current_list = []
power_list = []

for i in range(0, (search_str_end_pos - search_str_start_pos)):
    line = contents[search_str_start_pos + i]   #Get a line of data
    entries_hex = line.split(":")               #Split the string into two
    vbus_str = str(entries_hex[0])              #convert list entry to string
    vshunt_str = str(entries_hex[1]).rstrip()   #same and remove trailing white space
    vbus_num = struct.unpack(">h", vbus_str.decode('hex'))[0] #convert big endian hex string to value
    vshunt_num = struct.unpack(">h", vshunt_str.decode('hex'))[0]
    vbus_num = vbus_num * vbus_v_LSB            #scale
    vshunt_num = vshunt_num * vshunt_v_LSB      #scale
    #print "line " + str(line).rstrip()
    #print "vbus (" + vbus_str + ") " + str(vbus_num)
    #print "vshunt (" + vshunt_str + ")" + str(vshunt_num)
    count_list.append(i)
    vbus_list.append(vbus_num)
    vshunt_list.append(vshunt_num * 1000)       #Convert to millivolts
    current_list.append(vshunt_num/shunt_res)
    power_list.append((vshunt_num/shunt_res) * vbus_num)

#Get the graph data ready
x  = np.array(count_list)
y1 = np.array(vbus_list)
y2 = np.array(vshunt_list)
y3 = np.array(current_list)
y4 = np.array(power_list)

#Plot the graph data
plt.subplot(2,2,1)          #plot rows, plot cols, plot number
plt.plot(x, y1, 'b.-')
plt.ylabel("Bus Voltage (V)")
plt.xlabel("Seconds")
plt.grid(True)

plt.subplot(2,2,2)          #plot rows, plot cols, plot number
plt.plot(x, y2, 'b.-')
plt.ylabel("Shunt Voltage (mV)")
plt.xlabel("Seconds")
plt.grid(True)

plt.subplot(2,2,3)          #plot rows, plot cols, plot number
plt.plot(x, y3, 'r.-')
plt.ylabel("Current (A)")
plt.xlabel("Seconds")
plt.grid(True)

plt.subplot(2,2,4)          #plot rows, plot cols, plot number
plt.plot(x, y4, 'r.-')
plt.ylabel("Power (W)")
plt.xlabel("Seconds")
plt.grid(True)


plt.legend()
plt.show()

f.close()
