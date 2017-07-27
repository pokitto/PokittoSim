//
// ListBox : A ListBox component for the Pokitto (http://www.pokitto.com)
//
// Copyright (C) 2017 Jerome Perrot (Initgraph)
//
// Version : 0.1
//
// Licence :
//
//   This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
//   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc.,
//   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// For any remarks or questions you can contact me on Twitter (@InitgraphDotCom) or by email (contact@initgraph.com).
// You can also visit my website : http://www.initgraph.com
//
// Enjoy !
//

#ifndef LISTBOX_H
#define LISTBOX_H

#include "pokitto.h"

namespace Pokitto {

#define LB_BACKGROUND_COLOR 0
#define LB_BORDER_COLOR 1
#define LB_ITEM_COLOR 3
#define LB_SELECTED_ITEM_COLOR 1
#define LB_BORDER_MARGIN_UP 2
#define LB_BORDER_MARGIN_DOWN 2
#define LB_ITEM_MARGIN_LEFT 1
#define LB_ITEM_CHAR_WIDTH 8
#define LB_ITEM_CHAR_HEIGHT 8
#define LB_ITEM_LENGTH 32       // Max characters in a line (31 chars + '\0')

#define LB_HIDE_BORDER 1

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// ListBox Item class
// ------------------------------------------------------------------------------------------------------------------------------------------------------
class ListBoxItem {

  public:

    char text[LB_ITEM_LENGTH];

    ListBoxItem();
    ~ListBoxItem();

  private:
};


// ------------------------------------------------------------------------------------------------------------------------------------------------------
// ListBox class
// ------------------------------------------------------------------------------------------------------------------------------------------------------
class ListBox : public WidgetBase {

  public:

    uint8_t x;
    uint8_t y;
    ListBoxItem *items;
    uint16_t itemsCount;
    uint16_t maxItems;
    uint16_t selectedItem;
    uint8_t backgroundColor;
    uint8_t borderColor;
    uint8_t itemColor;
    uint8_t selectedItemColor;

    ListBox(uint32_t flags);
    ~ListBox();
    uint16_t addItem(const char* text);
    uint16_t removeItem(uint8_t itemId);
    void update();
    //uint8_t init(uint8_t x, uint8_t y , uint8_t width, uint8_t height, uint16_t maxItems, uint8_t options);
    uint8_t init(uint8_t x, uint8_t y , uint8_t widthInChars, uint8_t heightInChars, uint16_t maxItems, uint8_t options);
    void subString(char *dstString, const char *srcString, uint8_t firstChar, uint8_t lastChar);

    // Inherited
    virtual void setRect(int16_t x, int16_t y, int16_t w, int16_t h) {m_x = x; m_y = y; m_w = w; m_h = h;}
    void draw();

  private:

    uint8_t width;
    uint8_t height;
    uint8_t viewX;
    uint8_t viewY;
    uint8_t viewWidth;
    uint8_t viewHeight;
    uint8_t firstCharToShow;
    uint16_t firstItemToShow;
    bool hideBorder;

    void show();
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
};

}  // namespace
#endif
