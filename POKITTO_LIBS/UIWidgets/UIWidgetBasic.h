/**************************************************************************/
/*!
    @file     xxx.h
    @author   Hannu Viitala

    @section LICENSE

    Pokitto development stage library
    Software License Agreement

    Copyright (c) 2015, Jonne Valola ("Author")
    All rights reserved.

    This library is intended solely for the purpose of Pokitto development.

    Redistribution and use in source and binary forms, with or without
    modification requires written permission from Author.
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
    WidgetBase(uint32_t flags){setRect(0,0,0,0); m_flags = flags;}

    /** Destructor.
     */
    ~WidgetBase(){}

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
    virtual void getRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h) {

        if (m_flags & Flags::hasBorders) {
            x = m_x + fontW; y = m_y + fontH; w = m_w - (2 * fontW); h = m_h - (2 * fontH);
        }
        else {
            x = m_x; y = m_y; w = m_w; h = m_h;
        }
    }

    /** Gets the rect of the view area.
     * @param x Return view area x position
     * @param y Return view area y position
     * @param w Return view area width
     * @param h Return view area height
     */
    virtual void getViewRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h) {

        if (m_flags & Flags::hasBorders) {
            x = m_x + fontW; y = m_y + fontH; w = m_w - (2 * fontW); h = m_h - (2 * fontH);
        }
        else {
            x = m_x; y = m_y; w = m_w; h = m_h;
        }
    }

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

protected:
    int16_t m_x, m_y, m_w, m_h;
    uint16_t m_flags;
};

/** Window class.
*/
class Window : public WidgetBase {

public:  // New

    /** Constructor.
    */
    Window() : WidgetBase(hasBorders) {m_ptitle=NULL;}

    /** Destructor.
    */
    ~Window() {free(m_ptitle);}

    /** Sets the title for the window.
     * @param ptitle The title string
     */
    void setTitle(char* ptitle) {
        m_ptitle = (char*)malloc(strlen(ptitle)+1);
        strcpy(m_ptitle,ptitle);
    }

protected:

    virtual void drawTitle();

public: // From base class

    void getViewRect(int16_t& x, int16_t& y, int16_t& w, int16_t& h) {

        WidgetBase::getViewRect(x, y, w, h);

        if( m_ptitle ) {
            x = x; y = y + (2 * fontH); w = w; h = h - (2 * fontH);
        }
    }

    void draw();

protected:
    char* m_ptitle; // Owned
};

}  // namespace

#endif // UI_WIDGET_BASIC_H
