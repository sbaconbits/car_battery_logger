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
// File Name: i2c.c
//
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <util/twi.h>

#include "serial.h"
#include "i2c.h"

void i2c_init(void)
{
    // TWI (Two wire interface) Bit Rate register (TWBR)
    // 400KHz mode
    // 16+2*(TWBR)*(PrescalerValue) = 8MHz / 400KHz = 20
    // 4/2 = TWBR * PrescalerValue.
    // TWBR = 2, PrescalerValue = 1.
    TWBR = 2;
    // PrescalerValue TWPS[1:0] = 00
    TWSR &= ~((1 << TWPS0) | (1 << TWPS1));
}

uint8_t i2c_START(void)
{
    uint8_t status = 0;

    // Master Tx (MT) Mode
    // START condition (SLA+W)

    // TWEN     - Enable the two wire interface
    // TWSTA    - Tx a START condition
    // TWINT    - Clear the interrupt flag by writing a 1 
    TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
    TWI_WAIT_JOB_COMPLETE;

    // Should see START condition has been transmitted
    status = TWSR & TW_STATUS_MASK;
    if( (status != TW_START) && (status != TW_REP_START) )
        return e_i2c_err_1; //ERROR

    return 0;
}

uint8_t i2c_slave_addr(uint8_t addr, uint8_t read)
{
    addr <<= 1;
    addr |= (read & 0x1);

    // Write SLA+W
    TWDR = addr;

    // Continue Tx
    TWCR = (1 << TWEN) | (1 << TWINT);
    TWI_WAIT_JOB_COMPLETE;

    if(read)
    {
        switch(TWSR & TW_STATUS_MASK)
        {
            default:
            case TW_MR_SLA_NACK:    // SLA+R Transmitted, NACK received.
                return e_i2c_err_5;
            case TW_MR_ARB_LOST:    // Arbitration lost in SLA-R or NACK.
                return e_i2c_err_6;
            case TW_MR_SLA_ACK:     // SLA+R Transmitted, ACK received.
                break;              //TODO just deal with the working case for now.
        }
    }
    else //write
    {
        switch(TWSR & TW_STATUS_MASK)
        {
            default:
            case TW_MT_SLA_NACK:    // SLA+W Transmitted, NACK received.
                return e_i2c_err_2;
            case TW_MT_ARB_LOST:    // Arbitration lost in SLA+W or data.
                return e_i2c_err_3;
            case TW_MT_SLA_ACK:     // SLA+W Transmitted, ACK received.
                break;              //TODO just deal with the working case for now.
        }
    }
    return 0;
}

uint8_t i2c_write_data(uint8_t* pd, uint8_t size)
{
    uint8_t i;

    for(i=0; i<size; i++)
    {
        //TWI_WAIT_JOB_COMPLETE;
        TWDR = pd[i];

        // Continue Tx
        TWCR = (1 << TWEN) | (1 << TWINT);
        TWI_WAIT_JOB_COMPLETE;

        // Write collision
        if(TWCR & (1 << TWWC))
            return e_i2c_err_write_collision;
    }
    return 0;
}

uint8_t i2c_read_data(uint8_t* pd, uint8_t size)
{
    uint8_t i;

    for(i=0; i<size; i++)
    {
        // Continue Rx
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
        TWI_WAIT_JOB_COMPLETE;
        pd[i] = TWDR;
        //TODO Do I need to check this: TW_MR_DATA_NACK
    }

    //Could NACK, but going to send a STOP condition
    return 0;
}

uint8_t i2c_STOP(void)
{
    // TWEN     - Enable the two wire interface
    // TWSTO    - Tx a STOP condition
    // TWINT    - Clear the interrupt flag by writing a 1 
    TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);

    return 0;
}


