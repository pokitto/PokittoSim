/**************************************************************************/
/*!
    @file     UIWidgetBasic.cpp
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

#include "PokittoDisplay.h"
#include "UIWidget.h"

#define UIWIDGET_KEYBOARD_W 8
#define UIWIDGET_KEYBOARD_H 8

using namespace Pokitto;

// WidgetBase class.
WidgetBase::WidgetBase(uint32_t flags){
    setRect(0, 0, 0, 0);
    m_flags = flags;
    m_titleText = nullptr;
    m_vkbText = nullptr;
}

WidgetBase::~WidgetBase(){
    free(m_titleText);
    free(m_vkbText);
}

void WidgetBase::getViewRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h) {

    if (m_flags & Flags::hasBorders) {
        x = m_x + fontW; y = m_y + fontH; w = m_w - (2 * fontW); h = m_h - (2 * fontH);
        if( m_titleText ) {
            x = x; y = y + (2 * fontH); w = w; h = h - (2 * fontH);
        }
    }
    else {
        x = m_x; y = m_y; w = m_w; h = m_h;
    }
}

void WidgetBase::setTitle(char* titleText) {

    m_titleText = (char*)malloc(strlen(titleText) + 1);
    strcpy(m_titleText, titleText);
}

void WidgetBase::draw() {

    // Clear
    uint16_t currColor = Display::color;
    Display::color = LB_BACKGROUND_COLOR;
    Display::fillRectangle(m_x, m_y, m_w, m_h);
    Display::color = currColor;

    // Draw borders
    if (m_titleText) {
        if (m_flags & Flags::hasBorders)
            drawBorders(m_x, m_y + (2 * fontH), m_w, m_h - (2 * fontH));
     }
    else {
        if (m_flags & Flags::hasBorders)
            drawBorders(m_x, m_y, m_w, m_h);
    }

    // Draw title
    drawTitle();
}

void WidgetBase::drawBorders(int16_t x, int16_t y, int16_t w, int16_t h) {

    uint16_t currColor = Display::color;
    Display::color = LB_BORDER_COLOR;

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
        Display::print(x1,y1,' ');
        y1+=fontH;
        Display::print(x1,y1,' ');
        y1+=fontH;
        Display::print(x1,y1,' ');
        y1+=fontH;
        Display::print(x1,y1,'f');

        // Left side
        y1=y+((numCharsInCol*5/6)-3)*fontH;
        Display::print(x2,y1,'f');
        y1+=fontH;
        Display::print(x2,y1,' ');
        y1+=fontH;
        Display::print(x2,y1,' ');
        y1+=fontH;
        Display::print(x2,y1,' ');
        y1+=fontH;
        Display::print(x2,y1,'f');
   }

    // Restore original color.
    Display::color = currColor;
}

void WidgetBase::drawTitle() {

    if (m_titleText) {

        int16_t titleLen = strlen(m_titleText);
        int16_t numCharsInLine = titleLen;

        // Draw top border.
        int16_t x1 = m_x;
        Display::print(x1,m_y,'a');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print('b');
        Display::print('c');

        // Draw 2nd line: text and left and right borders.
        int16_t y=m_y+fontH;
        Display::print(x1,y,'|');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print(m_titleText[i]);

        //Display::print(m_ptitle);
        Display::print('|');

        // Draw 3rd line.
        Display::print(m_x,m_y+(2*fontH),'|');
        for (int16_t i = 0; i < numCharsInLine; i++)
            Display::print(' '); // space
        Display::print('d');
   }
}

void WidgetBase::keyboardInit(char* ptext) {

    // Store text
    free(m_vkbText);
    m_vkbText = nullptr;
    m_vkbText = (char*)malloc(strlen(ptext+1)); // space for '\0' also
    strcpy(m_vkbText, ptext);

	//active character in the typing area
	m_vkbTextLenWithNull = strlen(m_vkbText) + 1;
	m_vkbActiveChar = 0;
	//selected char on the keyboard
	m_vkbActiveX = 0;
	m_vkbActiveY = 2;
	//position of the keyboard on the screen
	m_vkbCurrentX = LCDWIDTH;
	m_vkbCurrentY = LCDHEIGHT;
	m_vkbEnd = false;
}

void WidgetBase::keyboardUpdate() {

    //move the character selector
    if (Buttons::repeat(BTN_DOWN, 4)) {
        m_vkbActiveY++;
        Sound::playTick();
    }
    if (Buttons::repeat(BTN_UP, 4)) {
        m_vkbActiveY--;
        Sound::playTick();
    }
    if (Buttons::repeat(BTN_RIGHT, 4)) {
        m_vkbActiveX++;
        Sound::playTick();
    }
    if (Buttons::repeat(BTN_LEFT, 4)) {
        m_vkbActiveX--;
        Sound::playTick();
    }
    //don't go out of the keyboard
    if (m_vkbActiveX == UIWIDGET_KEYBOARD_W) m_vkbActiveX = 0;
    if (m_vkbActiveX < 0) m_vkbActiveX = UIWIDGET_KEYBOARD_W - 1;
    if (m_vkbActiveY == UIWIDGET_KEYBOARD_H) m_vkbActiveY = 0;
    if (m_vkbActiveY < 0) m_vkbActiveY = UIWIDGET_KEYBOARD_H - 1;

    //set the keyboard position on screen
    int8_t targetX = -(Display::fontWidth+1) * m_vkbActiveX + LCDWIDTH / 2 - 3;
    int8_t targetY = -(Display::fontHeight+1) * m_vkbActiveY + LCDHEIGHT / 2 - 4 - Display::fontHeight;

    //smooth the keyboard displacement
    m_vkbCurrentX = (targetX + m_vkbCurrentX) / 2;
    m_vkbCurrentY = (targetY + m_vkbCurrentY) / 2;

    //type character
    int8_t startChar = 32;
    if (Buttons::pressed(BTN_A)) {
        if (m_vkbActiveChar < m_vkbTextLenWithNull-1) {
            byte thisChar = m_vkbActiveX + (UIWIDGET_KEYBOARD_W * m_vkbActiveY) + startChar;
            //if((thisChar == 0)||(thisChar == 10)||(thisChar == 13)) //avoid line feed and carriage return
            //continue;
            m_vkbText[m_vkbActiveChar] = thisChar;
            m_vkbText[m_vkbActiveChar+1] = '\0';
        }
        m_vkbActiveChar++;
        Sound::playOK();
        if (m_vkbActiveChar > m_vkbTextLenWithNull-1)
        m_vkbActiveChar = m_vkbTextLenWithNull-1;
    }
    //erase character
    if (Buttons::pressed(BTN_B)) {
        m_vkbActiveChar--;
        Sound::playCancel();
        if (m_vkbActiveChar >= 0)
        m_vkbText[m_vkbActiveChar] = 0;
        else
        m_vkbActiveChar = 0;
    }
    //leave keyboard
    if (Buttons::pressed(BTN_C)) {
        Sound::playOK();
        m_vkbEnd = true;
    }
}

void WidgetBase::keyboardDraw() {

    //draw the keyboard
    int8_t startChar = 32, numChars = 64;
    Display::setColor(LB_ITEM_COLOR);
    int8_t x = 0, y = 0;
    for (y = 0; y < UIWIDGET_KEYBOARD_H && (x + (y * UIWIDGET_KEYBOARD_W)) <= numChars; y++) {
        for (x = 0; x < UIWIDGET_KEYBOARD_W && (x + (y * UIWIDGET_KEYBOARD_W)) <= numChars; x++) {
            Display::drawChar(m_vkbCurrentX + x * (Display::fontWidth+1), m_vkbCurrentY + y * (Display::fontHeight+1), startChar + x + y * UIWIDGET_KEYBOARD_W, 1);
        }
    }

    //draw instructions
    Display::setColor(LB_SELECTED_ITEM_COLOR);
    Display::cursorX = m_vkbCurrentX-Display::fontWidth*5+1;
    Display::cursorY = m_vkbCurrentY+1*(Display::fontHeight+1);
    Display::print(F("A=SEL"));

    Display::cursorX = m_vkbCurrentX-Display::fontWidth*5+1;
    Display::cursorY = m_vkbCurrentY+2*(Display::fontHeight+1);
    Display::print(F("B=DEL"));

    Display::cursorX = m_vkbCurrentX-Display::fontWidth*5+1;
    Display::cursorY = m_vkbCurrentY+3*(Display::fontHeight+1);
    Display::print(F("C=END"));

    //erase some pixels around the selected character
    Display::setColor(LB_BACKGROUND_COLOR);
    Display::drawFastHLine(m_vkbCurrentX + m_vkbActiveX * (Display::fontWidth+1) - 1, m_vkbCurrentY + m_vkbActiveY * (Display::fontHeight+1) - 2, 7);
    //draw the selection rectangle
    Display::setColor(LB_SELECTED_ITEM_COLOR);
    Display::drawRoundRect(m_vkbCurrentX + m_vkbActiveX * (Display::fontWidth+1) - 2, m_vkbCurrentY + m_vkbActiveY * (Display::fontHeight+1) - 3, (Display::fontWidth+2)+(Display::fontWidth-1)%2, (Display::fontHeight+5), 3);

    Display::setColor(LB_BACKGROUND_COLOR);
    Display::fillRect(0, LCDHEIGHT-(2*Display::fontHeight)-1, LCDWIDTH, Display::fontHeight+1);

    //Draw typed text
    Display::setColor(LB_SELECTED_ITEM_COLOR);
    Display::cursorX = Display::fontWidth;
    Display::cursorY = LCDHEIGHT-(2*Display::fontHeight)+3;
    Display::setColor(BLACK);
    Display::print(m_vkbText);

    //blinking cursor
    if (((Core::frameCount % 8) < 4) && (m_vkbActiveChar < (m_vkbTextLenWithNull-1)))
        Display::drawChar((Display::fontWidth) * m_vkbActiveChar + Display::fontWidth, LCDHEIGHT-(2*Display::fontHeight)+3, '_',1);
}


