/**************************************************************************/
/*!
    @file     SimLCD.h
    @author   Jonne Valola

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Jonne Valola
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef POKLCD_H
#define POKLCD_H

#include <stdint.h>

namespace Pokitto {

/** Initialize display hardware */
extern void lcdInit();
/** Clear display hardware */
extern void lcdClear();
/** Set DRAM pointer */
extern inline void setDRAMptr(uint16_t,uint16_t);
/** Setup display datalines */
extern inline void setup_data_16(uint16_t);
/** Blit one word of data*/
extern void blitWord(uint16_t);
/** Toggle write line */
extern inline void toggle_data();
/** Directly fill the lcd with a color (no buffering) */
extern void lcdFillSurface(uint16_t);
/** Directly draw a pixel in a position (no buffering) */
extern void lcdPixel(int16_t,int16_t,uint16_t);
/** Directly fill a rectangle (x0,y0,x1,y1) in a position (no buffering) */
extern void lcdRectangle(int16_t,int16_t,int16_t,int16_t,uint16_t);
/** Update LCD from native Mode 1 */
extern void lcdRefreshMode1(uint8_t*, uint16_t*);
/** Update LCD from native Mode 2 */
extern void lcdRefreshMode2(uint8_t*, uint16_t*);
/** Update LCD from Gamebuino mode*/
extern void lcdRefreshGB(uint8_t* , uint16_t*);
/** Update LCD from Arduboy mode */
extern void lcdRefreshAB(uint8_t*, uint16_t*);
/** Update LCD from Lamenes mode */
extern void lcdRefreshModeLamenes(uint8_t*, uint16_t*);
/** Update LCD from Gameboy mode*/
extern void lcdRefreshModeGBC(uint8_t* , uint16_t*);

}

#endif // POKLCD_H
