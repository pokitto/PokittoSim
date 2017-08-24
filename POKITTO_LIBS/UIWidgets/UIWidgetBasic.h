/**************************************************************************/
/*!
    @file     UIWidgetBasic.h
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

#ifndef UI_WIDGET_BASIC_H

#define POK_TRACE(str) printf("%s (%d): %s", __FILE__, __LINE__,str)

#define UI_WIDGET_BASIC_H

#include "Pokitto.h"

// Defines for widgets.
#define LB_BACKGROUND_COLOR 0
#define LB_BORDER_COLOR 1
#define LB_ITEM_COLOR 3
#define LB_SELECTED_ITEM_COLOR 1

namespace Pokitto {

const int16_t fontW = 8, fontH = 8;

/** WidgetBase class.
*/
class WidgetBase {

public:
    /** Flags.
     */
    enum Flags {
        none = 0x0,
        hasBorders = 0x1, /** The widget has borders */
    };

public:
    /** Constructor.
     * @param flags Flags
     */
    WidgetBase(uint32_t flags);

    /** Destructor.
     */
    virtual ~WidgetBase();

    /** Sets the window extent rect.
     * @param x Window x position
     * @param y Window y position
     * @param w Window width
     * @param h Window height
     */
    virtual void setRect(int16_t x, int16_t y, int16_t w, int16_t h) {m_x = x; m_y = y; m_w = w; m_h = h;}

    /** Gets the window extent rect.
     * @param x Return window extent x position
     * @param y Return window extent y position
     * @param w Return window extent width
     * @param h Return window extent height
     */
    virtual void getRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h) {x = m_x; y = m_y; w = m_w; h = m_h;}

    /** Gets the rect of the view area.
     * @param x Return view area x position
     * @param y Return view area y position
     * @param w Return view area width
     * @param h Return view area height
     */
    virtual void getViewRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h);

    /** Sets the title for the window.
     * @param ptitle The title string
     */
    void setTitle(char* titleText);

    /** Initiakize virtual keyboard.
     * @ptext The initial text string. It defines the width of the output text string.
     */
    void keyboardInit(char* ptext);

    /** Updates the virtual keyboard.
     */
    void keyboardUpdate();

    /** Draws the virtual keyboard.
     */
    void keyboardDraw();

    /** True, if the vkb has got end-command.
     * @return True, if the dialo     * @param ptitle The title string
g has been closed.
     */
    bool isVkbEnd() {return m_vkbEnd;}

    /** Gets the current vkb text.
     * @return The current vkb text.
     */
    char* GetVkbText() {return m_vkbText;}

    /** Draws the whole window.
     */
    virtual void draw();

    /** Draws the window borders.
     * @param x Border rect x position
     * @param y Border rect y position
     * @param w Border rect width
     * @param h Border rect height
     */
    virtual void drawBorders(int16_t x, int16_t y, int16_t w, int16_t h);

    virtual void drawTitle();

protected:
    int16_t m_x, m_y, m_w, m_h;
    uint16_t m_flags;
    char* m_titleText; // Owned

    /** Keyboard */

    char* m_vkbText;
    uint8_t m_vkbTextLenWithNull;
	//active character in the typing area
	int8_t m_vkbActiveChar;
	//selected char on the keyboard
	int8_t m_vkbActiveX;
	int8_t m_vkbActiveY;
	//position of the keyboard on the screen
	int8_t m_vkbCurrentX;
	int8_t m_vkbCurrentY;
	bool m_vkbEnd;

};

/** DialogBase class.
 */
class DialogBase : public WidgetBase {

public:
    /** Constructor.
     */
    DialogBase(uint32_t flags): WidgetBase(flags) {m_done = false;}

    /** Destructor.
    */
    virtual ~DialogBase() {}

    /** True, if the dialog has been closed.
     * @return True, if the dialog has been closed.
     */
    bool isDone() {return m_done;}

    /** Sets the dialog state as don or not done.
     * @param isDone Dialog state to set
     */
    void setDone(bool isDone) {m_done = isDone;}

protected:
    virtual void update() {}

protected:
    bool m_done;
};

}  // namespace

#endif // UI_WIDGET_BASIC_H
