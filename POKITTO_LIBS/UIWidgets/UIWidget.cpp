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

#include "PokittoDisplay.h"
#include "UIWidget.h"
#include <new>

using namespace Pokitto;

// InfoDlg class.

InfoDlg::InfoDlg(char* ptext)
: DialogBase(WidgetBase::hasBorders) {

    m_ptext = NULL;
    m_okText = NULL;

    init(ptext, nullptr);
}

InfoDlg::InfoDlg(char* ptext, char* okText)
: DialogBase(WidgetBase::hasBorders) {

    m_ptext = NULL;
    m_okText = NULL;

    init(ptext, okText);
}

InfoDlg::~InfoDlg() { free(m_ptext); }

void InfoDlg::init(char* ptext, char* okText) {

    // Store text
    m_ptext = (char*)malloc(strlen(ptext)+1);
    strcpy(m_ptext, ptext);

    // Store "ok" text
    if(okText) {
        m_okText = (char*)malloc(strlen(okText)+1);
        strcpy(m_okText, okText);
    }
    else {
        m_okText = (char*)malloc(strlen(STR_OK)+1);
        strcpy(m_okText, STR_OK);
    }

    // Set rect.
    const int32_t dlgW = Display::getWidth()*2/3;
    const int32_t dlgH = 10 * fontH;
    setRect((Display::getWidth()- dlgW) / 2, (Display::getHeight() - dlgH) / 2, dlgW, dlgH);

}

void InfoDlg::draw() {

    update();

    WidgetBase::draw();

    uint16_t currColor = Display::color;
    Display::color = LB_SELECTED_ITEM_COLOR;

    // Draw little Pokitto!
    int16_t vx, vy, vw, vh;
    getViewRect(vx, vy, vw, vh);
    int16_t x = ((vw - (4*fontW)) / 2); // centralize
    int16_t y = 0;
    Display::print(vx + x,vy + y,"ijkl");
    y+=fontH;
    Display::print(vx + x,vy + y,"mnop");
    y+=fontH;
    Display::print(vx + x,vy + y,"qrst");
    y+=fontH;
    Display::print(vx + x,vy + y,"uvwx");
    y+=fontH;

    // One empty line
    y+=fontH;

    // Draw text
    Display::color = LB_ITEM_COLOR;
    int16_t len = strlen(m_ptext);
    x = ((vw - (len*fontW)) / 2); // centralize
    Display::print(vx + x, vy + y, m_ptext);

    // One empty line
    y+=fontH;

    // Draw OK button
    Display::color = LB_SELECTED_ITEM_COLOR;
    len = strlen(m_okText);
    x = ((vw - (len*fontW)) / 2); // centralize
    y+=fontH;Display::
    Display::print(vx + x, vy  + y, m_okText);

    // Restore original color.
    Display::color = currColor;
}

// Note: the object can be destroyed during this call!
void InfoDlg::update() {

    if(!m_done) {

        if( Core::buttons.pressed(BTN_A) ) {

            // Done with the dialog
            m_done = true;
        }
   }
}

// CancelDlg class.

CancelDlg::CancelDlg(char* ptext)
: DialogBase(WidgetBase::hasBorders) {

    m_ptext = NULL;

    init(ptext, nullptr, nullptr);
}

CancelDlg::CancelDlg(char* ptext, char* okText, char* cancelText)
: DialogBase(WidgetBase::hasBorders) {

    m_ptext = NULL;

    init(ptext, okText, cancelText);
}

CancelDlg::~CancelDlg() { free(m_ptext); }

void CancelDlg::init(char* ptext, char* okText, char* cancelText) {

    // Store text
    m_ptext = (char*)malloc(strlen(ptext)+1);
    strcpy(m_ptext, ptext);

    // Store "ok" text
    if(okText) {
        m_okText = (char*)malloc(strlen(okText)+1);
        strcpy(m_okText, okText);
    }
    else {
        m_okText = (char*)malloc(strlen(STR_OK)+1);
        strcpy(m_okText, STR_OK);
    }

    // Store "cancel" text
    if(cancelText) {
        m_cancelText = (char*)malloc(strlen(cancelText)+1);
        strcpy(m_cancelText, cancelText);
    }
    else {
        m_cancelText = (char*)malloc(strlen(STR_CANCEL)+1);
        strcpy(m_cancelText, STR_CANCEL);
    }

    // Set rect.
    const int32_t dlgW = Display::getWidth()*2/3;
    const int32_t dlgH = 11 * fontH;
    setRect((Display::getWidth()- dlgW) / 2, (Display::getHeight() - dlgH) / 2, dlgW, dlgH);

}

void CancelDlg::draw() {

    update();

    WidgetBase::draw();

    uint16_t currColor = Display::color;
    Display::color = LB_ITEM_COLOR;

    // Draw little Pokitto!
    int16_t vx, vy, vw, vh;
    getViewRect(vx, vy, vw, vh);
    int16_t x = ((vw - (4*fontW)) / 2); // centralize
    int16_t y = 0;
    Display::print(vx + x,vy + y,"ijkl");
    y+=fontH;
    Display::print(vx + x,vy + y,"mnop");
    y+=fontH;
    Display::print(vx + x,vy + y,"qrst");
    y+=fontH;
    Display::print(vx + x,vy + y,"uvwx");
    y+=fontH;

    // One empty line
    y+=fontH;

    // Draw text
    int16_t len = strlen(m_ptext);
    x = ((vw - (len*fontW)) / 2); // centralize
    Display::print(vx + x, vy +  y, m_ptext);

    // One empty line
    y+=fontH;

    // Draw OK button
    Display::color = m_isOkSelected ? LB_SELECTED_ITEM_COLOR : LB_ITEM_COLOR;
    len = strlen(m_okText);
    x = ((vw - (len*fontW)) / 2); // centralize
    y+=fontH;
    Display::print(vx + x, vy  + y, m_okText);

    // Draw CANCEL button
    Display::color = (!m_isOkSelected) ? LB_SELECTED_ITEM_COLOR : LB_ITEM_COLOR;
    len = strlen(m_cancelText);
    x = ((vw - (len*fontW)) / 2); // centralize
    y+=fontH;
    Display::print(vx + x, vy  + y, m_cancelText);

    // Restore original color.
    Display::color = currColor;
}

// Note: the object can be destroyed during this call!
void CancelDlg::update() {

    if(!m_done) {

        // Done with the dialog?
        if( Core::buttons.pressed(BTN_A) )
            m_done = true;

        if (Core::buttons.pressed(BTN_UP) ||
            Core::buttons.pressed(BTN_DOWN) ||
            Core::buttons.pressed(BTN_LEFT) ||
            Core::buttons.pressed(BTN_RIGHT) ) {

            m_isOkSelected = !m_isOkSelected;  // Switch state
        }
    }
}

// TextInputDlg class.

TextInputDlg::TextInputDlg(char* ptext)
: DialogBase(WidgetBase::hasBorders) {

    init(ptext);
}

TextInputDlg::~TextInputDlg() {}

void TextInputDlg::init(char* ptext) {

    // Set rect.
    const int32_t dlgW = Display::getWidth()-1;
    const int32_t dlgH = Display::getHeight();
    setRect((Display::getWidth()- dlgW) / 2, (Display::getHeight() - dlgH) / 2, dlgW, dlgH);

    // Initialize virtual keyboard.
    keyboardInit(ptext);
}

void TextInputDlg::draw() {

    // Clear
    uint16_t currColor = Display::color;
    Display::color = LB_BACKGROUND_COLOR;
    Display::fillRectangle(m_x, m_y, m_w, m_h);
    Display::color = currColor;

    // Update and draw the virtual keyboard.
    keyboardUpdate();
    keyboardDraw();
    m_done = m_vkbEnd;

    // Clear the right edge (because e.g. display width 110 is not dividable by 8)
    currColor = Display::color;
    Display::color = LB_BACKGROUND_COLOR;
    Display::fillRectangle(Display::getWidth()-7, m_y, 7, m_h);
    Display::color = currColor;

    // Draw borders
    if (m_titleText) {
        drawBorders(m_x, m_y + (2 * fontH), m_w, m_h - (2 * fontH));
     }
    else {

        // Draw window borders
    uint16_t currColor = Display::color;
    Display::color = LB_BORDER_COLOR;
        drawBorders(m_x, m_y, m_w, Display::getHeight()-16);
    // Restore original color.
    Display::color = currColor;

    currColor = Display::color;
    Display::color = 2;
        // Draw text box borders
        drawBorders(m_x, m_y + Display::getHeight()-24, m_w, 24);
    Display::color = currColor;

    }

    // Draw title
    drawTitle();
}

// ListBoxDlg class

ListBoxDlg::ListBoxDlg(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t maxItems )
: DialogBase(WidgetBase::hasBorders){

    m_listbox = nullptr;

    init(titleText, x, y, w, h, maxItems);
}

ListBoxDlg::~ListBoxDlg(){

    delete m_listbox;
}

void ListBoxDlg::init(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t maxItems ) {

    // Set title
    if(titleText)
        setTitle(titleText);

    // Set the dialog rect
    setRect(x, y, w, h);

    // Create listbox widget.
    int16_t vx, vy, vw, vh;
    getViewRect(vx, vy, vw, vh);
    m_listbox = new(std::nothrow) ListBox(0);
    m_listbox->init(vx, vy, vw/fontW, vh/fontH + 1, maxItems);
}

uint16_t ListBoxDlg::addItem(const char* text) {
    return(m_listbox->addItem(text));
}

uint16_t ListBoxDlg::removeItem(uint8_t itemId) {
    return(m_listbox->removeItem(itemId));
}

void ListBoxDlg::update() {

    if( Core::buttons.pressed(BTN_A) )
        m_done = true;

    if(!m_done)
        m_listbox->update(); // To react scrolling
}

void ListBoxDlg::draw() {

    DialogBase::draw();
    m_listbox->draw();
}
