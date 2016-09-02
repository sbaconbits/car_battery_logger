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
// File Name: hw_io.h
//

#ifndef HW_IO_H
#define HW_IO_H

#include <avr/io.h>

#define LED_ACT_ON          (PORTB |=  (1 << PB0))
#define LED_ACT_OFF         (PORTB &= ~(1 << PB0))
#define LED_ACT_TOGGLE      (PORTB ^=  (1 << PB0))

#define LED_TRG_ON          (PORTD |=  (1 << PD6))
#define LED_TRG_OFF         (PORTD &= ~(1 << PD6))
#define LED_TRG_TOGGLE      (PORTD ^=  (1 << PD6))


#define BUTTON_MODE_PRESSED     ( !(PIND & (1 << PD7)) )
#define BUTTON_TRG_RST_PRESSED  ( !(PIND & (1 << PD5)) )

//PB0 - LED Activity            (red, D1)
//PD7 - Button start/stop       (START/STOP SW1)
//PD6 - LED triggered           (white D2)
//PD5 - Button reset trigger    (RESET SW2)


#endif //HW_IO_H
