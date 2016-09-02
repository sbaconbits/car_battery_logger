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
// File Name: logger_fs.c
//
#include <stdlib.h>

#include "logger_fs.h"
#include "flash_S25FL.h"
#include "serial.h"
#include "utils.h"


#define IS_SECTOR_START(_addr) ( 0 == (_addr & FLASH_SECTOR_MASK) )
#define IS_PAGE_START(_addr)   ( 0 == (_addr & FLASH_PAGE_MASK  ) )

// Entry header
// ============
// - At the start of every sector:
//  - 4K per sector (256B per page. 16 pages per sector).
//  - 5bytes per entry. 256 / 5 = 51.2 entries per page.

typedef struct
{
    uint16_t log_session;
    uint16_t seq_num;       // Wrap 2048 (sector count).
    uint16_t inv_seq_num;
    uint8_t checksum;
}t_log_sector_header;

typedef void (*entry_cb)(t_log_entry* entry);

static void clear_page_write_buffer(void);
static void write_log_header(void);
static void do_flash_write(void);
static void do_flash_sector_erase(uint32_t addr);
static void print_header(t_log_sector_header* header);
static void print_entry(t_log_entry* entry);
static void scan_entries_in_sector(uint32_t addr, uint16_t read_offset, entry_cb call_back);
static uint8_t find_session_start(uint16_t session, uint32_t* find_addr);

static void add_entry_checksum(t_log_entry* entry);
static void add_header_checksum(t_log_sector_header* header);
static uint8_t is_header_valid(t_log_sector_header* header);
static uint8_t is_header_empty(t_log_sector_header* header);
static uint8_t is_entry_empty(t_log_entry* entry);
static uint8_t is_log_entry_checksum_valid(t_log_entry* entry);
static uint8_t is_log_entry_empty(t_log_entry* entry);

// Initial scan will set this.
// ALWAYS a multiple of flash page size.
static uint32_t             g_flash_write_addr = 0;
static t_log_sector_header  g_current_log_header;
static uint16_t             g_flash_buf_offset = 0;
//****************************************

void fs_init(void)
{
}

void fs_start_log_session(void)
{
    //TODO this can be really slow, worst case three scans of the entire flash looking at the header in each sector.

    // Find first empty sector
    // If no empty sectors, find lowest session number, then find the start of that session.
    uint32_t addr = 0;
    uint16_t oldest_session = 0xffff;   //Lowest
    uint16_t newest_session = 0;        //Highest
    uint16_t oldest_seq = 0xffff;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;

    // Search for oldest and newest sessions.
    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        flash_read_page_buffer(addr);
        if( !is_header_empty(header) &&
             is_header_valid(header) )
        {
            if(header->log_session < oldest_session)
                oldest_session = header->log_session;
            if(header->log_session > newest_session)
                newest_session = header->log_session;
        }
    }

    // Search for empty space.
    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        flash_read_page_buffer(addr);
        if(is_header_empty(header) )
        {
            g_flash_write_addr = addr;
            g_current_log_header.log_session    = newest_session + 1;
            g_current_log_header.seq_num        = 0;
            g_current_log_header.inv_seq_num    = 0;
            g_flash_buf_offset = 0;
            goto complete;
        }
    }

    // Search for lowest sequence number for session.
    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        flash_read_page_buffer(addr);
        if( is_header_valid(header) &&
            (header->log_session == oldest_session))
        {
            if(header->seq_num < oldest_seq)
            {
                oldest_seq = header->seq_num;
                g_flash_write_addr = addr;
            }
        }
    }

    g_flash_write_addr = addr;
    g_current_log_header.log_session    = newest_session + 1;
    g_current_log_header.seq_num        = 0;
    g_current_log_header.inv_seq_num    = 0;
    g_flash_buf_offset = 0;
complete:
    PRINT_CSTR("Start Session addr:");uart_hex_32(g_flash_write_addr);
    PRINT_CSTR(" Session: 0x");uart_hex_16(g_current_log_header.log_session);
    PRINT_CSTR("\r\n");
}

static void do_flash_write(void)
{
    flash_wait_while_busy();
    flash_write_enable();
    flash_write_page_buffer(g_flash_write_addr);
    flash_write_disable();
    flash_wait_while_busy();
}

static void do_flash_sector_erase(uint32_t addr)
{
    flash_wait_while_busy();
    flash_write_enable();
    flash_sector_erase(addr);
    flash_write_disable();
    flash_wait_while_busy();
}

void fs_end_log_session(void)
{
    // Write any incomplete buffer to flash
    if(g_flash_buf_offset)
    {
        do_flash_write();
    }
    g_flash_buf_offset = 0;
    g_flash_write_addr = 0;
}

void add_header_checksum(t_log_sector_header* header)
{
    header->checksum = 0;
    header->checksum += (header->log_session & 0xff00) >> 8;
    header->checksum += (header->log_session & 0x00ff) >> 0;
    header->checksum += (header->seq_num & 0xff00) >> 8;
    header->checksum += (header->seq_num & 0x00ff) >> 0;
    header->checksum += (header->inv_seq_num & 0xff00) >> 8;
    header->checksum += (header->inv_seq_num & 0x00ff) >> 0;
}

void add_entry_checksum(t_log_entry* entry)
{
    entry->checksum = 0;
    entry->checksum += (entry->bus_voltage & 0xff00) >> 8;
    entry->checksum += (entry->bus_voltage & 0x00ff) >> 0;
    entry->checksum += (entry->shunt_voltage & 0xff00) >> 8;
    entry->checksum += (entry->shunt_voltage & 0x00ff) >> 0;
}

void write_log_header(void)
{
    uint8_t i;
    uint8_t* p = (uint8_t*) &g_current_log_header;

    //uart_tx_str(__func__); PRINT_CSTR("\r\n");

    g_current_log_header.seq_num++;
    g_current_log_header.inv_seq_num = g_current_log_header.seq_num ^ 0xffff;
    add_header_checksum(&g_current_log_header);

    // Copy to buffer
    for(i=0; i<sizeof(t_log_sector_header); i++)
        flash_page_write_buffer[g_flash_buf_offset++] = *(p++);
}


void fs_write_log_entry(t_log_entry* entry)
{
    uint8_t i;
    uint8_t* p = (uint8_t*) entry;

    //uart_tx_str(__func__); PRINT_CSTR("\r\n");

    add_entry_checksum(entry);

    //PRINT_CSTR("Entry offset: "); uart_hex_16(g_flash_buf_offset); PRINT_CSTR(" addr: "); uart_hex_32(g_flash_write_addr); PRINT_CSTR("\r\n");

    if(0 == g_flash_buf_offset)
    {
        // Reset page buffer
        clear_page_write_buffer();
        if(IS_SECTOR_START(g_flash_write_addr))
        {
            //PRINT_CSTR("Sector start, write header: "); uart_hex_32(g_flash_write_addr);PRINT_CSTR("\r\n");
            // Erase sector.
            do_flash_sector_erase(g_flash_write_addr);
            // Write sector header.
            write_log_header();
        }
    }

    // Note: assumes (header + entry) < page size.
    // Add data to flash buffer
    for(i=0; i<sizeof(t_log_entry); i++)
    {
        flash_page_write_buffer[g_flash_buf_offset++] = *(p++);
    }

    // If not enough space in the flash buffer for another entry then write it.
    if( (g_flash_buf_offset + sizeof(t_log_entry)) > FLASH_PAGE_SIZE )
    {
        //flash_dump_write_page_buffer();
        //PRINT_CSTR("Writing page: ");uart_hex_32(g_flash_write_addr);PRINT_CSTR("\r\n");

        do_flash_write();
        g_flash_buf_offset = 0;
        g_flash_write_addr += FLASH_PAGE_SIZE;
        // Just wrap to the start of flash, all enties should be sequencial
        if(g_flash_write_addr >= FLASH_SIZE)
            g_flash_write_addr = 0;
    }
}

static void print_header(t_log_sector_header* header)
{
    PRINT_CSTR("session:");     uart_hex_16(header->log_session);
    PRINT_CSTR(" seq:");        uart_hex_16(header->seq_num);
    PRINT_CSTR(" inv_seq:");    uart_hex_16(header->inv_seq_num);
    PRINT_CSTR(" checksum:");   uart_hex_8(header->checksum);
    PRINT_CSTR("\r\n");
}

static void print_entry(t_log_entry* entry)
{
    PRINT_CSTR("VBUS:");    uart_hex_16(entry->bus_voltage);
    PRINT_CSTR(" ");
    PRINT_CSTR("VSHUNT:");  uart_hex_16(entry->shunt_voltage);
    PRINT_CSTR("\r\n");
}


// Scan the entries in a sector starting at a given page address (addr) and
// offset after that address (read_offset), call a callback (call_back) with
// log entries found.
static void scan_entries_in_sector(uint32_t addr, uint16_t read_offset, entry_cb call_back)
{
    t_log_entry* entry;

    do
    {
        entry = (t_log_entry*)(flash_page_read_buffer + read_offset);
        if(! is_log_entry_empty(entry))
        {
            if(is_log_entry_checksum_valid(entry))
            {
                call_back(entry);
            }
            else
            {
                PRINT_CSTR("Invalid entry header at addr: "); uart_hex_32(addr);PRINT_CSTR("\r\n");
            }
        }
        read_offset += sizeof(t_log_entry);

        // If no more space in buffer for another entry
        if( (read_offset + sizeof(t_log_entry)) > FLASH_PAGE_SIZE )
        {
            //PRINT_CSTR("Page addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
            addr += FLASH_PAGE_SIZE;
            // If not on sector boundary
            if(addr & FLASH_SECTOR_MASK) // Optimisaion
                flash_read_page_buffer(addr);
            read_offset = 0;
        }
    }
    while( (addr + read_offset) & FLASH_SECTOR_MASK);
    // While not on a sector boundary
    //TODO remove this debug: PRINT_CSTR("end loop addr:"); uart_hex_32(addr); PRINT_CSTR(" read:"); uart_hex_16(read_offset); PRINT_CSTR("\r\n");
}

void fs_scan_entries_print(void)
{
    uint32_t addr = 0;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;

    for(addr=0; addr < FLASH_SIZE; addr += FLASH_SECTOR_SIZE)
    {
        flash_read_page_buffer(addr);
        if(! is_header_empty(header) )
        {
            PRINT_CSTR("Sector addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
            if(is_header_valid(header))
            {
                print_header(header);
                scan_entries_in_sector(addr, sizeof(t_log_sector_header), print_entry);
            }
            else
            {
                PRINT_CSTR("Invalid sector header at addr:"); uart_hex_32(addr);PRINT_CSTR("\r\n");
            }
        }
    }
}
void print_entry_minimal(t_log_entry* entry)
{
    uart_hex_16(entry->bus_voltage);
    PRINT_CSTR(":");
    uart_hex_16(entry->shunt_voltage);
    PRINT_CSTR("\r\n");
}

void fs_print_session(uint16_t session)
{
    uint32_t addr = 0;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;

    //TODO Should we add user data to the callback to record the number of entries?
    if(find_session_start(session, &addr))
    {
        // Failed to find the session
        return;
    }

    // For every sector after this point
    while(addr < FLASH_SIZE)
    {
        flash_read_page_buffer(addr);
        if( (!is_header_empty(header)) &&
            (is_header_valid(header))  &&
            (header->log_session == session) )
        {
            scan_entries_in_sector(addr, sizeof(t_log_sector_header), print_entry_minimal);
        }
        else
        {
            return;
        }
        addr += FLASH_SECTOR_SIZE;
    }
}

// Find the first entry of a session and return the header address
// return 0 on success and 1 on failure.
uint8_t find_session_start(uint16_t session, uint32_t* find_addr)
{
    uint32_t addr = 0;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;
    uint8_t found = 0;
    uint16_t min_seq_num = 0xffff;
    *find_addr = 0;

    // For each sector.
    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        flash_read_page_buffer(addr);
        // Does it have a valid header and the session we are looking for
        if( !is_header_empty(header) &&
            is_header_valid(header)  &&
            (header->log_session == session) )
        {
            if(header->seq_num < min_seq_num)
            {
                PRINT_CSTR("Found smaller at addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
                min_seq_num = header->seq_num;
                *find_addr = addr;
                found = 1;
            }
        }
    }

    if(found)
        return 0;
    else
        return 1;
}

// Deletes all log sessions with a non-empty session header (no erasing if already erased).
void fs_delete_all(void)
{
    uint32_t addr = 0;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;

    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        // Read the next sector header into page buffer.
        flash_read_page_buffer(addr);
        if(! is_header_empty(header) )
        {
            do_flash_sector_erase(addr);
        }
    }
}

void fs_scan_sector_print_headers(void)
{
    uint32_t addr = 0;
    uint16_t sector = 0;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;

    for(addr=0; addr<FLASH_SIZE; addr+=FLASH_SECTOR_SIZE)
    {
        // Read the next sector header into page buffer.
        flash_read_page_buffer(addr);
        if(! is_header_empty(header) )
        {
            PRINT_CSTR("Sector 0x");        uart_hex_16(sector);
            PRINT_CSTR(" header addr: ");   uart_hex_32(addr);PRINT_CSTR("\r\n");
            print_header(header);
        }
        sector++;
    }
}


static uint8_t is_header_valid(t_log_sector_header* header)
{
    uint8_t checksum = 0;
    checksum += (header->log_session & 0xff00) >> 8;
    checksum += (header->log_session & 0x00ff) >> 0;
    checksum += (header->seq_num & 0xff00) >> 8;
    checksum += (header->seq_num & 0x00ff) >> 0;
    checksum += (header->inv_seq_num & 0xff00) >> 8;
    checksum += (header->inv_seq_num & 0x00ff) >> 0;

    if(checksum == header->checksum)
        return 1;
    else
        return 0;
}

static uint8_t is_log_entry_checksum_valid(t_log_entry* entry)
{
    uint8_t checksum = 0;
    checksum += (entry->bus_voltage & 0xff00) >> 8;
    checksum += (entry->bus_voltage & 0x00ff) >> 0;
    checksum += (entry->shunt_voltage & 0xff00) >> 8;
    checksum += (entry->shunt_voltage & 0x00ff) >> 0;

    if(checksum == entry->checksum)
        return 1;
    else
        return 0;
}

static uint8_t is_header_empty(t_log_sector_header* header)
{
    if( (header->seq_num     == 0xffff) &&
        (header->inv_seq_num == 0xffff) )
    {
        return 1;
    }
    return 0;
}

static uint8_t is_entry_empty(t_log_entry* entry)
{
    if( (entry->bus_voltage     == 0xffff) &&
        (entry->shunt_voltage   == 0xffff) &&
        (entry->checksum        == 0xff))
    {
        return 1;
    }
    return 0;
}

static uint8_t is_log_entry_empty(t_log_entry* entry)
{
    if( (entry->bus_voltage    == 0xffff ) &&
        (entry->shunt_voltage  == 0xffff ) &&
        (entry->checksum       == 0xff   ) )
    {
        return 1;
    }
    return 0;
}

static void clear_page_write_buffer(void)
{
    uint16_t i;
    uint8_t* p = (uint8_t*)flash_page_write_buffer;

    for(i=0; i<FLASH_PAGE_SIZE; i++)
        *(p++) = 0xff;
}

//******************** Test Code *******************

uint16_t test_data_bus_voltage      = 0;
uint16_t test_data_shunt_voltage    = 0;
uint16_t test_data_valid_entries    = 0;
uint16_t test_data_empty_entries    = 0;
uint16_t test_data_invalid_entries  = 0;

void test1_entry_check_cb(t_log_entry* entry)
{
    if( (entry->bus_voltage   == test_data_bus_voltage  ) &&
        (entry->shunt_voltage == test_data_shunt_voltage) )
    {
        test_data_valid_entries++;
    }
    else if(is_entry_empty(entry))
    {
        test_data_empty_entries++;
    }
    else
    {
        test_data_invalid_entries++;
        print_entry(entry);
    }
    test_data_bus_voltage++;
    test_data_shunt_voltage++;
}


// Write a session header in sector 0
void test_write_entries_with_verify(uint32_t addr_start,
                        uint16_t session,
                        uint16_t bus_v_start,
                        uint16_t shunt_v_start)
{
    uint32_t addr;
    t_log_entry entry;
    uint16_t count;
    t_log_sector_header* header = (t_log_sector_header*) flash_page_read_buffer;
    uint8_t searching;
    char* p;

    entry.bus_voltage = bus_v_start;
    entry.shunt_voltage = shunt_v_start;

    g_current_log_header.log_session = session;
    g_current_log_header.seq_num     = 1;
    g_current_log_header.inv_seq_num = 1 ^ 0xffff;

    // Start at the last sector in flash
    g_flash_write_addr = addr_start;

    for(count=0; count<1000; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }

    fs_end_log_session();

    // Find the start the session in flash.
    if(0 == find_session_start(session, &addr))
    {
        PRINT_CSTR("Session found at addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
        test_data_bus_voltage       = bus_v_start;
        test_data_shunt_voltage     = shunt_v_start;
        test_data_valid_entries     = 0;
        test_data_empty_entries     = 0;
        test_data_invalid_entries   = 0;
        searching = 1;

        while(searching)
        {
            //PRINT_CSTR("Next sector at addr: ");uart_hex_32(addr);PRINT_CSTR("\r\n");
            flash_read_page_buffer(addr);
            // If we have a valid sector header for this session scan the entries.
            if( !is_header_empty(header) &&
                is_header_valid(header)  &&
                (header->log_session == session) )
            {
                scan_entries_in_sector(addr, sizeof(t_log_sector_header), test1_entry_check_cb);
            }
            else
            {
                searching = 0;
            }
            addr += FLASH_SECTOR_SIZE;

            if(addr >= FLASH_SIZE)
                addr = 0;
        }
        // Search complete, check the results.
        PRINT_CSTR("Valid entries: "); p = uint16_toa(test_data_valid_entries); uart_tx_str(p); PRINT_CSTR("\r\n");
        PRINT_CSTR("Empty entries: "); p = uint16_toa(test_data_empty_entries); uart_tx_str(p); PRINT_CSTR("\r\n");
        PRINT_CSTR("Invalid entries: "); p = uint16_toa(test_data_invalid_entries); uart_tx_str(p); PRINT_CSTR("\r\n");
    }
    else
    {
        PRINT_CSTR("Unable to find log session\r\n");
    }
}

void fs_test1(void)
{
    // Write 1000 incrementing log entries starting at a specific location.
    test_write_entries_with_verify(0, 1, 0x10, 0x20);
}

// Write the last sector in flash and wrap into the next sector (first)
void fs_test2(void)
{
    // Write 1000 incrementing log entries starting at a specific location.
    test_write_entries_with_verify(FLASH_SIZE - FLASH_SECTOR_SIZE, 52, 0x1000, 0x2000);
}

void fs_test1_reset(void)
{
    // Erase the first two sectors of flash.
    do_flash_sector_erase(0);
    do_flash_sector_erase(FLASH_SECTOR_SIZE);
}

void fs_test2_reset(void)
{
    // Erase first and last
    do_flash_sector_erase(0);
    do_flash_sector_erase(FLASH_SIZE - FLASH_SECTOR_SIZE);
}

// Start and stop a large number of log sessions
void fs_test3(void)
{
    t_log_entry entry;
    uint32_t count;

    // First entry page  :
    //  page size - header size / entry size = (256 - 7) / 5 = 49.8 = 49
    // Next entries page :
    //  page size / entry size = 256 / 5 = 51.2 = 51
    // Entries per sector:
    //  (1 * 49) + (15 * 51) = 814
    // Sector size = 4K = 16 pages
    // Flash size = 8M = 2048 sectors

    // SECTOR 0
    // Address: 0
    // The flash is empty.
    // The first session should start at the start of flash and fill an entire sector.
    // Fill 16 pages, page 1 has 49 entries, page 2-16 have 51 entries:
    // 49 + (15 * 51) = 814
    PRINT_CSTR("Session 0\r\n");
    entry.bus_voltage = 0;
    entry.shunt_voltage = 0;
    fs_start_log_session();
    for(count=0; count<814; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }
    fs_end_log_session();

    // SECTOR 1
    // Address: python -c "print hex(1*4096)"  = 0x1000
    // Write a small session 5.5 pages
    // 49 + (4.5 * 51) = 278.5 = 278
    PRINT_CSTR("Session 1\r\n");
    entry.bus_voltage = 0x1000;
    entry.shunt_voltage = 0x1000;
    fs_start_log_session();
    for(count=0; count<278; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }
    fs_end_log_session();

    // SECTOR 2 -> 1000
    // Address: python -c "print hex(2*4096)"  = 0x2000
    // 999 * 814 = 813186
    // Write a massive session 
    PRINT_CSTR("Session 2\r\n");
    entry.bus_voltage = 0x2000;
    entry.shunt_voltage = 0x2000;
    fs_start_log_session();
    for(count=0; count<813186; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }
    fs_end_log_session();

    // SECTOR 3 1001 -> 2000 
    // Address: python -c "print hex((2+999)*4096)" = 0x3e9000
    // 1000 * 814 = 814000
    PRINT_CSTR("Session 3\r\n");
    entry.bus_voltage = 0x3000;
    entry.shunt_voltage = 0x3000;
    fs_start_log_session();
    for(count=0; count<814000; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }
    fs_end_log_session();

    // SECTOR 2001 -> 2047 -> 5
    // Address: python -c "print hex((2+999+1000)*4096)" = 0x7d1000
    // 47 + 6 = 53 sectors
    // 53 * 814 = 43142
    // Write past the end and wrap into next sector
    PRINT_CSTR("Session 4\r\n");
    entry.bus_voltage = 0x4000;
    entry.shunt_voltage = 0x4000;
    fs_start_log_session();
    for(count=0; count<43142; count++)
    {
        fs_write_log_entry(&entry);
        entry.bus_voltage++;
        entry.shunt_voltage++;
    }
    fs_end_log_session();
}

