EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:car_battery_logger-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328P-A IC3
U 1 1 56DB3DEA
P 6350 2500
F 0 "IC3" H 5600 3750 50  0000 L BNN
F 1 "ATMEGA328P-A" H 6750 1100 50  0000 L BNN
F 2 "My footprints:TQFP-32_7x7mm_Pitch0.8mm_big_foot" H 6350 2500 50  0001 C CIN
F 3 "" H 6350 2500 50  0000 C CNN
	1    6350 2500
	1    0    0    -1  
$EndComp
$Comp
L ina226 IC1
U 1 1 56DB5C79
P 3500 2100
F 0 "IC1" H 3000 3150 60  0000 C CNN
F 1 "ina226" H 3500 1800 79  0000 C CNN
F 2 "My footprints:TSSOP-10_3x3mm_Pitch0.5mm_big_foot" H 3500 1800 60  0001 C CNN
F 3 "" H 3500 1800 60  0000 C CNN
	1    3500 2100
	1    0    0    -1  
$EndComp
$Comp
L S25FL064P IC2
U 1 1 56DC4042
P 5100 7000
F 0 "IC2" H 4550 8050 60  0000 C CNN
F 1 "S25FL064P" H 5150 7100 60  0000 C CNN
F 2 "My footprints:SOC008_5.3x5.3mm_Pitch1.27mm_big_foot" H 5150 7100 60  0001 C CNN
F 3 "" H 5150 7100 60  0000 C CNN
	1    5100 7000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 56DC464E
P 2750 2250
F 0 "#PWR6" H 2750 2000 50  0001 C CNN
F 1 "GND" H 2750 2100 50  0000 C CNN
F 2 "" H 2750 2250 50  0000 C CNN
F 3 "" H 2750 2250 50  0000 C CNN
	1    2750 2250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR9
U 1 1 56DC4888
P 3950 850
F 0 "#PWR9" H 3950 700 50  0001 C CNN
F 1 "+3.3V" H 3950 990 50  0000 C CNN
F 2 "" H 3950 850 50  0000 C CNN
F 3 "" H 3950 850 50  0000 C CNN
	1    3950 850 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR16
U 1 1 56DC48F6
P 5150 1250
F 0 "#PWR16" H 5150 1100 50  0001 C CNN
F 1 "+3.3V" H 5150 1390 50  0000 C CNN
F 2 "" H 5150 1250 50  0000 C CNN
F 3 "" H 5150 1250 50  0000 C CNN
	1    5150 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 56DC495C
P 5200 3750
F 0 "#PWR18" H 5200 3500 50  0001 C CNN
F 1 "GND" H 5200 3600 50  0000 C CNN
F 2 "" H 5200 3750 50  0000 C CNN
F 3 "" H 5200 3750 50  0000 C CNN
	1    5200 3750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR14
U 1 1 56DC4BD9
P 4850 5650
F 0 "#PWR14" H 4850 5500 50  0001 C CNN
F 1 "+3.3V" H 4850 5790 50  0000 C CNN
F 2 "" H 4850 5650 50  0000 C CNN
F 3 "" H 4850 5650 50  0000 C CNN
	1    4850 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 56DC4C1F
P 4850 7000
F 0 "#PWR15" H 4850 6750 50  0001 C CNN
F 1 "GND" H 4850 6850 50  0000 C CNN
F 2 "" H 4850 7000 50  0000 C CNN
F 3 "" H 4850 7000 50  0000 C CNN
	1    4850 7000
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 56DC4C47
P 5150 5700
F 0 "C5" H 5175 5800 50  0000 L CNN
F 1 "100nF" H 5175 5600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5188 5550 50  0001 C CNN
F 3 "" H 5150 5700 50  0000 C CNN
	1    5150 5700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR19
U 1 1 56DC5030
P 5450 5700
F 0 "#PWR19" H 5450 5450 50  0001 C CNN
F 1 "GND" H 5450 5550 50  0000 C CNN
F 2 "" H 5450 5700 50  0000 C CNN
F 3 "" H 5450 5700 50  0000 C CNN
	1    5450 5700
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 56DC53E2
P 5150 1950
F 0 "C4" H 5175 2050 50  0000 L CNN
F 1 "100nF" H 5175 1850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5188 1800 50  0001 C CNN
F 3 "" H 5150 1950 50  0000 C CNN
	1    5150 1950
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 56DC5F69
P 8500 3950
F 0 "R16" V 8580 3950 50  0000 C CNN
F 1 "10K" V 8500 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8430 3950 50  0001 C CNN
F 3 "" H 8500 3950 50  0000 C CNN
	1    8500 3950
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 56DC6091
P 8800 3950
F 0 "R18" V 8880 3950 50  0000 C CNN
F 1 "10K" V 8800 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8730 3950 50  0001 C CNN
F 3 "" H 8800 3950 50  0000 C CNN
	1    8800 3950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR21
U 1 1 56DC6198
P 8500 3700
F 0 "#PWR21" H 8500 3550 50  0001 C CNN
F 1 "+3.3V" H 8500 3840 50  0000 C CNN
F 2 "" H 8500 3700 50  0000 C CNN
F 3 "" H 8500 3700 50  0000 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR22
U 1 1 56DC61CA
P 8800 3700
F 0 "#PWR22" H 8800 3550 50  0001 C CNN
F 1 "+3.3V" H 8800 3840 50  0000 C CNN
F 2 "" H 8800 3700 50  0000 C CNN
F 3 "" H 8800 3700 50  0000 C CNN
	1    8800 3700
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 56DC633B
P 4500 1100
F 0 "C2" H 4525 1200 50  0000 L CNN
F 1 "100nF" H 4525 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4538 950 50  0001 C CNN
F 3 "" H 4500 1100 50  0000 C CNN
	1    4500 1100
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR12
U 1 1 56DC646D
P 4500 1300
F 0 "#PWR12" H 4500 1050 50  0001 C CNN
F 1 "GND" H 4500 1150 50  0000 C CNN
F 2 "" H 4500 1300 50  0000 C CNN
F 3 "" H 4500 1300 50  0000 C CNN
	1    4500 1300
	1    0    0    -1  
$EndComp
Entry Wire Line
	7800 1500 7900 1600
Entry Wire Line
	7800 1700 7900 1800
Entry Wire Line
	7800 1800 7900 1900
Entry Wire Line
	7800 1900 7900 2000
Entry Wire Line
	5650 5300 5750 5200
Text Label 7450 1900 0    39   ~ 0
SPI_CLK
Text Label 7450 1800 0    39   ~ 0
SPI_MISO
Text Label 7450 1700 0    39   ~ 0
SPI_MOSI
Text Label 7450 1500 0    39   ~ 0
SPI_CS0
Text Label 3650 5600 3    39   ~ 0
SPI_MOSI
Text Label 3400 5850 1    39   ~ 0
SPI_CLK
Text Label 3200 5850 1    39   ~ 0
SPI_CS0
Text Label 5650 5600 1    39   ~ 0
SPI_MISO
$Comp
L AVR-ISP-6 CON1
U 1 1 56DC5DDE
P 10200 1950
F 0 "CON1" H 10095 2190 50  0000 C CNN
F 1 "AVR-ISP-6" H 9935 1720 50  0000 L BNN
F 2 "My footprints:AVR_ISP_HEADER_6PIN" H 10200 1650 50  0001 C CNN
F 3 "" H 10175 1950 50  0000 C CNN
	1    10200 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR29
U 1 1 57276EAD
P 10050 5750
F 0 "#PWR29" H 10050 5500 50  0001 C CNN
F 1 "GND" H 10050 5600 50  0000 C CNN
F 2 "" H 10050 5750 50  0000 C CNN
F 3 "" H 10050 5750 50  0000 C CNN
	1    10050 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR24
U 1 1 57276EE5
P 8800 5750
F 0 "#PWR24" H 8800 5500 50  0001 C CNN
F 1 "GND" H 8800 5600 50  0000 C CNN
F 2 "" H 8800 5750 50  0000 C CNN
F 3 "" H 8800 5750 50  0000 C CNN
	1    8800 5750
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 57277135
P 10450 5300
F 0 "C10" H 10475 5400 50  0000 L CNN
F 1 "100nF" H 10475 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10488 5150 50  0001 C CNN
F 3 "" H 10450 5300 50  0000 C CNN
	1    10450 5300
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5727620A
P 2700 3550
F 0 "D1" H 2700 3650 50  0000 C CNN
F 1 "LED" H 2700 3450 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 2700 3350 50  0001 C CNN
F 3 "" H 2700 3550 50  0000 C CNN
	1    2700 3550
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 572762AD
P 2700 4650
F 0 "D2" H 2700 4750 50  0000 C CNN
F 1 "LED" H 2700 4550 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 2700 4450 50  0001 C CNN
F 3 "" H 2700 4650 50  0000 C CNN
	1    2700 4650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 572763A6
P 2550 3150
F 0 "SW1" H 2700 3260 50  0000 C CNN
F 1 "START/STOP" H 2550 3070 50  0000 C CNN
F 2 "My footprints:Button_connector" H 2550 3000 50  0001 C CNN
F 3 "" H 2550 3150 50  0000 C CNN
	1    2550 3150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 5727640B
P 2550 4250
F 0 "SW2" H 2700 4360 50  0000 C CNN
F 1 "RESET" H 2550 4170 50  0000 C CNN
F 2 "My footprints:Button_connector" H 2600 4100 50  0001 C CNN
F 3 "" H 2550 4250 50  0000 C CNN
	1    2550 4250
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y1
U 1 1 57276668
P 8650 1650
F 0 "Y1" H 8650 1500 50  0000 C CNN
F 1 "32.768KHz" V 8450 1650 50  0000 C CNN
F 2 "Crystals:Crystal_Round_Horizontal_2mm" H 8650 1900 50  0001 C CNN
F 3 "" H 8650 1650 50  0000 C CNN
	1    8650 1650
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 57277533
P 10200 3100
F 0 "P2" H 10200 3300 50  0000 C CNN
F 1 "Serial TTL" V 10300 3100 50  0000 C CNN
F 2 "My footprints:Serial_header" H 10200 2850 50  0001 C CNN
F 3 "" H 10200 3100 50  0000 C CNN
	1    10200 3100
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 572CCB56
P 8300 5300
F 0 "C6" H 8325 5400 50  0000 L CNN
F 1 "10uF" H 8325 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 8338 5150 50  0001 C CNN
F 3 "" H 8300 5300 50  0000 C CNN
	1    8300 5300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 572CD25D
P 2050 1500
F 0 "R2" V 2130 1500 50  0000 C CNN
F 1 "0" V 2050 1500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1980 1500 50  0001 C CNN
F 3 "" H 2050 1500 50  0000 C CNN
	1    2050 1500
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 572CD2E2
P 2050 1800
F 0 "R3" V 2130 1800 50  0000 C CNN
F 1 "0" V 2050 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1980 1800 50  0001 C CNN
F 3 "" H 2050 1800 50  0000 C CNN
	1    2050 1800
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 572CD3E0
P 2300 1650
F 0 "C1" H 2325 1750 50  0000 L CNN
F 1 "0" H 2325 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2338 1500 50  0001 C CNN
F 3 "" H 2300 1650 50  0000 C CNN
	1    2300 1650
	1    0    0    -1  
$EndComp
Text Notes 10100 5750 0    60   ~ 0
Make Inhibit modifiable\non board (loop it out)\n
Text Notes 9200 4650 0    60   ~ 0
Extra caps on output\njust in case\n
Text Notes 1750 2050 0    60   ~ 0
Filtering optional
$Comp
L +12V #PWR1
U 1 1 572CF1CC
P 1900 1100
F 0 "#PWR1" H 1900 950 50  0001 C CNN
F 1 "+12V" H 1900 1240 50  0000 C CNN
F 2 "" H 1900 1100 50  0000 C CNN
F 3 "" H 1900 1100 50  0000 C CNN
	1    1900 1100
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR30
U 1 1 572CF87F
P 10450 5000
F 0 "#PWR30" H 10450 4850 50  0001 C CNN
F 1 "+12V" H 10450 5140 50  0000 C CNN
F 2 "" H 10450 5000 50  0000 C CNN
F 3 "" H 10450 5000 50  0000 C CNN
	1    10450 5000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR23
U 1 1 572CF9A9
P 8800 4700
F 0 "#PWR23" H 8800 4550 50  0001 C CNN
F 1 "+3.3V" H 8800 4840 50  0000 C CNN
F 2 "" H 8800 4700 50  0000 C CNN
F 3 "" H 8800 4700 50  0000 C CNN
	1    8800 4700
	1    0    0    -1  
$EndComp
Entry Wire Line
	8200 1400 8300 1500
Entry Wire Line
	8200 3500 8300 3600
Entry Wire Line
	8200 3600 8300 3700
Entry Wire Line
	8200 3700 8300 3800
Entry Wire Line
	3400 3150 3500 3250
Entry Wire Line
	3400 3550 3500 3650
Entry Wire Line
	3400 4250 3500 4350
Entry Wire Line
	3400 4650 3500 4750
Text Label 7950 1400 0    39   ~ 0
LED_ACT
Text Label 7550 3500 0    39   ~ 0
BUT_RST
Text Label 7550 3600 0    39   ~ 0
LED_TRIG
Text Label 7550 3700 0    39   ~ 0
BUT_START
Text Label 3200 3150 0    39   ~ 0
BUT_START
Text Label 3200 4250 0    39   ~ 0
BUT_RST
Text Label 3200 3550 0    39   ~ 0
LED_ACT
Text Label 3200 4650 0    39   ~ 0
LED_TRIG
$Comp
L R R6
U 1 1 572D8605
P 2900 3000
F 0 "R6" V 2980 3000 50  0000 C CNN
F 1 "10K" V 2900 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 3000 50  0001 C CNN
F 3 "" H 2900 3000 50  0000 C CNN
	1    2900 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 572D86C2
P 2200 3200
F 0 "#PWR4" H 2200 2950 50  0001 C CNN
F 1 "GND" H 2200 3050 50  0000 C CNN
F 2 "" H 2200 3200 50  0000 C CNN
F 3 "" H 2200 3200 50  0000 C CNN
	1    2200 3200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR7
U 1 1 572D87C6
P 2900 2800
F 0 "#PWR7" H 2900 2650 50  0001 C CNN
F 1 "+3.3V" H 2900 2940 50  0000 C CNN
F 2 "" H 2900 2800 50  0000 C CNN
F 3 "" H 2900 2800 50  0000 C CNN
	1    2900 2800
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 572D8AA5
P 2300 3550
F 0 "R4" V 2380 3550 50  0000 C CNN
F 1 "150" V 2300 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2230 3550 50  0001 C CNN
F 3 "" H 2300 3550 50  0000 C CNN
	1    2300 3550
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 572D8BD7
P 2900 4100
F 0 "R7" V 2980 4100 50  0000 C CNN
F 1 "10K" V 2900 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 4100 50  0001 C CNN
F 3 "" H 2900 4100 50  0000 C CNN
	1    2900 4100
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 572D8C7A
P 2300 4650
F 0 "R5" V 2380 4650 50  0000 C CNN
F 1 "150" V 2300 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2230 4650 50  0001 C CNN
F 3 "" H 2300 4650 50  0000 C CNN
	1    2300 4650
	0    1    1    0   
$EndComp
$Comp
L GND #PWR2
U 1 1 572D8D10
P 2100 3600
F 0 "#PWR2" H 2100 3350 50  0001 C CNN
F 1 "GND" H 2100 3450 50  0000 C CNN
F 2 "" H 2100 3600 50  0000 C CNN
F 3 "" H 2100 3600 50  0000 C CNN
	1    2100 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 572D8D75
P 2200 4300
F 0 "#PWR5" H 2200 4050 50  0001 C CNN
F 1 "GND" H 2200 4150 50  0000 C CNN
F 2 "" H 2200 4300 50  0000 C CNN
F 3 "" H 2200 4300 50  0000 C CNN
	1    2200 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 572D8DDA
P 2100 4700
F 0 "#PWR3" H 2100 4450 50  0001 C CNN
F 1 "GND" H 2100 4550 50  0000 C CNN
F 2 "" H 2100 4700 50  0000 C CNN
F 3 "" H 2100 4700 50  0000 C CNN
	1    2100 4700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR8
U 1 1 572D8E3F
P 2900 3900
F 0 "#PWR8" H 2900 3750 50  0001 C CNN
F 1 "+3.3V" H 2900 4040 50  0000 C CNN
F 2 "" H 2900 3900 50  0000 C CNN
F 3 "" H 2900 3900 50  0000 C CNN
	1    2900 3900
	1    0    0    -1  
$EndComp
Text Notes 10150 2800 0    39   ~ 0
1=B, 2=Y, 3=0
$Comp
L GND #PWR28
U 1 1 572DEA7B
P 9900 2950
F 0 "#PWR28" H 9900 2700 50  0001 C CNN
F 1 "GND" H 9900 2800 50  0000 C CNN
F 2 "" H 9900 2950 50  0000 C CNN
F 3 "" H 9900 2950 50  0000 C CNN
	1    9900 2950
	-1   0    0    1   
$EndComp
Entry Wire Line
	7800 2850 7900 2950
Text Label 7450 2850 0    39   ~ 0
nRESET
Entry Wire Line
	9450 1750 9550 1850
Entry Wire Line
	9450 1850 9550 1950
Entry Wire Line
	9450 1950 9550 2050
Entry Wire Line
	10750 1950 10850 2050
$Comp
L GND #PWR31
U 1 1 572E0705
P 10500 2200
F 0 "#PWR31" H 10500 1950 50  0001 C CNN
F 1 "GND" H 10500 2050 50  0000 C CNN
F 2 "" H 10500 2200 50  0000 C CNN
F 3 "" H 10500 2200 50  0000 C CNN
	1    10500 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR33
U 1 1 572E0785
P 10650 1800
F 0 "#PWR33" H 10650 1650 50  0001 C CNN
F 1 "+3.3V" H 10650 1940 50  0000 C CNN
F 2 "" H 10650 1800 50  0000 C CNN
F 3 "" H 10650 1800 50  0000 C CNN
	1    10650 1800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR10
U 1 1 572DF02F
P 4300 1550
F 0 "#PWR10" H 4300 1400 50  0001 C CNN
F 1 "+3.3V" H 4300 1690 50  0000 C CNN
F 2 "" H 4300 1550 50  0000 C CNN
F 3 "" H 4300 1550 50  0000 C CNN
	1    4300 1550
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 572DF079
P 4300 1750
F 0 "R11" V 4380 1750 50  0000 C CNN
F 1 "10K" V 4300 1750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4230 1750 50  0001 C CNN
F 3 "" H 4300 1750 50  0000 C CNN
	1    4300 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 572DF68B
P 4400 2300
F 0 "#PWR11" H 4400 2050 50  0001 C CNN
F 1 "GND" H 4400 2150 50  0000 C CNN
F 2 "" H 4400 2300 50  0000 C CNN
F 3 "" H 4400 2300 50  0000 C CNN
	1    4400 2300
	1    0    0    -1  
$EndComp
NoConn ~ 5450 2000
NoConn ~ 5450 2750
NoConn ~ 5450 2850
NoConn ~ 7350 1600
NoConn ~ 7350 2250
NoConn ~ 7350 2350
NoConn ~ 7350 2450
$Comp
L R R15
U 1 1 572E0C0E
P 7750 1100
F 0 "R15" V 7830 1100 50  0000 C CNN
F 1 "10K" V 7750 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7680 1100 50  0001 C CNN
F 3 "" H 7750 1100 50  0000 C CNN
	1    7750 1100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR20
U 1 1 572E0E26
P 7750 900
F 0 "#PWR20" H 7750 750 50  0001 C CNN
F 1 "+3.3V" H 7750 1040 50  0000 C CNN
F 2 "" H 7750 900 50  0000 C CNN
F 3 "" H 7750 900 50  0000 C CNN
	1    7750 900 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR27
U 1 1 572E11CB
P 9350 1300
F 0 "#PWR27" H 9350 1150 50  0001 C CNN
F 1 "+3.3V" H 9350 1440 50  0000 C CNN
F 2 "" H 9350 1300 50  0000 C CNN
F 3 "" H 9350 1300 50  0000 C CNN
	1    9350 1300
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 572E1219
P 9350 1500
F 0 "R21" V 9430 1500 50  0000 C CNN
F 1 "10K" V 9350 1500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9280 1500 50  0001 C CNN
F 3 "" H 9350 1500 50  0000 C CNN
	1    9350 1500
	1    0    0    -1  
$EndComp
NoConn ~ 4250 6550
NoConn ~ 4250 6700
$Comp
L L4931CD33-TR IC4
U 1 1 5727668C
P 9500 5700
F 0 "IC4" H 9450 6450 60  0000 C CNN
F 1 "L4931CD33-TR" H 9450 5750 60  0000 C CNN
F 2 "My footprints:SOIC-8_3.9x4.9mm_Pitch1.27mm_big_foot" H 9550 5700 60  0001 C CNN
F 3 "" H 9550 5700 60  0000 C CNN
	1    9500 5700
	1    0    0    -1  
$EndComp
Text Label 9550 1850 0    39   ~ 0
SPI_MISO
Text Label 9550 1950 0    39   ~ 0
SPI_CLK
Text Label 9550 2050 0    39   ~ 0
nRESET
Text Label 10700 1950 0    39   ~ 0
SPI_MOSI
$Comp
L GND #PWR17
U 1 1 572E431E
P 5150 2200
F 0 "#PWR17" H 5150 1950 50  0001 C CNN
F 1 "GND" H 5150 2050 50  0000 C CNN
F 2 "" H 5150 2200 50  0000 C CNN
F 3 "" H 5150 2200 50  0000 C CNN
	1    5150 2200
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG1
U 1 1 572E693D
P 7950 5700
F 0 "#FLG1" H 7950 5795 50  0001 C CNN
F 1 "PWR_FLAG" H 7950 5880 50  0000 C CNN
F 2 "" H 7950 5700 50  0000 C CNN
F 3 "" H 7950 5700 50  0000 C CNN
	1    7950 5700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 576ED886
P 1500 1650
F 0 "R1" V 1580 1650 50  0000 C CNN
F 1 "0.01" V 1500 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 1430 1650 50  0001 C CNN
F 3 "" H 1500 1650 50  0000 C CNN
	1    1500 1650
	-1   0    0    1   
$EndComp
$Comp
L R R12
U 1 1 576EDC75
P 5650 4200
F 0 "R12" V 5730 4200 50  0000 C CNN
F 1 "0" V 5650 4200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5580 4200 50  0001 C CNN
F 3 "" H 5650 4200 50  0000 C CNN
	1    5650 4200
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 576EDD66
P 6150 4300
F 0 "R14" V 6230 4300 50  0000 C CNN
F 1 "0" V 6150 4300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6080 4300 50  0001 C CNN
F 3 "" H 6150 4300 50  0000 C CNN
	1    6150 4300
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 576EDE76
P 3550 6250
F 0 "R8" V 3630 6250 50  0000 C CNN
F 1 "0" V 3550 6250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 6250 50  0001 C CNN
F 3 "" H 3550 6250 50  0000 C CNN
	1    3550 6250
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 576EE0D6
P 3800 6100
F 0 "R9" V 3880 6100 50  0000 C CNN
F 1 "0" V 3800 6100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3730 6100 50  0001 C CNN
F 3 "" H 3800 6100 50  0000 C CNN
	1    3800 6100
	0    -1   -1   0   
$EndComp
$Comp
L R R10
U 1 1 576EE1D5
P 3800 6400
F 0 "R10" V 3880 6400 50  0000 C CNN
F 1 "0" V 3800 6400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3730 6400 50  0001 C CNN
F 3 "" H 3800 6400 50  0000 C CNN
	1    3800 6400
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 576EE27D
P 5650 5800
F 0 "R13" V 5730 5800 50  0000 C CNN
F 1 "0" V 5650 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5580 5800 50  0001 C CNN
F 3 "" H 5650 5800 50  0000 C CNN
	1    5650 5800
	-1   0    0    1   
$EndComp
$Comp
L C C8
U 1 1 576EE7B4
P 9000 1400
F 0 "C8" H 9025 1500 50  0000 L CNN
F 1 "100nF" H 9025 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9038 1250 50  0001 C CNN
F 3 "" H 9000 1400 50  0000 C CNN
	1    9000 1400
	0    1    1    0   
$EndComp
$Comp
L C C9
U 1 1 576EE938
P 9000 1900
F 0 "C9" H 9025 2000 50  0000 L CNN
F 1 "100nF" H 9025 1800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9038 1750 50  0001 C CNN
F 3 "" H 9000 1900 50  0000 C CNN
	1    9000 1900
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 576EF962
P 8800 4900
F 0 "R19" V 8880 4900 50  0000 C CNN
F 1 "0" V 8800 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8730 4900 50  0001 C CNN
F 3 "" H 8800 4900 50  0000 C CNN
	1    8800 4900
	-1   0    0    1   
$EndComp
$Comp
L D D3
U 1 1 576EFD55
P 10150 5150
F 0 "D3" H 10150 5365 50  0000 C CNN
F 1 "D" H 10150 5274 50  0000 C CNN
F 2 "Diodes_SMD:SMA_Handsoldering" H 10150 5273 50  0001 C CNN
F 3 "" H 10150 5150 50  0000 C CNN
	1    10150 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR25
U 1 1 576F1427
P 9150 1500
F 0 "#PWR25" H 9150 1250 50  0001 C CNN
F 1 "GND" H 9150 1350 50  0000 C CNN
F 2 "" H 9150 1500 50  0000 C CNN
F 3 "" H 9150 1500 50  0000 C CNN
	1    9150 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 576F14B0
P 9150 2000
F 0 "#PWR26" H 9150 1750 50  0001 C CNN
F 1 "GND" H 9150 1850 50  0000 C CNN
F 2 "" H 9150 2000 50  0000 C CNN
F 3 "" H 9150 2000 50  0000 C CNN
	1    9150 2000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P1
U 1 1 572CDEFC
P 700 1650
F 0 "P1" H 700 1900 50  0000 C CNN
F 1 "Sense input" V 800 1650 50  0000 C CNN
F 2 "My footprints:GPIO_header_1x4" H 700 1650 50  0001 C CNN
F 3 "" H 700 1650 50  0000 C CNN
	1    700  1650
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 576EE6C7
P 4850 1650
F 0 "C3" H 4875 1750 50  0000 L CNN
F 1 "100nF" H 4875 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4888 1500 50  0001 C CNN
F 3 "" H 4850 1650 50  0000 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 576F3A24
P 4850 1900
F 0 "#PWR13" H 4850 1650 50  0001 C CNN
F 1 "GND" H 4850 1750 50  0000 C CNN
F 2 "" H 4850 1900 50  0000 C CNN
F 3 "" H 4850 1900 50  0000 C CNN
	1    4850 1900
	1    0    0    -1  
$EndComp
Entry Wire Line
	3550 5200 3650 5300
Entry Wire Line
	3300 5200 3400 5300
Entry Wire Line
	3100 5200 3200 5300
$Comp
L R R17
U 1 1 576F73EA
P 8700 3000
F 0 "R17" V 8780 3000 50  0000 C CNN
F 1 "1K" V 8700 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8630 3000 50  0001 C CNN
F 3 "" H 8700 3000 50  0000 C CNN
	1    8700 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 1400 5450 1400
Wire Wire Line
	5300 5700 5450 5700
Wire Wire Line
	4850 5650 4850 5800
Wire Wire Line
	5000 5700 4850 5700
Connection ~ 4850 5700
Wire Wire Line
	7350 1500 7800 1500
Wire Wire Line
	7800 1700 7350 1700
Wire Wire Line
	7800 1800 7350 1800
Wire Wire Line
	7800 1900 7350 1900
Wire Wire Line
	5500 6100 5650 6100
Wire Bus Line
	7900 5200 7900 1500
Wire Bus Line
	3100 5200 7900 5200
Wire Wire Line
	9950 5250 9950 5350
Wire Wire Line
	8950 5250 8950 5350
Wire Wire Line
	8800 5350 8800 5750
Wire Wire Line
	8950 5350 8800 5350
Wire Wire Line
	9950 5350 10050 5350
Wire Wire Line
	10050 5350 10050 5750
Wire Wire Line
	9950 5450 10050 5450
Connection ~ 10050 5450
Wire Wire Line
	8300 5150 8950 5150
Wire Wire Line
	8300 5450 8800 5450
Connection ~ 8800 5450
Wire Wire Line
	8150 2650 8150 4200
Wire Wire Line
	8050 2750 8050 4300
Wire Wire Line
	4000 4300 4000 1600
Wire Wire Line
	4100 4200 4100 1450
Wire Wire Line
	4100 1450 3900 1450
Wire Wire Line
	4000 1600 3900 1600
Wire Wire Line
	2200 1500 2750 1500
Wire Wire Line
	2200 1800 2750 1800
Wire Wire Line
	2750 1500 2750 1550
Connection ~ 2300 1500
Wire Wire Line
	2750 1800 2750 1700
Connection ~ 2300 1800
Wire Wire Line
	1050 1200 2750 1200
Wire Wire Line
	1050 2250 2750 2250
Wire Wire Line
	1900 1100 1900 1200
Connection ~ 1900 1200
Wire Wire Line
	8650 2100 7350 2100
Wire Wire Line
	8150 2650 7350 2650
Wire Wire Line
	8050 2750 7350 2750
Wire Wire Line
	8500 4200 8500 4100
Wire Wire Line
	8800 4300 8800 4100
Wire Wire Line
	8500 3800 8500 3700
Wire Wire Line
	8800 3700 8800 3800
Wire Wire Line
	7350 1400 8200 1400
Wire Wire Line
	8200 3500 7350 3500
Wire Wire Line
	7350 3600 8200 3600
Wire Wire Line
	7350 3700 8200 3700
Wire Bus Line
	3500 4850 8300 4850
Wire Bus Line
	8300 4850 8300 1500
Wire Wire Line
	2900 2850 2900 2800
Wire Wire Line
	2250 3150 2200 3150
Wire Wire Line
	2200 3150 2200 3200
Wire Wire Line
	3400 3550 2900 3550
Wire Wire Line
	2500 3550 2450 3550
Wire Wire Line
	2150 3550 2100 3550
Wire Wire Line
	2100 3550 2100 3600
Wire Wire Line
	2900 3900 2900 3950
Wire Wire Line
	2850 4250 3400 4250
Connection ~ 2900 4250
Wire Wire Line
	2200 4300 2200 4250
Wire Wire Line
	2200 4250 2250 4250
Wire Wire Line
	2100 4700 2100 4650
Wire Wire Line
	2100 4650 2150 4650
Wire Wire Line
	2450 4650 2500 4650
Wire Wire Line
	2900 4650 3400 4650
Wire Wire Line
	2850 3150 3400 3150
Connection ~ 2900 3150
Wire Bus Line
	3500 3250 3500 4850
Wire Wire Line
	9650 3000 9650 3200
Wire Wire Line
	9650 3200 10000 3200
Wire Wire Line
	9900 2950 9900 3000
Wire Wire Line
	9900 3000 10000 3000
Wire Wire Line
	7800 2850 7350 2850
Wire Wire Line
	10300 1950 10750 1950
Wire Bus Line
	7900 2500 10850 2500
Wire Bus Line
	9450 1750 9450 2500
Wire Wire Line
	10300 2050 10500 2050
Wire Wire Line
	10500 2050 10500 2200
Wire Wire Line
	10650 1800 10650 1850
Wire Wire Line
	10650 1850 10300 1850
Wire Wire Line
	7350 2550 7400 2550
Wire Wire Line
	7400 2550 7400 1000
Wire Wire Line
	7400 1000 4650 1000
Wire Wire Line
	4650 1000 4650 1950
Wire Wire Line
	4650 1950 3900 1950
Wire Wire Line
	4300 1600 4300 1550
Wire Wire Line
	4300 1900 4300 1950
Connection ~ 4300 1950
Wire Wire Line
	3900 2100 4400 2100
Wire Wire Line
	4400 2100 4400 2300
Wire Wire Line
	3900 2250 4400 2250
Connection ~ 4400 2250
Wire Wire Line
	7750 1250 7750 1500
Connection ~ 7750 1500
Wire Wire Line
	7750 900  7750 950 
Wire Wire Line
	7350 3200 9450 3200
Wire Wire Line
	9450 3200 9450 3700
Wire Wire Line
	9450 3700 9900 3700
Wire Wire Line
	7350 3300 9350 3300
Wire Wire Line
	9350 3300 9350 3800
Wire Wire Line
	9350 3800 10100 3800
Wire Wire Line
	7350 3400 9250 3400
Wire Wire Line
	9250 3400 9250 3900
Wire Wire Line
	9250 3900 10300 3900
Wire Wire Line
	4850 1500 5450 1500
Wire Wire Line
	9550 1850 10050 1850
Wire Wire Line
	9550 1950 10050 1950
Wire Wire Line
	9550 2050 10050 2050
Wire Bus Line
	10850 2500 10850 2050
Wire Wire Line
	9350 1650 9350 2150
Wire Wire Line
	9350 2150 9600 2150
Wire Wire Line
	9600 2150 9600 2050
Connection ~ 9600 2050
Wire Wire Line
	9350 1300 9350 1350
Wire Wire Line
	7950 5700 8800 5700
Connection ~ 8800 5700
Wire Wire Line
	5200 3500 5200 3750
Wire Wire Line
	5450 3600 5200 3600
Connection ~ 5200 3600
Wire Wire Line
	5450 3700 5200 3700
Connection ~ 5200 3700
Wire Wire Line
	5450 3500 5200 3500
Wire Wire Line
	10450 5450 10450 5500
Wire Wire Line
	10450 5500 10050 5500
Connection ~ 10050 5500
Wire Wire Line
	9950 5150 10000 5150
Wire Wire Line
	10300 5150 10450 5150
Wire Wire Line
	10450 5150 10450 5000
Wire Wire Line
	8800 4700 8800 4750
Wire Wire Line
	8800 5050 8800 5150
Connection ~ 8800 5150
Wire Wire Line
	8400 1500 8400 2050
Wire Wire Line
	8400 1500 8650 1500
Wire Wire Line
	7350 2000 7600 2000
Wire Wire Line
	7600 2000 7600 2050
Wire Wire Line
	7600 2050 8400 2050
Wire Wire Line
	8650 1800 8650 2100
Wire Wire Line
	8650 1500 8650 1400
Wire Wire Line
	8650 1400 8850 1400
Wire Wire Line
	8650 1900 8850 1900
Connection ~ 8650 1900
Wire Wire Line
	9150 1400 9150 1500
Wire Wire Line
	9150 1900 9150 2000
Wire Wire Line
	5800 4200 8500 4200
Connection ~ 8150 4200
Wire Wire Line
	5500 4200 4100 4200
Wire Wire Line
	6300 4300 8800 4300
Connection ~ 8050 4300
Wire Wire Line
	6000 4300 4000 4300
Wire Wire Line
	1250 1500 1900 1500
Wire Wire Line
	1250 1800 1900 1800
Wire Wire Line
	1250 1500 1250 1600
Wire Wire Line
	1250 1600 900  1600
Connection ~ 1500 1500
Wire Wire Line
	900  1700 1250 1700
Wire Wire Line
	1250 1700 1250 1800
Connection ~ 1500 1800
Wire Wire Line
	1050 2250 1050 1800
Wire Wire Line
	1050 1800 900  1800
Wire Wire Line
	1050 1200 1050 1500
Wire Wire Line
	1050 1500 900  1500
Wire Wire Line
	5450 1700 5150 1700
Wire Wire Line
	5150 1250 5150 1800
Wire Wire Line
	5150 2100 5150 2200
Connection ~ 5150 1400
Connection ~ 5150 1500
Wire Wire Line
	4850 1800 4850 1900
Wire Wire Line
	3650 5300 3650 6100
Wire Wire Line
	3950 6100 4250 6100
Wire Wire Line
	3400 5300 3400 6250
Wire Wire Line
	3700 6250 4250 6250
Wire Wire Line
	3200 5300 3200 6400
Wire Wire Line
	3200 6400 3650 6400
Wire Wire Line
	3950 6400 4250 6400
Wire Wire Line
	5650 5300 5650 5650
Wire Wire Line
	5650 6100 5650 5950
Wire Wire Line
	7350 3000 8550 3000
Wire Wire Line
	8850 3000 9650 3000
$Comp
L R R20
U 1 1 576F7CF1
P 9100 3100
F 0 "R20" V 9180 3100 50  0000 C CNN
F 1 "1K" V 9100 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9030 3100 50  0001 C CNN
F 3 "" H 9100 3100 50  0000 C CNN
	1    9100 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 3100 8950 3100
Wire Wire Line
	9250 3100 10000 3100
$Comp
L CP_Small C7
U 1 1 576F87BF
P 8600 5300
F 0 "C7" H 8688 5346 50  0000 L CNN
F 1 "10uF" H 8688 5255 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L11_P2" H 8688 5209 50  0001 L CNN
F 3 "" H 8600 5300 50  0000 C CNN
	1    8600 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5150 8600 5200
Connection ~ 8600 5150
Wire Wire Line
	8600 5400 8600 5450
Connection ~ 8600 5450
Wire Wire Line
	4500 1250 4500 1300
Wire Wire Line
	4500 950  4500 900 
Wire Wire Line
	3900 1200 3950 1200
Wire Wire Line
	3950 1200 3950 850 
Wire Wire Line
	4500 900  3950 900 
Connection ~ 3950 900 
Connection ~ 5150 1700
$Comp
L PWR_FLAG #FLG2
U 1 1 576F2333
P 8550 4700
F 0 "#FLG2" H 8550 4795 50  0001 C CNN
F 1 "PWR_FLAG" H 8550 4924 50  0000 C CNN
F 2 "" H 8550 4700 50  0000 C CNN
F 3 "" H 8550 4700 50  0000 C CNN
	1    8550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4700 8800 4700
$Comp
L PWR_FLAG #FLG3
U 1 1 576F3227
P 10700 5000
F 0 "#FLG3" H 10700 5095 50  0001 C CNN
F 1 "PWR_FLAG" H 10700 5224 50  0000 C CNN
F 2 "" H 10700 5000 50  0000 C CNN
F 3 "" H 10700 5000 50  0000 C CNN
	1    10700 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 5000 10700 5000
$Comp
L R R24
U 1 1 576FF072
P 10100 3500
F 0 "R24" V 10180 3500 50  0000 C CNN
F 1 "0" V 10100 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10030 3500 50  0001 C CNN
F 3 "" H 10100 3500 50  0000 C CNN
	1    10100 3500
	-1   0    0    1   
$EndComp
$Comp
L R R25
U 1 1 576FF155
P 10100 4100
F 0 "R25" V 10180 4100 50  0000 C CNN
F 1 "0" V 10100 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10030 4100 50  0001 C CNN
F 3 "" H 10100 4100 50  0000 C CNN
	1    10100 4100
	-1   0    0    1   
$EndComp
$Comp
L R R23
U 1 1 576FF871
P 9900 4100
F 0 "R23" V 9980 4100 50  0000 C CNN
F 1 "0" V 9900 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9830 4100 50  0001 C CNN
F 3 "" H 9900 4100 50  0000 C CNN
	1    9900 4100
	-1   0    0    1   
$EndComp
$Comp
L R R22
U 1 1 576FF918
P 9900 3500
F 0 "R22" V 9980 3500 50  0000 C CNN
F 1 "0" V 9900 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9830 3500 50  0001 C CNN
F 3 "" H 9900 3500 50  0000 C CNN
	1    9900 3500
	-1   0    0    1   
$EndComp
$Comp
L R R26
U 1 1 576FF9CA
P 10300 3500
F 0 "R26" V 10380 3500 50  0000 C CNN
F 1 "0" V 10300 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10230 3500 50  0001 C CNN
F 3 "" H 10300 3500 50  0000 C CNN
	1    10300 3500
	-1   0    0    1   
$EndComp
$Comp
L R R27
U 1 1 576FFAD1
P 10300 4100
F 0 "R27" V 10380 4100 50  0000 C CNN
F 1 "0" V 10300 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10230 4100 50  0001 C CNN
F 3 "" H 10300 4100 50  0000 C CNN
	1    10300 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	9900 3650 9900 3950
Wire Wire Line
	10100 3650 10100 3950
Wire Wire Line
	10300 3650 10300 3950
$Comp
L GND #PWR32
U 1 1 57700B9A
P 10550 4250
F 0 "#PWR32" H 10550 4000 50  0001 C CNN
F 1 "GND" H 10550 4100 50  0000 C CNN
F 2 "" H 10550 4250 50  0000 C CNN
F 3 "" H 10550 4250 50  0000 C CNN
	1    10550 4250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR34
U 1 1 57700C6D
P 10700 3350
F 0 "#PWR34" H 10700 3200 50  0001 C CNN
F 1 "+3.3V" H 10700 3490 50  0000 C CNN
F 2 "" H 10700 3350 50  0000 C CNN
F 3 "" H 10700 3350 50  0000 C CNN
	1    10700 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 3350 10700 3350
Connection ~ 10100 3350
Connection ~ 10300 3350
Wire Wire Line
	9900 4250 10550 4250
Connection ~ 10100 4250
Connection ~ 10300 4250
Connection ~ 9900 3700
Connection ~ 10100 3800
Connection ~ 10300 3900
$EndSCHEMATC
