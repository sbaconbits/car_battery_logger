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
// File Name: pwr_meas.h
//

#ifndef PWR_MEAS_H
#define PWR_MEAS_H

void    power_meas_init(void);
void    power_meas_configure(void);
void    power_meas_dump_registers(void);
// Bus voltage in 100ths of a milli Volt.
uint8_t power_meas_get_bus_voltage_deci_mV(uint32_t* val);
// Shunt voltage in 10ths of a micro Volt.
uint8_t power_meas_get_shunt_voltage_cent_uV(int32_t* val);

void    power_meas_get_bus_voltage_raw(uint16_t* val);
void    power_meas_get_shunt_voltage_raw(uint16_t* val);
#endif //PWR_MEAS_H
