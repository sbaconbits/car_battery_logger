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
// File Name: menu.c
//
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "menu.h"
#include "serial.h"
#include "hw_io.h"
#include "flash_S25FL.h"
#include "pwr_meas.h"
#include "utils.h"
#include "eeprom.h"
#include "logger_fs.h"
#include "ui.h"

#define ESC_KEY 0x1b

typedef void (*t_menu_handler)(void);

void menu_handler_led_on(void)
{
    LED_ACT_ON;
    LED_TRG_ON;
}

void menu_handler_led_off(void)
{
    LED_ACT_OFF;
    LED_TRG_OFF;
}

void menu_handler_led_pulses(void)
{
    LED_ACT_OFF;
    LED_TRG_OFF;
    int i;

    for(i=0; i<3; i++)
    {
        LED_ACT_ON;
        LED_TRG_ON;
        _delay_ms(5);
        LED_ACT_OFF;
        LED_TRG_OFF;
        _delay_ms(1000);
    }
}

void menu_handler_button_state(void)
{
    PRINT_CSTR("Button:");
    if(BUTTON_MODE_PRESSED)
        PRINT_CSTR("pressed");
    else
        PRINT_CSTR("released");
    PRINT_CSTR("\r\n");
}

void menu_handler_flash_test_1(void)
{
    flash_test1();
}

void menu_handler_flash_erase_chip(void)
{
    flash_test_erase_chip();
}

void menu_handler_flash_read_chip(void)
{
    flash_test_read_chip();
}
void menu_handler_dump_flash_sectors(void)
{
    flash_test_dump_flash_sectors(2);
}
void menu_handler_flash_write_chip(void)
{
    flash_test_write_chip();
}

void menu_handler_power_meas_dump_regs(void)
{
    power_meas_dump_registers();
}

void menu_handler_power_meas_bus_voltage(void)
{
    uint32_t val = 0;
    char* p = NULL;
    power_meas_get_bus_voltage_deci_mV(&val);
    PRINT_CSTR("Bus voltage (1/100 mV):");
    p = uint32_toa(val);
    uart_tx_str(p);
    PRINT_CSTR("\r\n");
}

void menu_handler_power_meas_shunt_voltage(void)
{
    int32_t val = 0;
    char* p = NULL;
    power_meas_get_shunt_voltage_cent_uV(&val);
    PRINT_CSTR("Shunt voltage (1/10 uV):");
    p = int32_toa(val);
    uart_tx_str(p);
    PRINT_CSTR("\r\n");
}

void menu_handler_power_meas_voltages(void)
{
    menu_handler_power_meas_bus_voltage();
    menu_handler_power_meas_shunt_voltage();
}

void menu_handler_test_itoa(void)
{
    utils_test_itoa();
}

void menu_handler_print_time(void)
{
    PRINT_CSTR("Monotonic timer (mS):\r\n");
    uart_tx_str(uint16_toa(g_timer_ms_count));
    PRINT_CSTR("\r\n");
}

void menu_handler_print_rtc(void)
{
    PRINT_CSTR("RTC time seconds:\r\n");
    uart_tx_str(uint32_toa(g_seconds_count));
    PRINT_CSTR("\r\n");
    rtc_print_time();
}

void menu_handler_watchdog_enable(void)
{
    watchdog_enable();
}

void gets_test(void)
{
    char buf[10];

    gets(buf, 10);
    PRINT_CSTR("Got string:\r\n");
    uart_tx_str(buf);
    PRINT_CSTR("\r\n");
}

void menu_handler_test_eeprom_dump(void)
{
    eeprom_dump();
}

void menu_handler_test_eeprom_read(void)
{
    eeprom_test_read();
}

void menu_handler_test_eeprom_write(void)
{
    eeprom_test_write();
}

void menu_handler_test_eeprom_erase(void)
{
    eeprom_erase();
}

void menu_handler_led_duty1(void)
{
    led_act_enable_duty(500,500);
    led_trg_enable_duty(100,900);
}

void menu_handler_led_duty2(void)
{
    led_act_enable_duty(10,990);
    led_trg_enable_duty(50,50);
}

void menu_handler_led_disable(void)
{
    led_act_disable();
    led_trg_disable();
}

void menu_handler_fs_print_session(void)
{
    uint16_t session = 0;
    char buffer[8];

    PRINT_CSTR("Input session (hex):\r\n");
    gets(buffer, 8);
    session = strhex16_toi(buffer);
    PRINT_CSTR("Printing session: 0x");
    uart_hex_16(session);
    PRINT_CSTR("\r\n");
    PRINT_CSTR("------- start of session print -------\r\n");
    fs_print_session(session);
    PRINT_CSTR("------- end of session print -------\r\n");
}

//------------------------------------------
typedef struct t_menu_item
{
    char                    selection_char;
    const char*             label;
    t_menu_handler          handler;
    struct t_menu*          sub_menu;
}t_menu_item;

typedef struct t_menu
{
    const char*             title;
    int                     items;
    t_menu_item*            menu_items;
}t_menu;
// -----
t_menu_item hw_menu_items[] =
{
    {'o', "LED on", menu_handler_led_on, NULL},
    {'f', "LED off", menu_handler_led_off, NULL},
    {'p', "LED pulses", menu_handler_led_pulses, NULL},
    {'b', "button state", menu_handler_button_state, NULL}
};
t_menu hw_menu =
{
    "Hardware Menu", sizeof(hw_menu_items)/sizeof(t_menu_item),
    hw_menu_items
};
// -----
t_menu_item flash_menu_items[] =
{
    {'1', "test 1", menu_handler_flash_test_1, NULL},
    {'e', "erase chip", menu_handler_flash_erase_chip, NULL},
    {'r', "read chip", menu_handler_flash_read_chip, NULL},
    {'d', "dump flash sectors", menu_handler_dump_flash_sectors, NULL},
    {'w', "write chip", menu_handler_flash_write_chip, NULL}
};
t_menu flash_menu =
{
    "Flash Menu", sizeof(flash_menu_items)/sizeof(t_menu_item),
    flash_menu_items
};
// -----
t_menu_item power_menu_items[] =
{
    {'d', "dump registers", menu_handler_power_meas_dump_regs, NULL},
    {'c', "configure", power_meas_configure, NULL},
    {'v', "voltages", menu_handler_power_meas_voltages, NULL}
};
t_menu power_menu =
{
    "Power Meas Menu", sizeof(power_menu_items)/sizeof(t_menu_item),
    power_menu_items
};
// -----
t_menu_item utils_menu_items[] =
{
    {'1', "Test my itoa", menu_handler_test_itoa, NULL},
    {'t', "print monotonic time", menu_handler_print_time, NULL},
    {'r', "print RTC time", menu_handler_print_rtc, NULL},
    {'w', "Watchdog enable", menu_handler_watchdog_enable, NULL},
    {'l', "Test LEDs duty1", menu_handler_led_duty1, NULL},
    {'k', "Test LEDs duty2", menu_handler_led_duty2, NULL},
    {'d', "disalbe LEDs", menu_handler_led_disable, NULL}
};
t_menu utils_menu =
{
    "Utils Menu", sizeof(utils_menu_items)/sizeof(t_menu_item),
    utils_menu_items
};
// -----
t_menu_item eeprom_menu_items[] =
{
    {'d', "dump eeprom", menu_handler_test_eeprom_dump, NULL},
    {'r', "read eeprom", menu_handler_test_eeprom_read, NULL},
    {'w', "write eeprom", menu_handler_test_eeprom_write, NULL},
    {'e', "erase eeprom", menu_handler_test_eeprom_erase, NULL}
};
t_menu eeprom_menu =
{
    "EEPROM Menu", sizeof(eeprom_menu_items)/sizeof(t_menu_item),
    eeprom_menu_items
};
// -----
t_menu_item logger_fs_menu_items[] =
{
    {'1', "test 1", fs_test1, NULL},
    {'2', "test 2", fs_test2, NULL},
    {'3', "test 3", fs_test3, NULL},
    {'r', "reset test 1", fs_test1_reset, NULL},
    {'t', "reset test 2", fs_test2_reset, NULL},
    {'d', "delete all sessions", fs_delete_all, NULL},
    {'e', "entry scan", fs_scan_entries_print, NULL},
    {'s', "sector scan", fs_scan_sector_print_headers, NULL},
    {'p', "print session", menu_handler_fs_print_session, NULL}
};
t_menu logger_fs_menu =
{
    "Logger FS Menu", sizeof(logger_fs_menu_items)/sizeof(t_menu_item),
    logger_fs_menu_items
};
// -----
t_menu_item ui_menu_items[] =
{
    {'s', "start fsm", ui_fsm_start, NULL}
};
t_menu ui_menu =
{
    "UI Menu", sizeof(ui_menu_items)/sizeof(t_menu_item),
    ui_menu_items
};
// -----
t_menu_item main_menu_items[] =
{
    {'h', "HW Menu", NULL, &hw_menu},
    {'f', "Flash Menu", NULL, &flash_menu},
    {'p', "Power Measurement Menu", NULL, &power_menu},
    {'u', "Utils Menu", NULL, &utils_menu},
    {'e', "EEPROM Menu", NULL, &eeprom_menu},
    {'l', "Logger FS Menu", NULL, &logger_fs_menu},
    {'i', "UI Menu", NULL, &ui_menu}
};

t_menu top_menu =
{
    "Main Menu", sizeof(main_menu_items)/sizeof(t_menu_item),
    main_menu_items
};
// -----
void menu_system_loop(void)
{
    t_menu* m = &top_menu;
    int i;
    uint8_t r;
    uint8_t actioned;

    for(i=0; i<20; i++)
    {
        LED_ACT_ON;
        LED_TRG_ON;
        _delay_ms(40);
        LED_ACT_OFF;
        LED_TRG_OFF;
        _delay_ms(40);
    }

    while(1)
    {
        actioned = 0;
        PRINT_CSTR("\r\n");
        uart_tx_str(m->title);
        PRINT_CSTR("\r\n");
        for(i=0; i<m->items; i++)
        {
            uart_tx(m->menu_items[i].selection_char);
            PRINT_CSTR(" - ");
            uart_tx_str(m->menu_items[i].label);
            PRINT_CSTR("\r\n");
        }

        PRINT_CSTR("Input:");
        r = uart_rx_block();
        PRINT_CSTR("\r\n");
        for(i=0; i<m->items; i++)
        {
            // ESC key pressed, special case
            if(r == ESC_KEY)
            {
                m = &top_menu;
                actioned = 1;
                continue;
            }
            // Found selection
            if(m->menu_items[i].selection_char == r)
            {
                // If we need to go to a sub menu
                if(m->menu_items[i].sub_menu)
                {
                    m = m->menu_items[i].sub_menu;
                    actioned = 1;
                    continue;
                }
                // Action the handler if we have one
                if(m->menu_items[i].handler)
                {
                    m->menu_items[i].handler();
                    //Go back to the top menu
                    m = &top_menu;
                    actioned = 1;
                    continue;
                }
            }
        }

        if(!actioned)
        {
            // didn't find selection, go back to top menu
            PRINT_CSTR("Err selection (");
            uart_tx(r);
            PRINT_CSTR(") not found\r\n");
            m = &top_menu;
        }
    }
}

