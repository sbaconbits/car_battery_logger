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
// File Name: serial.h
//

#ifndef SERIAL_H
#define SERIAL_H

#include <inttypes.h>
#include <avr/pgmspace.h>

//#define SERIAL_DEBUG

void uart_init(void);
void uart_tx(uint8_t c);
uint8_t uart_rx_block(void);
void uart_tx_str(const char* str);
void uart_tx_cstr(const char* str);
void uart_hex_32(uint32_t d);
void uart_hex_16(uint16_t d);
void uart_hex_8(uint8_t d);
uint8_t uart_rx_ready(void);
void uart_flush(void);

#ifdef SERIAL_DEBUG
void uart_reset_stats(void);
void uart_ping_test(void);
void uart_dump_stats(void);
#endif //SERIAL_DEBUG

#endif //SERIAL_H
