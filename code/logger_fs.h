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
// File Name: logger_fs.h
//

#include <inttypes.h>


typedef struct
{
    uint16_t bus_voltage;           // Raw register value
    uint16_t shunt_voltage;         // Raw register value
    uint8_t checksum;               // Internal use only
}t_log_entry;


void fs_init(void);

void fs_start_log_session(void);
void fs_end_log_session(void);
void fs_write_log_entry(t_log_entry* entry);
void fs_delete_all(void);

// Search for the presence of a header in each sector
// and dump results.
void fs_scan_sector_print_headers(void);
void fs_scan_entries_print(void);
void fs_print_session(uint16_t session);


void fs_test1(void);
void fs_test1_reset(void);
void fs_test2(void);
void fs_test2_reset(void);
void fs_test3(void);

