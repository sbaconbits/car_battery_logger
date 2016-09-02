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
// File Name: flash_S25FL.h
//

#ifndef FLASH_S25L_H
#define FLASH_S25L_H

#define FLASH_SIZE          (8ul * 1024 * 1024)
#define FLASH_PAGE_SIZE     (256)
#define FLASH_PAGE_MASK     (FLASH_PAGE_SIZE - 1)
#define FLASH_SECTOR_SIZE   (4 * 1024ul)
#define FLASH_SECTOR_MASK   (FLASH_SECTOR_SIZE - 1)
#define FLASH_BLOCK_SIZE    (64 * 1024)
#define FLASH_BLOCK_MASK    (FLASH_BLOCK_SIZE - 1)
#define FLASH_SECTOR_COUNT  (FLASH_SIZE / FLASH_SECTOR_SIZE)
#define FLASH_PAGE_COUNT    (FLASH_SIZE / FLASH_PAGE_SIZE)


#define PAGE_ALIGN_ADDR(_addr)  (_addr & (~(FLASH_PAGE_SIZE-1)))

// Note:
// - Addresses are 24-bit (16Mbyte)


void flash_init(void);
void flash_test1(void);
void flash_test_erase_chip(void);
void flash_test_read_chip(void);
void flash_test_write_chip(void);
void flash_test_dump_flash_sectors(uint8_t count);

uint8_t flash_read_manuf_dev_id(uint8_t* manu_id, uint8_t* dev_id);
uint8_t flash_read_status_reg_1(uint8_t* stat1);
uint8_t flash_read_status_reg_2(uint8_t* stat2);
uint8_t flash_read_status_reg_3(uint8_t* stat3);
uint8_t flash_write_enable(void);
uint8_t flash_write_disable(void);
// Can take about 40 secs
uint8_t flash_chip_erase(void);
uint8_t flash_wait_while_busy(void);
uint8_t flash_read_data(uint32_t addr, uint8_t* buf, uint16_t len);
uint8_t flash_sector_erase(uint32_t addr);
// 0-256 bytes
uint8_t flash_page_program(uint32_t addr, uint8_t* buf, uint16_t len);


uint8_t flash_read_page_buffer(uint32_t addr);  // page aligned.
uint8_t flash_write_page_buffer(uint32_t addr); // page aligned.

void flash_dump_write_page_buffer(void);

extern uint8_t flash_page_read_buffer[FLASH_PAGE_SIZE];
extern uint8_t flash_page_write_buffer[FLASH_PAGE_SIZE];


#endif //FLASH_S25L_H
