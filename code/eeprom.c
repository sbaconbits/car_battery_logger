// Copyright (c) 2016 Steven Bacon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// File Name: eeprom.c
//
#include <avr/io.h>
#include <avr/interrupt.h>

#include "eeprom.h"
#include "serial.h"
#include "utils.h"

// EEARH - EEPROM Address register high
// EEARL - EEPROM Address register low
// EEAR  - EEPROM Address register
// EEDR  - EEPROM Data register
// EECR  - EEPROM Control register

//TODO handle the watchdog in write/erase functions
//TODO add a timeout to this loop.
#define EEPROM_WAIT_READY while(EECR & (1 << EEPE)){}

uint8_t eeprom_dump(void)
{
    // 1-KB of EEPROM
    uint16_t addr=0;
    uint8_t i;

    cli(); // Clear global interrupt flags (disable)

    PRINT_CSTR("EEPROM Dump\r\n");
    do
    {
        uart_hex_16(addr);
        PRINT_CSTR(": ");
        for(i=0; i<16; i++)
        {
            // Set the address to read
            EEAR = addr;
            // Start the read
            EECR |= (1 << EERE);
            // Print EEPROM data read
            uart_hex_8(EEDR);
            PRINT_CSTR(" ");
            addr++;
        }
        PRINT_CSTR("\r\n");
    } while(addr < EEPROM_SIZE);

    sei(); // Global enable interrupts
    return 0;
}

uint8_t eeprom_erase(void)
{
    uint16_t addr=0;

    cli(); // Clear global interrupt flags (disable)

    do
    {
        // Wait for EEPE to clear
        EEPROM_WAIT_READY;
        // Set address to write to.
        EEAR = addr;
        // Set data to write.
        EEDR = 0xff;
        // EECR
        // - EEPM1:0 = 01 = Programming mode: erase only.
        // - EERIE   = 0  = Disable read interrupt
        // - EEMPE   = 1  = Master write enable  (may have to be done seperatley)
        // - EEPE    = 1  = Write enable
        // - EERE    = 0  = Read enable
        EECR = (1 << EEMPE) | (1 << EEPM0); // Setup
        EECR |= (1 << EEPE);                // Action (before 4 cycles after EEMPE)
        ++addr;
    } while(addr < EEPROM_SIZE);
    sei(); // Global enable interrupts
    return 0;
}

//TODO implement this
uint8_t eeprom_test_read(void)
{
    return 0;
}

uint8_t eeprom_test_write(void)
{
    uint16_t addr=0;
    uint8_t data=0;

    cli(); // Clear global interrupt flags (disable)

    do
    {
        // Wait for EEPE to clear
        EEPROM_WAIT_READY;
        // Set address to write to.
        EEAR = addr;
        // Set data to write.
        EEDR = data;
        // EECR
        // - EEPM1:0 = 00 = Programming mode: erase and write in one operation.
        // - EERIE   = 0  = Disable read interrupt
        // - EEMPE   = 1  = Master write enable  (may have to be done seperatley)
        // - EEPE    = 1  = Write enable
        // - EERE    = 0  = Read enable
        EECR = (1 << EEMPE);    // Setup
        EECR |= (1 << EEPE);    // Action (before 4 cycles after EEMPE)
        ++addr;
        ++data;
    } while(addr < EEPROM_SIZE);
    sei(); // Global enable interrupts
    return 0;
}



