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
// File Name: main.c
//
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "menu.h"
#include "version.c"
#include "hw_io.h"
#include "flash_S25FL.h"
#include "pwr_meas.h"
#include "i2c.h"
#include "serial.h"
#include "utils.h"
#include "logger_fs.h"
#include "ui.h"

static uint8_t reset_source;

// /usr/lib/avr/include/avr

void init(void)
{
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

    reset_source = MCUSR;

    // If watchdog caused a reset then it will still be enabled on reset.
    watchdog_disable();

    uart_init();
    timer_init();
    flash_init();
    i2c_init();
    power_meas_init();
    fs_init();
    utils_init();
    ui_init();
}

void print_version(void)
{
    uart_tx_cstr(version_str);
    PRINT_CSTR("\r\n");
}

int main(void)
{
    init();
    reset_reason_print(reset_source);
    reset_reason_clear();
    PRINT_CSTR("\r\nStart: ");
    print_version();
    _delay_ms(1000);
    rtc_init();
    menu_system_loop();
    return 0;
}



