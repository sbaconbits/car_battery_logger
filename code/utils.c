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
// File Name: utils.c
//

#include <stdlib.h>
#include <inttypes.h>
#include <avr/interrupt.h>

#include "utils.h"
#include "serial.h"
#include "hw_io.h"

// 32 bit : 4294967296
// 16 bit : 65536

#define NUM_BUF_SIZE 12     // 4294967296
char num_buf[NUM_BUF_SIZE];
volatile uint16_t g_timer_ms_count = 0;
volatile uint32_t g_seconds_count = 0;

static void leds_update_ms(void);

typedef enum
{
    led_disabled,
    led_on_phase,
    led_off_phase
} e_led_phase;

typedef struct
{
    uint16_t set_on_16ms;
    uint16_t set_off_16ms;
    uint16_t count_down16;
    e_led_phase phase;
} t_led_data;

t_led_data led_act_data;
t_led_data led_trg_data;

void utils_init(void)
{
    led_act_data.set_on_16ms  = 0;
    led_act_data.set_off_16ms = 0;
    led_act_data.count_down16 = 0;
    led_act_data.phase      = led_disabled;

    led_trg_data.set_on_16ms  = 0;
    led_trg_data.set_off_16ms = 0;
    led_trg_data.count_down16 = 0;
    led_trg_data.phase      = led_disabled;
}

char* uint32_toa(uint32_t data)
{
    ldiv_t d;
    char* p = &num_buf[NUM_BUF_SIZE];

    *(--p) = '\0';
    do
    {
        d = ldiv(data, 10);
        data = d.quot;
        *(--p) = '0' + abs(d.rem);
    }while(data);
    return p;
}

char* uint16_toa(uint16_t data)
{
    div_t d;
    char* p = &num_buf[NUM_BUF_SIZE];

    *(--p) = '\0';
    do
    {
        //TODO the following doesn't quite work as expected. div uses int16_t
        //so find the abs results in 1/2 the range, same with the above function.
        d = div(data, 10);
        data = d.quot;
        *(--p) = '0' + abs(d.rem);
    }while(data);
    return p;
}

char* int32_toa(int32_t data)
{
    char* p = &num_buf[NUM_BUF_SIZE];
    char neg = (data < 0) ? 1:0;
    ldiv_t d;

    *(--p) = '\0';
    do
    {
        d = ldiv(data, 10);
        data = d.quot;
        *(--p) = '0' + abs(d.rem);
    }while(data);

    if(neg)
        *(--p) = '-';

    return p;
}

char* int16_toa(int16_t data)
{
    div_t d;
    char neg = (data < 0) ? 1:0;
    char* p = &num_buf[NUM_BUF_SIZE];

    *(--p) = '\0';
    do
    {
        d = div(data, 10);
        data = d.quot;
        *(--p) = '0' + abs(d.rem);
    }while(data);

    if(neg)
        *(--p) = '-';
    return p;
}


void utils_test_itoa(void)
{
    char* p = NULL;
    uint16_t i = 0xfffe;

    PRINT_CSTR("utils_test_itoa\r\n");

    p = uint32_toa(65023);
    uart_tx_str(p);
    PRINT_CSTR("\r\n");

    p = uint32_toa(75002);
    uart_tx_str(p);
    PRINT_CSTR("\r\n");

    p = int32_toa((int16_t)i);   //uint16_t -> int32_t
    uart_tx_str(p);
    PRINT_CSTR("\r\n");

    PRINT_CSTR("32 bit byte order:");
    uart_hex_32(0x44332211);
    PRINT_CSTR("\r\n");

    PRINT_CSTR("rand:");
    srand(0);
    uart_tx_str(int32_toa(rand()));
    PRINT_CSTR("\r\n");

}

void watchdog_enable(void)
{
    cli(); // Disable interrupts
    WATCHDOG_RESET; 
    //Start timed sequence 
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    // WDP[3:0]     = 0110  = 1Sec timeout
    // WDE          = 1     = Watchdog system reset
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1);
    sei(); // Enable interrupts
}

void watchdog_disable(void)
{
    cli(); // Disable interrupts
    WATCHDOG_RESET;
    // Clear WDRF in MCUSR
    MCUSR &= ~(1 << WDRF);
    // Start timed sequence 
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    // Turn off watchdog
    WDTCSR = 0;
    sei(); // Enable interrupts
}



ISR (TIMER0_COMPA_vect, ISR_BLOCK)
{
    ++g_timer_ms_count;
    if((g_timer_ms_count & 0x0f) == 0)
        leds_update_ms();
}

static void leds_update_ms(void)
{
    if(led_act_data.phase == led_on_phase)
    {
        --led_act_data.count_down16;
        if(0 == led_act_data.count_down16)
        {
            LED_ACT_OFF;
            led_act_data.phase = led_off_phase;
            led_act_data.count_down16 = led_act_data.set_off_16ms;
        }
    }
    else if(led_act_data.phase == led_off_phase)
    {
        --led_act_data.count_down16;
        if(0 == led_act_data.count_down16)
        {
            LED_ACT_ON;
            led_act_data.phase = led_on_phase;
            led_act_data.count_down16 = led_act_data.set_on_16ms;
        }
    }
    else
    {
        LED_ACT_OFF;
    }

    if(led_trg_data.phase == led_on_phase)
    {
        --led_trg_data.count_down16;
        if(0 == led_trg_data.count_down16)
        {
            LED_TRG_OFF;
            led_trg_data.phase = led_off_phase;
            led_trg_data.count_down16 = led_trg_data.set_off_16ms;
        }
    }
    else if(led_trg_data.phase == led_off_phase)
    {
        --led_trg_data.count_down16;
        if(0 == led_trg_data.count_down16)
        {
            LED_TRG_ON;
            led_trg_data.phase = led_on_phase;
            led_trg_data.count_down16 = led_trg_data.set_on_16ms;
        }
    }
    else
    {
        LED_TRG_OFF;
    }
}

void led_enable_duty(t_led_data* data, uint16_t on_ms, uint16_t off_ms)
{
    data->set_on_16ms   = on_ms/16;
    data->set_off_16ms  = off_ms/16;
    data->phase         = led_on_phase;

    // Lets not round to zero if non-zero was asked for.
    if((data->set_on_16ms == 0) && (on_ms != 0))
        data->set_on_16ms = 1;

    data->count_down16 = data->set_on_16ms;
}

void led_act_enable_duty(uint16_t on_ms, uint16_t off_ms)
{
    led_enable_duty(&led_act_data, on_ms, off_ms);
    LED_ACT_ON;
}

void led_trg_enable_duty(uint16_t on_ms, uint16_t off_ms)
{
    led_enable_duty(&led_trg_data, on_ms, off_ms);
    LED_TRG_ON;
}

void led_act_disable(void)
{
    led_act_data.phase = led_disabled;
    LED_ACT_OFF;
}

void led_trg_disable(void)
{
    led_trg_data.phase = led_disabled;
    LED_ACT_OFF;
}

void timer_init(void)
{
    // 1mS timer
    // 8Mhz / (256 * 31) = 1008 per second

    // Clear timer on compare match (CTC) mode.
    // 8-bit timer.
    // WGM02:0 = 010
    TCCR0A = (1 << WGM01);
    // Clock select /256
    // CS02:0 = 100
    TCCR0B = (1 << CS02);
    OCR0A = 31;
    // Output compare match A interrupt enable
    TIMSK0 = (1 << OCIE0A);
}

ISR (TIMER2_OVF_vect, ISR_BLOCK)
{
    ++g_seconds_count;
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
}

void rtc_print_time(void)
{
    ldiv_t t;
    uint32_t rtc_seconds = g_seconds_count;
    uint8_t sec, min, hour, day;

    t = ldiv(rtc_seconds, 60);
    sec = t.rem;
    rtc_seconds = t.quot;       // Contains mins

    t = ldiv(rtc_seconds, 60);
    min = t.rem;
    rtc_seconds = t.quot;       // Contains hours

    t = ldiv(rtc_seconds, 24);
    hour = t.rem;
    rtc_seconds = t.quot;       // Contains days
    day = t.quot;

    PRINT_CSTR("D:H:M:S ");
    uart_tx_str(uint16_toa(day));
    PRINT_CSTR(":");
    uart_tx_str(uint16_toa(hour));
    PRINT_CSTR(":");
    uart_tx_str(uint16_toa(min));
    PRINT_CSTR(":");
    uart_tx_str(uint16_toa(sec));
    PRINT_CSTR("\r\n");

}

// Decodes flags in MCUSR register.
void reset_reason_print(uint8_t source)
{
    PRINT_CSTR("\r\n\r\nReset reason: ");

    if(source & (1 << PORF))
        PRINT_CSTR(" power on ");
    if(source & (1 << EXTRF))
        PRINT_CSTR(" external reset ");
    if(source & (1 << BORF))
        PRINT_CSTR(" brown out ");
    if(source & (1 << WDRF))
        PRINT_CSTR(" watchdog ");

    PRINT_CSTR("\r\n");
}

void reset_reason_clear(void)
{
    MCUSR = 0;
}

uint8_t gets(char* buf, uint8_t buf_size)
{
    uint8_t pos, c;

    for(pos=0; pos<buf_size; pos++)
        buf[pos] = '\0';

    pos = 0;
    while(pos < (buf_size-1))
    {
        c = uart_rx_block();
        uart_tx(c);
        if(c == '\r')
        {
            goto end;
        }
        else if(((c == 0x7f) || (c == 0x08))&& (pos > 0)) // backspace
        {
            buf[--pos] = '\0';
            PRINT_CSTR("\r");
            uart_tx_str(buf);
        }
        else
        {
            buf[pos++] = (char)c;
        }
    }
end:
    return pos;
}

uint16_t strhex16_toi(char* str)
{
    char* p = str;
    uint16_t mult = 1;
    uint16_t ret = 0;

    // Move to end.
    while(*p != '\0')
        ++p;

    // Point to last.
    --p;

    while(p >= str)
    {
        if( (*p >= 'a') && (*p <= 'f') )
            ret += (*p - 'a' + 0xa) * mult;
        else if( (*p >= 'A') && (*p <= 'F') )
            ret += (*p - 'A' + 0xa) * mult;
        else if((*p >= '0') && (*p <= '9') )
            ret += (*p - '0') * mult;
        else
            return 0;
        mult *= 16;
        --p;
    }
    return ret;
}

