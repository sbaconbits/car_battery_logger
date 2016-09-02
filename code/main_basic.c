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
// File Name: main_basic.c
//
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <avr/wdt.h>
#include <inttypes.h>

#include "serial.h"

//PB1 flash CS#
//ina226 alert PC3


// /usr/lib/avr/include/avr

//      Atmega328p pinout
//          ---------
//      PC6 | 1   28| PC5
//  RXD PD0 | 2   27| PC4
//  TXD PD1 | 3   26| PC3
//      PD2 | 4   25| PC2
//      PD3 | 5   24| PC1
//      PD4 | 6   23| PC0
//      VCC | 7   22| GND
//      GND | 8   21| AREF
//      PB6 | 9   20| AVCC
//      PB7 |10   19| PB5   (SCK  - spi clock)
//      PD5 |11   18| PB4   (MISO - SPI master input / slave output)
//      PD6 |12   17| PB3   (MOSI - SPI master output / slave input)
//      PD7 |13   16| PB2   (SS   - SPI slave select)
//      PB0 |14   15| PB1   SPI_FLASH_N_CS
//          ---------

void init(void)
{
    //TODO hw_init()

    PORTB = 0x00;
    // PB0, PB1 output
    DDRB |= (1 << DDB0);
    DDRB |= (1 << DDB1);

    // PC5 output
    DDRC |= (1 << DDC5);

    // PD6 output
    DDRD |= (1 << DDD6);

    // PD7 input
    DDRD &= ~(1 << DDD7);

    //Clock prescale register
    CLKPR = 0x0; //clk_io = F_CPU (no scaling)


}

#define LED_ACT_ON          (PORTB |=  (1 << PB0))
#define LED_ACT_OFF         (PORTB &= ~(1 << PB0))
#define LED_ACT_TOGGLE      (PORTB ^=  (1 << PB0))

#define LED_TRG_ON          (PORTD |=  (1 << PD6))
#define LED_TRG_OFF         (PORTD &= ~(1 << PD6))
#define LED_TRG_TOGGLE      (PORTD ^=  (1 << PD6))

volatile uint32_t secs = 0;
ISR (TIMER2_OVF_vect, ISR_BLOCK)
{
    secs++;
    LED_TRG_TOGGLE;
    //LED_ACT_TOGGLE;
}

void rtc_init(void)
{
    // Crystal = 32.768KHz (pow(2,15)/sec)
    // pow(2,15) = pow(2,7) * pow(2,8)
    // 32768 = 128 * 256.

    // Timer 2

    // Asynchronous Timer/Counter2
    // Setting this can corrupt the following registers.
    ASSR = (1 << AS2);

    TCNT2  = 0;
    OCR2A  = 0;
    OCR2B  = 0;
    TCCR2A = 0;

    // mode normal
    // WGM2[2:0] = 000
    // CS2[2:0] = 101
    TCCR2B = (1 << CS22) | (1 << CS20);
    // Timer/Counter overflow interrupt enable
    TIMSK2 = (1 << TOIE2);

    sei(); // Enable interrupts
}

void main_loop(void)
{
    while(1)
    {
        _delay_ms(500);
        LED_ACT_ON;
        _delay_ms(500);
        LED_ACT_OFF;
        uart_hex_32(secs);
        uart_tx_str("\r\n");
    }
}

int main(void)
{
    init();
    uart_init();
    _delay_ms(1000);
    uart_tx_str("Start\r\n");
    rtc_init();
    main_loop();

    return 0;
}



