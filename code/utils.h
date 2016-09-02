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
// File Name: utils.h
//

#ifndef UTILS_H
#define UTILS_H

#include <avr/pgmspace.h>
#include "serial.h"

void utils_test_itoa(void);

char* uint32_toa(uint32_t data);
char* uint16_toa(uint16_t data);
char* int32_toa(int32_t data);
char* int16_toa(int16_t data);

uint16_t strhex16_toi(char* str);

void watchdog_enable(void);
void watchdog_disable(void);

void timer_init(void);
extern volatile uint16_t g_timer_ms_count;

void rtc_init(void); //Wait a second after boot before calling this?
void rtc_print_time(void);
extern volatile uint32_t g_seconds_count;

void reset_reason_print(uint8_t source);
void reset_reason_clear(void);

uint8_t gets(char* buf, uint8_t buf_size);

void led_act_enable_duty(uint16_t on_ms, uint16_t off_ms);
void led_act_disable(void);
void led_trg_enable_duty(uint16_t on_ms, uint16_t off_ms);
void led_trg_disable(void);

void utils_init(void);

#define PRINT_CSTR(_str) uart_tx_cstr( PSTR(_str) )
//#define PRINT_CSTR(_str) uart_tx_str( _str )

#define WATCHDOG_RESET __asm__ __volatile__ ("wdr")

#endif //UTILS_H
