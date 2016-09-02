CC=/usr/bin/avr-gcc
OBJCOPY=/usr/bin/avr-objcopy
ALL_FLAGS = -mmcu=atmega328p

C_DEFS = -DF_CPU=8000000UL

C_FLAGS = $(ALL_FLAGS)
C_FLAGS += -Os
C_FLAGS += -g -Wall -Werror
C_FLAGS += -Wno-unused-function
C_FLAGS += -Wa,-ahlms=$(<:.c=.lst)
C_FLAGS += $(C_DEFS)
#LD_FLAGS += -Wl,--verbose #To output the default linker script.
#LD_FLAGS += -Wl,-Map=main.map #Save a map file

#AVRDUDE = avrdude
AVRDUDE = /store/bin/avrdude-5.11/avrdude

all: main.hex size

.PHONY: version.c
version.c:
	@ echo "const char version_str[] PROGMEM =\"`date +%F-%H-%M-%S`\";" > version.c

logger_fs.o: logger_fs.c
	$(CC) $(C_FLAGS) -c logger_fs.c

eeprom.o: eeprom.c
	$(CC) $(C_FLAGS) -c eeprom.c

i2c.o: i2c.c
	$(CC) $(C_FLAGS) -c i2c.c

utils.o: utils.c
	$(CC) $(C_FLAGS) -c utils.c

serial.o: serial.c
	$(CC) $(C_FLAGS) -c serial.c

menu.o: menu.c
	$(CC) $(C_FLAGS) -c menu.c

flash_S25FL.o: flash_S25FL.c
	$(CC) $(C_FLAGS) -c flash_S25FL.c

pwr_meas.o: pwr_meas.c
	$(CC) $(C_FLAGS) -c pwr_meas.c

hw_io.o: hw_io.c
	$(CC) $(C_FLAGS) -c hw_io.c

ui.o: ui.c
	$(CC) $(C_FLAGS) -c ui.c

main.o: main.c version.c
	$(CC) $(C_FLAGS) -c main.c

main.elf: main.o serial.o menu.o hw_io.o flash_S25FL.o pwr_meas.o i2c.o utils.o eeprom.o logger_fs.o ui.o
	$(CC) $(ALL_FLAGS) $(LD_FLAGS) -o main.elf main.o serial.o menu.o hw_io.o flash_S25FL.o pwr_meas.o i2c.o utils.o eeprom.o logger_fs.o ui.o

main.hex: main.elf
	$(OBJCOPY) -j .text -j .data -O ihex main.elf main.hex

prog:
	$(AVRDUDE) -p m328p -c avrispmkII -P usb -U flash:w:main.hex -v

size:
	avr-size --format=avr --mcu=atmega328p main.elf

read_eeprom:
	$(AVRDUDE) -p m328p -c avrispmkII -P usb -U eeprom:r:eeprom.hex:r -v

# Fuse low byte:
# CKDIV8	7    1      No divide by 8
# CKOUT		6    1      No clock out
# SUT		5:4  10     Start up time set to max
# CKSEL		3:0  0010   Calibrated internal RC oscillator
# 1110 0010 = e2

fuse:
	$(AVRDUDE) -p m328p -c avrispmkII -P usb -U lfuse:w:0xe2:m -v

todo:
	@echo "Everything that needs to be fixed one day"
	@grep -n "TODO" *.c *.h

clean:
	rm -f *.elf *.hex *.lst *.o version.c *.map
 
###############################################################
main_basic.o: main_basic.c
	$(CC) $(C_FLAGS) -c main_basic.c

main_basic.elf: main_basic.o serial.o
	$(CC) $(ALL_FLAGS) -o main_basic.elf main_basic.o serial.o

main_basic.hex: main_basic.elf
	$(OBJCOPY) -j .text -j .data -O ihex main_basic.elf main_basic.hex

prog_basic:
	$(AVRDUDE) -p m328p -c avrispmkII -P usb -U flash:w:main_basic.hex -v


#look at sections.
#/usr/bin/avr-readelf -S main.elf

