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

#include "UIWidgetBasic.h"
#include "ListBox.h"


namespace Pokitto {

/** InfoDlg class.
 *  Note ment to be inherited.
 */
class InfoDlg : public WidgetBase {

public:
    /** Constructor.
     * @param ptext Dialog text
     * @param pdone True, if the user has done the selection.
     */
    InfoDlg(char* ptext, bool* pdone);

    /** Constructor.
     * @param ptext Dialog text
     * @param okText Dialog text
     * @param pdone True, if the user has done the selection.
     */
    InfoDlg(char* ptext, char* okText, bool* pdone);

    /** Destructor.
    */// Owned
    ~InfoDlg();

public:  // From base class
    void draw();

private:
    void init(char* ptext, char* oktext);
    void update();

private:
    char* m_ptext; // Owned
    char* m_okText; // Owned
    bool* m_pdone;
};

/** CancelDlg class.
 *  Note ment to be inherited.
 */
class CancelDlg : public WidgetBase {

public:
    /** Constructor.
     * @param ptext Dialog text
     * @param pisOkSelected True, if the user has selected ok.
     * @param pdone True, if the user has done the selection.
     */
    CancelDlg(char* ptext, bool* pisOkSelected, bool* pdone);

    /** Constructor.
     * @param ptext Dialog text
     * @param okText Dialog "ok" text
     * @param cancelText Dialog "cancel" text
     * @param pisOkSelected True, if the user has selected ok.
     * @param pdone True, if the user has done the selection.
     */
    CancelDlg(char* ptext, char* okText, char* cancelText, bool* pisOkSelected, bool* pdone);

    /** Destructor.
    */
    ~CancelDlg();

public:  // From base class
    void draw();

private:
    void init(char* ptext, char* okText, char* cancelText);
    void update();

private:
    bool m_isOkSelected;
    char* m_ptext; // Owned
    char* m_okText; // Owned
    char* m_cancelText; // Owned
    bool* m_pisOkSelected;
    bool* m_pdone;
};

class ListBoxDlg : public Window {

 public:
   ListBoxDlg(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h);
    ~ListBoxDlg();
    void update();
    bool isdone() {return m_done;}
    int16_t getIndex() {return m_listbox->selectedItem;}

private:
    void init(char* titleText, int16_t x, int16_t y, int16_t w, int16_t h);

public: // Inherited
    void draw();

public:
    char* m_titleText;
    bool m_done;
    ListBox* m_listbox;
};


}  // namespace

#endif // UI_WIDGET_H
