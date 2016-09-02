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
// File Name: pwr_meas.c
//
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <util/twi.h>

#include "serial.h"
#include "i2c.h"
#include "utils.h"

// INA226 I2C
// To read a register:
// - START
// - Slave + W
// - Write register to be read
// - START
// - Slave + R
// - Reads (as many as required)
// - STOP

// A1 = GND, A0 = GND therefore address = 100 0000 (+ R/!W LSB)
#define INA226_SLA          0x40 //0100 0000
#define INA226_SLA_READ     0x81 //1000 0001
#define INA226_SLA_WRITE    0x80 //1000 0000

#define INA226_REG_CONFIG           0x00
#define INA226_REG_SHUNT_V          0x01
#define INA226_REG_BUS_V            0x02
#define INA226_REG_POWER            0x03
#define INA226_REG_CURRENT          0x04
#define INA226_REG_CALIBRATION      0x05
#define INA226_REG_MASK_ENABLE      0x06
#define INA226_REG_ALERT_LIMIT      0x07
#define INA226_REG_MANUF_ID         0xfe
#define INA226_REG_DIE_ID           0xff

#define INA226_REG_CNFG_RESET_MASK      0x01    // RST
#define INA226_REG_CNFG_RESET_SHIFT     0x15    // bits[15]
#define INA226_REG_CNFG_AVG_MASK        0x07    // AVG
#define INA226_REG_CNFG_AVG_SHIFT       0x09    // bits[11:9]
#define INA226_REG_CNFG_VBUSCT_MASK     0x07    // VBUSCT
#define INA226_REG_CNFG_VBUSCT_SHIFT    0x06    // bits[8:6]
#define INA226_REG_CNFG_VSHCT_MASK      0x07    // VSHCT
#define INA226_REG_CNFG_VSHCT_SHIFT     0x03    // bits[5:3]
#define INA226_REG_CNFG_MODE_MASK       0x07    // MODE
#define INA226_REG_CNFG_MODE_SHIFT      0x00    // bits[2:0]

#define DBG_PWR_MEAS

typedef struct
{
    uint8_t addr;
    const char* name;
} s_ina226_reg_info;

static uint8_t power_meas_read_reg(uint8_t reg, uint16_t* val);
static uint8_t power_meas_write_reg(uint8_t reg, uint16_t val);

s_ina226_reg_info reg_list[] =
{
    {INA226_REG_CONFIG,     "Config"},
    {INA226_REG_SHUNT_V,    "Shunt Volt"},
    {INA226_REG_BUS_V,      "Bus Volt"},
    {INA226_REG_POWER,      "Power"},
    {INA226_REG_CURRENT,    "Current"},
    {INA226_REG_CALIBRATION,"Calibration"},
    {INA226_REG_MASK_ENABLE,"Mask/Enable"},
    {INA226_REG_ALERT_LIMIT,"Alert Limit"},
    {INA226_REG_MANUF_ID,   "Manuf ID"},
    {INA226_REG_DIE_ID,     "Die ID"}
};

//TODO add a soft reset before setup for robustness (INA226_REG_CNFG_RESET_SHIFT).

void power_meas_init(void)
{
}

// TODO Make configuration generic in future by exposing parameter to make this driver more useful.
void power_meas_configure(void)
{
    uint8_t averaging_mode = 0x7;                   // 1024 averages.
    uint8_t bus_voltage_conversion_time = 0x4;      // 1.1mS.
    uint8_t shunt_voltage_conversion_time = 0x4;    // 1.1mS.
    uint8_t operating_mode = 0x7;                   // Shunt and bus continuous.
    uint16_t val = 0;

    val |= (averaging_mode                  << INA226_REG_CNFG_AVG_SHIFT);
    val |= (bus_voltage_conversion_time     << INA226_REG_CNFG_VBUSCT_SHIFT);
    val |= (shunt_voltage_conversion_time   << INA226_REG_CNFG_VSHCT_SHIFT);
    val |= (operating_mode                  << INA226_REG_CNFG_MODE_SHIFT);

    //PRINT_CSTR("writing config(0x");
    //uart_hex_16(val);
    //PRINT_CSTR(")\r\n");

    power_meas_write_reg(INA226_REG_CONFIG, val);
}

static uint8_t power_meas_read_reg(uint8_t reg, uint16_t* val)
{
    uint8_t fail_reason = 0;
    uint8_t data_rx[2] = {0, 0};

    fail_reason = i2c_START();
    if(fail_reason)
        goto fail;

    fail_reason = i2c_slave_addr(INA226_SLA, I2C_SLAVE_WRITE);
    if(fail_reason)
        goto fail;

    fail_reason = i2c_write_data(&reg, 1);
    if(fail_reason)
        goto fail;

    fail_reason = i2c_START(); // Repeat start
    if(fail_reason)
        goto fail;

    fail_reason = i2c_slave_addr(INA226_SLA, I2C_SLAVE_READ);
    if(fail_reason)
        goto fail;

    fail_reason = i2c_read_data(data_rx, 2);
    if(fail_reason)
       goto fail; 

    *val = data_rx[1] | (data_rx[0] << 8);

fail:
    i2c_STOP();

    return fail_reason;
}

static uint8_t power_meas_write_reg(uint8_t reg, uint16_t val)
{
    uint8_t fail_reason = 0;
    uint8_t data_rx[2];

    data_rx[0] = (val & 0xff00) >> 8;
    data_rx[1] = (val & 0x00ff);

    fail_reason = i2c_START();
    if(fail_reason)
        goto fail;

    fail_reason = i2c_slave_addr(INA226_SLA, I2C_SLAVE_WRITE);
    if(fail_reason)
        goto fail;

    fail_reason = i2c_write_data(&reg, 1);
    if(fail_reason)
        goto fail;

    fail_reason = i2c_write_data(data_rx, 2);
    if(fail_reason)
       goto fail; 

fail:
    i2c_STOP();
    return fail_reason;
}

uint8_t power_meas_get_bus_voltage_deci_mV(uint32_t* val)
{
    uint16_t raw_val;
    uint8_t ret = 0;

    // Bus voltage register LSB is 1.25mV. Full-scale +/- 40.96V
    ret = power_meas_read_reg(INA226_REG_BUS_V, &raw_val);
#ifdef DBG_PWR_MEAS
    PRINT_CSTR("(0x");
    uart_hex_16(raw_val);
    PRINT_CSTR(")\r\n");
#endif
    *val = raw_val;
    *val *= 125;

    return ret;
}

uint8_t power_meas_get_shunt_voltage_cent_uV(int32_t* val)
{
    uint16_t raw_val;
    uint8_t ret = 0;

    // Bus voltage register LSB is 2.5uV. Full-scale +/- 81.92mV
    ret = power_meas_read_reg(INA226_REG_SHUNT_V, &raw_val);
#ifdef DBG_PWR_MEAS
    PRINT_CSTR("(0x");
    uart_hex_16(raw_val);
    PRINT_CSTR(")\r\n");
#endif
    *val = (int16_t)raw_val;
    *val *= 25;

    return ret;
}

void power_meas_get_bus_voltage_raw(uint16_t* val)
{
    power_meas_read_reg(INA226_REG_BUS_V, val);
}

void power_meas_get_shunt_voltage_raw(uint16_t* val)
{
    power_meas_read_reg(INA226_REG_SHUNT_V, val);
}

void power_meas_dump_registers(void)
{
    uint8_t i;
    uint16_t val = 0;

    PRINT_CSTR("Dump ina226 registers:\r\n");
    PRINT_CSTR("Addr Val  Name\r\n");

    for(i=0; i<(sizeof(reg_list)/sizeof(s_ina226_reg_info)); i++)
    {
        power_meas_read_reg(reg_list[i].addr, &val);
        uart_hex_8(reg_list[i].addr);
        PRINT_CSTR("   ");
        uart_hex_16(val);
        PRINT_CSTR(" ");
        uart_tx_str(reg_list[i].name);
        PRINT_CSTR("\r\n");
    }

    power_meas_read_reg(INA226_REG_CONFIG, &val);
    PRINT_CSTR("AVG:   ");
    uart_hex_8((val >> INA226_REG_CNFG_AVG_SHIFT) & INA226_REG_CNFG_AVG_MASK);
    PRINT_CSTR("\r\n");
    PRINT_CSTR("VBUSCT:");
    uart_hex_8((val >> INA226_REG_CNFG_VBUSCT_SHIFT) & INA226_REG_CNFG_VBUSCT_MASK);
    PRINT_CSTR("\r\n");
    PRINT_CSTR("VSHCT: ");
    uart_hex_8((val >> INA226_REG_CNFG_VSHCT_SHIFT) & INA226_REG_CNFG_VSHCT_MASK);
    PRINT_CSTR("\r\n");
    PRINT_CSTR("MODE:  ");
    uart_hex_8((val >> INA226_REG_CNFG_MODE_SHIFT) & INA226_REG_CNFG_MODE_MASK);
    PRINT_CSTR("\r\n");
}


