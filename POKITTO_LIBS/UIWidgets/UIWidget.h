/**************************************************************************/
/*!
    @file     UIWidget.h
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

#ifndef UI_WIDGET_H

#define POK_TRACE(str) printf("%s (%d): %s", __FILE__, __LINE__,str)

#define UI_WIDGET_H

#include "UIWidgetBasic.h"
#include "ListBox.h"


namespace Pokitto {

/** InfoDlg class.
 *  Note ment to be inherited.
 */
class InfoDlg : public DialogBase {

public:
    /** Constructor.
     * @param ptext Dialog text
     * @param pdone True, if the user has done the selection.
     */
    InfoDlg(char* ptext);

    /** Constructor.
     * @param ptext Dialog text
     * @param okText Dialog text
     * @param pdone True, if the user has done the selection.
     */
    InfoDlg(char* ptext, char* okText);

    /** Destructor.
    */// Owned
    ~InfoDlg();

public:  // From base class
    void draw();
    void update();

private:
    void init(char* ptext, char* oktext);

private:
    char* m_ptext; // Owned
    char* m_okText; // Owned
};

/** CancelDlg class.
 *  Note ment to be inherited.
 */
class CancelDlg : public DialogBase {

public:
    /** Constructor.
     * @param ptext Dialog text
     * @param pisOkSelected True, if the user has selected ok.
     * @param pdone True, if the user has done the selection.
     */
    CancelDlg(char* ptext);

    /** Constructor.
     * @param ptext Dialog text
     * @param okText Dialog "ok" text
     * @param cancelText Dialog "cancel" text
     * @param pisOkSelected True, if the user has selected ok.
     * @param pdone True, if the user has done the selection.
     */
    CancelDlg(char* ptext, char* okText, char* cancelText);

    /** Destructor.
    */
    ~CancelDlg();

    /** Check the selection state.
     * @return true if the user has done the selection.
     */
    bool isOk() {return m_isOkSelected;}

public:  // From base class
    void draw();
    void update();

private:
    void init(char* ptext, char* okText, char* cancelText);

private:
    bool m_isOkSelected;
    char* m_ptext; // Owned
    char* m_okText; // Owned
    char* m_cancelText; // Owned
};

class ListBoxDlg : public DialogBase {

 public:
     /** Constructor.
     * @param titleText Dialog text
     * @param x Dialog x position
     * @param y Dialog y position
     * @param w Dialog width
     * @param h Dialog height
     * @param maxItems Max number if list box items
     */
    ListBoxDlg(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t maxItems);

    /** Destructor.
     */
    ~ListBoxDlg();

    /** Adds an item to the list.
     * @param text Item text.
     */
    uint16_t addItem(const char* text);

    /** Remoes an item from the list.
     * @param itemId The index of the item to be removed.
     */
    uint16_t removeItem(uint8_t itemId);

    /** Gets the currently selected item index.
     * @return ptext The currently selected item index.
     */
    int16_t getSelectedIndex() {return m_listbox->selectedItem;}

    /** Gets the currently selected item text.
     * @return ptext The currently selected item text.
     */
    char* getSelectedText() {return m_listbox->items[m_listbox->selectedItem].text;}

private:
    void init(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t maxItems);

public:  // From base class
    void draw();
    void update();

public:
    ListBox* m_listbox;
};


}  // namespace

#endif // UI_WIDGET_H
