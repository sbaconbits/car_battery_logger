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
// File Name: i2c.h
//

#ifndef I2C_H
#define I2C_H

#include <inttypes.h>

// TWI Registers (Two wire interface)
// =============
// TWI Bit Rate
// - TWBR
// TWI Control
// - TWCR
// TWI Status
// - TWSR
// TWI Data
// - TWDR
// TWI (Slave) Address
// - TWAR
// TWI (Slave) Address Mask
// - TWAMR

//TODO add timeout to wait (no lockup)
#define TWI_WAIT_JOB_COMPLETE while(!(TWCR & (1 << TWINT))){}
#define I2C_SLAVE_READ  0x01
#define I2C_SLAVE_WRITE 0x00

enum
{
    e_i2c_err_1 = 1,
    e_i2c_err_2,
    e_i2c_err_3,
    e_i2c_err_write_collision,
    e_i2c_err_5,
    e_i2c_err_6,
    e_i2c_err_7,
};

void        i2c_init(void);
uint8_t     i2c_START(void);
uint8_t     i2c_slave_addr(uint8_t addr, uint8_t read);
uint8_t     i2c_STOP(void);
uint8_t     i2c_write_data(uint8_t* pd, uint8_t size);
uint8_t     i2c_read_data(uint8_t* pd, uint8_t size);

#endif //I2C_H
