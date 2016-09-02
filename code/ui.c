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
// File Name: ui.c
//
#include "ui.h"

#include "utils.h"
#include "hw_io.h"
#include "logger_fs.h"
#include "pwr_meas.h"


typedef enum
{
    ST_POWER_ON,                // State after initial power on.
    ST_ALIVE,                   // Indicate life, the board is powered up and alive.
    ST_LOGGING,                 // Logging entries.
    ST_END_LOGGING,             //
    ST_FATAL_ERROR              // A fatal error has occured and we haven't rebooted.
} e_ui_state;

static e_ui_state ui_state;
static uint16_t marker_ms;
static uint32_t last_second_count;

// Length of time in mS mode button needs to be pressed to enter logging mode
#define BUTT_MODE_ALIVE_TO_LOG_MS   3000
// Length of time in mS mode button needs to be pressed to exit logging mode
#define BUTT_MODE_LOG_TO_END_MS     3000

void ui_init(void)
{
    ui_state = ST_POWER_ON;
    last_second_count = g_seconds_count;
}

void ui_fsm_start(void)
{
    t_log_entry entry;

    ui_state = ST_POWER_ON;
    while(1)
    {
        switch(ui_state)
        {
            case ST_POWER_ON:
                // Show we're alive and go to that state
                led_trg_disable();
                led_act_disable();
                ui_state = ST_ALIVE;
                led_act_enable_duty(20, 980); //Short 1/sec
                power_meas_configure();
                break;
            case ST_ALIVE:
                // Do we want to start logging yet?
                if(BUTTON_MODE_PRESSED)
                {
                    if(g_timer_ms_count > (marker_ms + BUTT_MODE_ALIVE_TO_LOG_MS))
                    {
                        led_act_enable_duty(20, 4980); //Short 1/5sec
                        ui_state = ST_LOGGING;
                        PRINT_CSTR("Going to start logging\r\n");
                        // Note: The following call can take a long time.
                        fs_start_log_session();
                        // We don't want to drop through future marker tests.
                        marker_ms = g_timer_ms_count;
                    }
                }
                else
                {
                    marker_ms = g_timer_ms_count;
                }
                break;
            case ST_LOGGING:
                // We're now logging, every second log an entry.
                if(last_second_count != g_seconds_count)
                {
                    LED_TRG_ON; //TODO change this when using trigger indication.
                    last_second_count = g_seconds_count;
                    entry.bus_voltage = 0;
                    entry.shunt_voltage = 0;
                    power_meas_get_bus_voltage_raw(&entry.bus_voltage);
                    power_meas_get_shunt_voltage_raw(&entry.shunt_voltage);
                    //TODO if power measurement has hit a threshold then start the trg LED indication.
                    fs_write_log_entry(&entry);
                    LED_TRG_OFF;
                }
                // Should we exit logging mode?
                if(BUTTON_MODE_PRESSED)
                {
                    if(g_timer_ms_count > (marker_ms + BUTT_MODE_LOG_TO_END_MS))
                    {
                        PRINT_CSTR("Going to end logging\r\n");
                        ui_state = ST_END_LOGGING;
                        // We don't want to drop through future marker tests.
                        marker_ms = g_timer_ms_count;
                    }
                }
                else
                {
                    marker_ms = g_timer_ms_count;
                }
                break;
            case ST_END_LOGGING:
                fs_end_log_session();
                ui_state = ST_POWER_ON;
                break;
            case ST_FATAL_ERROR:    // Follow through
            default:
                ui_state = ST_POWER_ON;
                break;
        }
    }
}
