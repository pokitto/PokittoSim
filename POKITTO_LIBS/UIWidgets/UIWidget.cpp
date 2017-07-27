/**************************************************************************/
/*!
    @file     UIWidget.cpp
    @author   Hannu Viitala.
    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2017, Jonne Valola
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

#if PROJ_WINDOWS
#include "defines_win_SIM.h"
#endif

#if PROJ_LINUX
#include "defines_linux_SIM.h"
#endif

#include "Pokitto.h"
#include "PokittoDisk.h"
#ifdef POK_SIM
#include "FileIO.h"
#endif


#include "Pokittodisplay.h"
#include "UIWidget.h"

using namespace Pokitto;

// WidgetBase class.

void WidgetBase::draw() {

    // Clear
    uint16_t currColor = Display::color;
    Display::color = 0;
    Display::fillRectangle(m_x, m_y, m_w, m_h);
    Display::color = currColor;

    // Draw borders.
    if (m_flags & Flags::hasBorders)
        drawBorders(m_x, m_y, m_w, m_h);
}

void WidgetBase::drawBorders(int16_t x, int16_t y, int16_t w, int16_t h) {

    int16_t numCharsInLine = (w/fontW) + 1;
    numCharsInLine-=2;
    if(numCharsInLine<0)
        return;
    int16_t numCharsInCol = (h/fontH) + 1;
    numCharsInCol-=2;
    if(numCharsInCol<0)
        return;

    // Draw top border
    Display::print(x,y,'a');
    for (int16_t i = 0; i < numCharsInLine; i++)
        Display::print('b');
    Display::print(x+w-fontW,y,'c');

    // Draw left and right borders
    int16_t x1=x, x2=x+w-fontW, y1=y+fontH;
    for (int16_t i = 0; i < numCharsInCol; i++, y1+=fontH) {
        Display::print(x1,y1,'|');
        Display::print(x2,y1,'|');
    }

    // Draw bottom border
    Display::print(x,y+h-fontH,'d');
    for (int16_t i = 0; i < numCharsInLine; i++)
        Display::print('b');
    Display::print(x+w-fontW,y+h-fontH,'e');

    // Draw dots decoration on left and right sides
    if (numCharsInCol > 7) {

        // Right side
        y1=y+((numCharsInCol/2)-3)*fontH;
        Display::print(x1,y1,'f');
        y1+=fontH;
        Display::print(x1,y1,'i');
        y1+=fontH;
        Display::print(x1,y1,'i');
        y1+=fontH;
        Display::print(x1,y1,'i');
        y1+=fontH;
        Display::print(x1,y1,'f');

        // Left side
        y1=y+((numCharsInCol*5/6)-3)*fontH;
        Display::print(x2,y1,'f');
        y1+=fontH;
        Display::print(x2,y1,'i');
        y1+=fontH;
        Display::print(x2,y1,'i');
        y1+=fontH;
        Display::print(x2,y1,'i');
        y1+=fontH;
        Display::print(x2,y1,'f');
   }
}

// Window class.

void Window::draw() {

    // Clear
    uint16_t currColor = Display::color;
    Display::color = 0;
    Display::fillRectangle(m_x,m_y,m_w,m_h);
    Display::color = currColor;

     if (m_ptitle)
        drawBorders(m_x,m_y+(2*fontH),m_w,m_h-(2*fontH));
    else
        drawBorders(m_x,m_y,m_w,m_h);

    drawTitle();
}

void Window::drawTitle() {

    if (m_ptitle) {

        int16_t titleLen = strlen(m_ptitle);
        int16_t numCharsInLine = titleLen;

        // Draw top border.
        int16_t x1=m_x, x2=m_x+((numCharsInLine-1) * fontW);
        Display::print(x1,m_y,'a');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print('b');
        Display::print('c');

        // Draw 2nd line: text and left and right borders.
        int16_t y=m_y+fontH;
        Display::print(x1,y,'|');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print(m_ptitle[i]);

        //Display::print(m_ptitle);
        Display::print('|');

        // Draw 3rd line.
        Display::print(m_x,m_y+(2*fontH),'|');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print('i'); // space
        Display::print('d');
   }

}
