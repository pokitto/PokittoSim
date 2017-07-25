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

class PokWindow {
public:
    PokWindow(){}
    init(int16_t x, int16_t y, int16_t w, int16_t h) {m_x = x; m_y = y; m_w = w; m_h = h;}
    draw();

public:
    int16_t m_x, m_y, m_w, m_h;
};
}
#endif // UI_WIDGET_H
