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

#ifndef UI_WIDGET_H

#define POK_TRACE(str) printf("%s (%d): %s", __FILE__, __LINE__,str)

#define UI_WIDGET_H

namespace Pokitto {

/** PokWindowBase class.
*/
class PokWindowBase {
public:
    PokWindowBase(){setRect(0,0,0,0); flags = 0;}

    /** Sets the window extent rect.
     * @param x Window x position
     * @param y Window y position
     * @param w Window width
     * @param h Window height
     */
    void setRect(int16_t x, int16_t y, int16_t w, int16_t h) {m_x = x; m_y = y; m_w = w; m_h = h;}

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
    uint16_t flags;
};

/** PokWindow class.
*/
class PokWindow : public PokWindowBase {
public:
    PokWindow(){m_ptitle=NULL;}
    ~PokWindow(){free(m_ptitle);}
    void setTitle(char* ptitle) {
        m_ptitle = (char*)malloc(strlen(ptitle)+1);
        strcpy(m_ptitle,ptitle);
    }
    void draw();
    void drawTitle();

protected:
    char* m_ptitle;
};

/** PokTextListbox class.
*/
class PokTextListbox : public PokWindowBase {
public:
    PokTextListbox(){m_ptextPointerArray=NULL;}
    ~PokTextListbox(){}

    void setTextArray( char** ptextPointerArray, int16_t count );

    void setFocusedItem(int16_t index);
    int16_t getFocusedItem();
    void setScrollPos(int16_t index);
    int16_t getScrollPos();

    void drawList();

    // From the base class.
    void draw();

protected:
    char** m_ptextPointerArray;
    int16_t m_count;
};

}  // namespace

#endif // UI_WIDGET_H
