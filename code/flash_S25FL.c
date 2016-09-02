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
// File Name: flash_S25FL.c
//
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "serial.h"
#include "utils.h"
#include "flash_S25FL.h"

#define FLASH_CS0_LOW                   PORTB &= ~(1 << PB1);
#define FLASH_CS0_HI                    PORTB |=  (1 << PB1);
//TODO add timeout to this loop
#define WAIT_SPI                        while(!(SPSR & (1 << SPIF))){}

#define FLASH_CMD_READ_STAT_REG_1           0x05
#define FLASH_CMD_READ_STAT_REG_2           0x35
#define FLASH_CMD_READ_STAT_REG_3           0x33
#define FLASH_CMD_WRITE_ENABLE              0x06
#define FLASH_CMD_WRITE_ENABLE_VOL_STAT     0x50
#define FLASH_CMD_WRITE_DISABLE             0x04
#define FLASH_CMD_WRITE_STAT_REG            0x01
#define FLASH_CMD_SET_BURST_WITH_WRAP       0x77
#define FLASH_CMD_SET_BLOCK_PTR_PROTECT     0x39
#define FLASH_CMD_PAGE_PROGRAM              0x02
#define FLASH_CMD_SECTOR_ERASE              0x20
#define FLASH_CMD_BLOCK_ERASE               0xD8
#define FLASH_CMD_CHIP_ERASE                0xC7
#define FLASH_CMD_ERASE_PROG_SUSPEND        0x75
#define FLASH_CMD_ERASE_PROG_RESUME         0x7A
#define FLASH_CMD_READ_DATA                 0x03
#define FLASH_CMD_FAST_READ                 0x0B
#define FLASH_CMD_FAST_READ_DUAL_OUTPUT     0x3B
#define FLASH_CMD_FAST_READ_QUAD_OUTPUT     0x6B
#define FLASH_CMD_FAST_READ_DUAL_IO         0xBB
#define FLASH_CMD_FAST_READ_QUAD_IO         0xEB
#define FLASH_CMD_CONTIN_READ_MODE_RST      0xFF
#define FLASH_CMD_DEEP_POWER_DOWN           0xB9
#define FLASH_CMD_RELEASE_PWD_DWN_DEV_ID    0xAB
#define FLASH_CMD_READ_MAN_DEV_ID           0x90
#define FLASH_CMD_READ_JEDEC_ID             0x9f
#define FLASH_CMD_READ_SFDP_REGISTER        0x5A
#define FLASH_CMD_READ_SECURITY_REGISTERS   0x48
#define FLASH_CMD_ERASE_SECURITY_REGISTERS  0x44
#define FLASH_CMD_PROG_SECURITY_REGISTERS   0x42

// Status Register 1 bits
#define SR1_SRP0    7   // Status register protect 0
#define SR1_SEC     6   // Sector/Block protect
#define SR1_TB      5   // Top/Bottom protect
#define SR1_BP2     4   // Block protect bits
#define SR1_BP1     3   //
#define SR1_BP0     2   //
#define SR1_WEL     1   // Write Enable latch
#define SR1_BUSY    0   // Embedded operation status

// Status Register 2 bits
#define SR2_SUS     7   // Suspend status
#define SR2_CMP     6   // Complement protect
#define SR2_LB3     5   // Security register lock bits
#define SR2_LB2     4   //
#define SR2_LB1     3   //
#define SR2_LB0     2   //
#define SR2_QE      1   // Quad enable
#define SR2_SRP1    0   // Status register protect 1

// Status Register 3 bits
#define SR3_RFU     7   // Reserved for future use
#define SR3_W6      6   // Burst wrap length
#define SR3_W5      5   //
#define SR3_W4      4   // Burst wrap enable
#define SR3_LC3     3   // Latency control
#define SR3_LC2     2   //
#define SR3_LC1     1   //
#define SR3_LC0     0   //

//TODO add code to kick the watchdog in these functions.
//TODO could remove one of these massive buffers if NO read part way through a write could be guaranteed.
uint8_t flash_page_read_buffer[FLASH_PAGE_SIZE];
uint8_t flash_page_write_buffer[FLASH_PAGE_SIZE];

void flash_init(void)
{
    //Setup outputs
    PORTB = 0;
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB1) | (1 << DDB2);
    //Setup input
    DDRB &= ~(1 << DDB4);

    FLASH_CS0_LOW;
    FLASH_CS0_HI;
    _delay_ms(100);

    //Enable SPI, Master, Set clock rate fosc/4
    //Spi interrupts disabled.
    //Tx MSB first 
    //Clock polarity: SCK low when idle
    //Clock phase: Leading edge sample, trailing edge setup
    SPCR = (1 << SPE) | (1 << MSTR);
}


uint8_t flash_read_manuf_dev_id(uint8_t* manu_id, uint8_t* dev_id)
{
    FLASH_CS0_LOW;
    // Send command
    SPDR = FLASH_CMD_READ_MAN_DEV_ID; WAIT_SPI;
    // Send 24 bit address
    SPDR = 0; WAIT_SPI;
    SPDR = 0; WAIT_SPI;
    SPDR = 0; WAIT_SPI;

    // Read manufacturer ID
    SPDR = 0; WAIT_SPI;
    *manu_id = SPDR;

    // Read the device ID
    SPDR = 0; WAIT_SPI;
    *dev_id = SPDR;

    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_read_status_reg_1(uint8_t* stat1)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_READ_STAT_REG_1; WAIT_SPI;
    // Read byte
    SPDR = 0; WAIT_SPI;
    *stat1 = SPDR;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_read_status_reg_2(uint8_t* stat2)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_READ_STAT_REG_2; WAIT_SPI;
    // Read byte
    SPDR = 0; WAIT_SPI;
    *stat2 = SPDR;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_read_status_reg_3(uint8_t* stat3)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_READ_STAT_REG_3; WAIT_SPI;
    // Read byte
    SPDR = 0; WAIT_SPI;
    *stat3 = SPDR;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_write_enable(void)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_WRITE_ENABLE; WAIT_SPI;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_write_disable(void)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_WRITE_DISABLE; WAIT_SPI;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_chip_erase(void)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_CHIP_ERASE; WAIT_SPI;
    FLASH_CS0_HI;
    return 0;
}

//TODO add a timeout to this loop.
uint8_t flash_wait_while_busy(void)
{
    uint8_t stat1;

    do
    {
        flash_read_status_reg_1(&stat1);
        // Wait for the busy flag to clear.
    }while(stat1 & (1 << SR1_BUSY));

    return 0;
}

uint8_t flash_read_data(uint32_t addr, uint8_t* buf, uint16_t len)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_READ_DATA;         WAIT_SPI;
    SPDR = ((addr & 0xff0000) >> 16);   WAIT_SPI;
    SPDR = ((addr & 0x00ff00) >>  8);   WAIT_SPI;
    SPDR = ((addr & 0x0000ff) >>  0);   WAIT_SPI;

    while(len)
    {
        // Read a byte
        SPDR = 0;   WAIT_SPI;
        *(buf++) = SPDR;
        --len;
    }

    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_sector_erase(uint32_t addr)
{
    //PRINT_CSTR("sector erase addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_SECTOR_ERASE;      WAIT_SPI;
    SPDR = ((addr & 0xff0000) >> 16);   WAIT_SPI;
    SPDR = ((addr & 0x00ff00) >>  8);   WAIT_SPI;
    SPDR = ((addr & 0x0000ff) >>  0);   WAIT_SPI;
    FLASH_CS0_HI;
    return 0;
}

uint8_t flash_page_program(uint32_t addr, uint8_t* buf, uint16_t len)
{
    FLASH_CS0_LOW;
    // Send cmd
    SPDR = FLASH_CMD_PAGE_PROGRAM;      WAIT_SPI;
    SPDR = ((addr & 0xff0000) >> 16);   WAIT_SPI;
    SPDR = ((addr & 0x00ff00) >>  8);   WAIT_SPI;
    SPDR = 0;                           WAIT_SPI; // LSB always zero (page aligned).

    while(len)
    {
        // Write a byte
        SPDR = *(buf++);    WAIT_SPI;
        --len;
    }

    FLASH_CS0_HI;
    return 0;
}

void flash_test1(void)
{
    uint8_t buf[4];
    uint8_t i;

    flash_read_manuf_dev_id(&buf[0], &buf[1]);
    PRINT_CSTR("Manu ID:");     uart_hex_8(buf[0]);
    PRINT_CSTR(" Dev ID:");     uart_hex_8(buf[1]);
    PRINT_CSTR("\r\n");

    flash_read_status_reg_1(&buf[0]);
    PRINT_CSTR("Stat1:");       uart_hex_8(buf[0]);
    PRINT_CSTR("\r\n");

    flash_read_status_reg_2(&buf[0]);
    PRINT_CSTR("Stat2:");       uart_hex_8(buf[0]);
    PRINT_CSTR("\r\n");

    flash_read_status_reg_3(&buf[0]);
    PRINT_CSTR("Stat3:");       uart_hex_8(buf[0]);
    PRINT_CSTR("\r\n");

    PRINT_CSTR("Wait not BUSY\r\n");

    flash_read_data(0, buf, 4);
    for(i=0; i<4; i++)
    {
        uart_hex_8(buf[i]);
        PRINT_CSTR(" ");
    }
    PRINT_CSTR("\r\n");

    PRINT_CSTR("Sector count:");
    uart_tx_str(uint16_toa(FLASH_SECTOR_COUNT));
    PRINT_CSTR("\r\n");
}

void flash_test_erase_chip(void)
{
    flash_wait_while_busy();
    flash_write_enable();
    flash_chip_erase();
    flash_wait_while_busy();
}

static void fill_page_buffer_rand(uint8_t* buf)
{
    uint8_t i;
    int r;
    int* p = (int*)buf;

    for(i=0; i<(FLASH_PAGE_SIZE/sizeof(int)); i++)
    {
        r = rand();
        *(p++) = r;
    }
}

static uint8_t page_buffers_equal(uint8_t* buf1, uint8_t* buf2)
{
    uint8_t i;
    uint16_t* p1 = (uint16_t*)buf1;
    uint16_t* p2 = (uint16_t*)buf2;

    for(i=0; i<(FLASH_PAGE_SIZE / sizeof(uint16_t)); i++)
    {
        if(*(p1++) != *(p2++))
            return 0;
    }

    return 1;
}

void flash_test_read_chip(void)
{
    uint32_t addr = 0;
    uint16_t page;
    uint32_t fail = 0, pass = 0;

    srand(0);
    PRINT_CSTR("Read entire chip:\r\n");
    for(page=0; page<FLASH_PAGE_COUNT; page++)
    //for(page=0; page<10; page++)
    {
        fill_page_buffer_rand(flash_page_write_buffer);
        flash_read_data(addr, flash_page_read_buffer, FLASH_PAGE_SIZE);
        if(page_buffers_equal(flash_page_read_buffer, flash_page_write_buffer))
        {
            ++pass;
        }
        else
        {
            ++fail;
            uart_tx('e');
        }
        addr += FLASH_PAGE_SIZE;
        // Print progress
        PRINT_CSTR("\r");
        uart_tx_str(uint16_toa(page));
    }
    PRINT_CSTR("\r\npass:");
    uart_tx_str(uint32_toa(pass));
    PRINT_CSTR(" fail:");
    uart_tx_str(uint32_toa(fail));
    PRINT_CSTR("\r\n");
}

void flash_test_write_chip(void)
{
    uint32_t addr = 0;
    uint16_t page;

    srand(0);
    PRINT_CSTR("Write entire chip:\r\n");
    for(page=0; page<FLASH_PAGE_COUNT; page++)
    //for(page=0; page<10; page++)
    {
        flash_wait_while_busy();
        flash_write_enable();
        fill_page_buffer_rand(flash_page_write_buffer);
        flash_page_program(addr, flash_page_write_buffer, FLASH_PAGE_SIZE);
        addr += FLASH_PAGE_SIZE;
        // Print progress
        PRINT_CSTR("\r");
        uart_tx_str(uint16_toa(page));
    }
    PRINT_CSTR("\r\n");
    flash_write_disable();
}

static void dump_page(uint8_t* buf, uint32_t addr)
{
    uint8_t line;
    uint16_t p;
    for(line=0; line<(FLASH_PAGE_SIZE/16); line++)
    {
        uart_hex_32(addr + (line * 16));
        PRINT_CSTR(" ");
        for(p=0; p<16; p++)
        {
            uart_hex_8(buf[line*16+p]);
            PRINT_CSTR(" ");
        }
        PRINT_CSTR("\r\n");
    }
}

void flash_test_dump_flash_sectors(uint8_t count)
{
    uint16_t page;
    uint16_t pages = (FLASH_SECTOR_SIZE * count) / FLASH_PAGE_SIZE;
    uint32_t addr = 0;

    for(page=0; page<pages; page++)
    {
        flash_read_data(addr, flash_page_read_buffer, FLASH_PAGE_SIZE);
        dump_page(flash_page_read_buffer, addr);
        addr += FLASH_PAGE_SIZE;
    }

}

void flash_dump_write_page_buffer(void)
{
    dump_page(flash_page_write_buffer, 0);
}

uint8_t flash_read_page_buffer(uint32_t addr)
{
    addr = PAGE_ALIGN_ADDR(addr);
    return flash_read_data(addr, flash_page_read_buffer, FLASH_PAGE_SIZE);
}

uint8_t flash_write_page_buffer(uint32_t addr)
{
    addr = PAGE_ALIGN_ADDR(addr);
    return flash_page_program(addr, flash_page_write_buffer, FLASH_PAGE_SIZE);
}

