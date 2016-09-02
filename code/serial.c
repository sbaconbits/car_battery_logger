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
// File Name: serial.c
//

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#include "serial.h"

//#define BAUD_RATE 9600UL
//#define BAUD_RATE 38400UL
#define BAUD_RATE 57600UL
//#define BAUD_RATE 115200UL

#ifndef F_CPU
#error "Need F_CPU defined"
#endif

#define DOUBLE_SPEED
#ifdef DOUBLE_SPEED
#define CLK_DIV (F_CPU / (8 * BAUD_RATE) - 1)
#else
#define CLK_DIV (F_CPU / (16 * BAUD_RATE) - 1)
#endif

//TODO Add timeout in waiting loops.
//TODO Common up the hex output strings.

void uart_init(void)
{
    // Uart 0
    // rate = F_CPU / (16 * baud) - 1
    //      = 8000000 / (16 * 9600) - 1 = 51.08
    //      = 8000000 / (16 * 38400) - 1 = 12.02
    //      = 8000000 / (16 * 57600 ) - 1 = 7.68
    //      = 8000000 / (16 * 115200) - 1 = 3.34        //rounding results in massive error
    //      = 20000000 / (16 * 9600) - 1 = 129.2
    //  bouble data rate
    //      python -c "print(8.0E6 / (8*57600)-1)"
    //          16.3611111111

    //UBRR0H = 0;
    //UBRR0L = 129;
    UBRR0 = CLK_DIV;
#ifdef DOUBLE_SPEED
    UCSR0A |= (1 << U2X0);
#endif
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Enable Tx and Rx
    // Async USART, no parity, 1 stop bit, 8-bit data
    UCSR0C =  (1 << UCSZ00) | (1 << UCSZ01); //00 00 0 11 0
}

void uart_tx(uint8_t c)
{
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
}

#ifdef SERIAL_DEBUG
static uint8_t stat_frame_err    = 0;
static uint8_t stat_data_overrun = 0;
static uint8_t stat_parity_check = 0;
#endif //SERIAL_DEBUG

#ifdef SERIAL_DEBUG
void check_rx_errors(void)
{
    //All of the following are reset on the next receive buffer read.
    //UCSR0A FE0 - Frame Error on receive (set on error)
    if(UCSR0A & (1 << FE0))
        stat_frame_err++;
    //UCSR0A DOR0 - Data OverRun on receive (set on overrun)
    if(UCSR0A & (1 << DOR0))
        stat_data_overrun++;
    //UCSR0A UPE0 - Parity check (set on parity error)
    if(UCSR0A & (1 << UPE0))
        stat_parity_check++;
}
#endif //SERIAL_DEBUG

#ifdef SERIAL_DEBUG
void uart_dump_stats(void)
{
    PRINT_CSTR("uart stats\r\n"
                "==========\r\n");
    PRINT_CSTR("frame errors:");
    uart_hex_8(stat_frame_err);
    PRINT_CSTR("\r\ndata overruns:");
    uart_hex_8(stat_data_overrun);
    PRINT_CSTR("\r\nparity fails:");
    uart_hex_8(stat_parity_check);
    PRINT_CSTR("\r\n");
}
#endif //SERIAL_DEBUG

#ifdef SERIAL_DEBUG
void uart_reset_stats(void)
{
    stat_frame_err    = 0;
    stat_data_overrun = 0;
    stat_parity_check = 0;
}
#endif //SERIAL_DEBUG

//TODO add a non-blocking (timeout) version
uint8_t uart_rx_block(void)
{
#ifdef SERIAL_DEBUG
    check_rx_errors();
#endif //SERIAL_DEBUG

    // Wait while there is nothing in the receive buffer.
    while (!(UCSR0A & (1 << RXC0))) {}
    return UDR0;
}

// return 1 when data in Rx buffer.
uint8_t uart_rx_ready(void)
{
    if(UCSR0A & (1 << RXC0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void uart_flush(void)
{
    uint8_t r;
    while(UCSR0A & (1 << RXC0))
        r = UDR0;
    (void)r; // To remove compiler warning
}

void uart_tx_str(const char* str)
{
    while(*str)
    {
        uart_tx(*(str++));
    }
}

void uart_tx_cstr(const char* str)
{
    while(pgm_read_byte(str))
    {
        uart_tx(pgm_read_byte(str++));
    }
}

void uart_hex_16(uint16_t d)
{
    uint8_t shift = 16;
    uint8_t c;

    do
    {
        shift -= 4;
        c = (d >> shift) & 0xf;
        if((c >= 0xa) && (c <= 0xf))
            uart_tx('a'-0xa+c);
        else
            uart_tx('0'+c);
    }while(shift);
}

void uart_hex_32(uint32_t d)
{
    uint8_t shift = 32;
    uint8_t c;

    do
    {
        shift -= 4;
        c = (d >> shift) & 0xf;
        if((c >= 0xa) && (c <= 0xf))
            uart_tx('a'-0xa+c);
        else
            uart_tx('0'+c);
    }while(shift);
}

void uart_hex_8(uint8_t d)
{
    uint8_t shift = 8;
    uint8_t c;

    do
    {
        shift -= 4;
        c = (d >> shift) & 0xf;
        if((c >= 0xa) && (c <= 0xf))
            uart_tx('a'-0xa+c);
        else
            uart_tx('0'+c);
    }while(shift);
}

#ifdef SERIAL_DEBUG
void uart_ping_test(void)
{
    uint8_t buf[10];
    uint8_t i;

    PRINT_CSTR("\r\nStarting uart ping test\r\n");

    while(1)
    {
        for(i=0; i<10; i++)
            buf[i] = uart_rx_block();

        for(i=0; i<10; i++)
            uart_tx(buf[i]);
    }
}
#endif //SERIAL_DEBUG

