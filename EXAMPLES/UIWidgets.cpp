#include "Pokitto.h"
#include "UIWidget.h"
#include <new>

Pokitto::Core game;

/** MAIN */
int main () {
    game.begin();

    game.display.setFont(fntC64UIGfx);  // A special font set that contains UI gfx in lower case letters.
    game.display.palette[0] = game.display.RGBto565(0x0, 0x0, 0x0); // black (backgound)
    game.display.palette[1] = game.display.RGBto565(0x00, 0xff, 0x00); // green (borders, selection)
    game.display.palette[2] = game.display.RGBto565(0xff, 0x00, 0x00); // red
    game.display.palette[3] = game.display.RGBto565(0xff, 0xff, 0xff); // white (text)
    game.display.charSpacingAdjust = 0; // Needed for the non-proportional C64 font (normal value=1)
    game.display.fixedWidthFont = true; // Needed for the non-proportional C64 font (default value=false)

    // Create the test framework listbox
    Pokitto::ListBoxDlg* testFrameWorkDlg = new(std::nothrow) Pokitto::ListBoxDlg(
        "TESTS", 0, 10, game.display.getWidth()-1, game.display.getHeight()-10, 50 );

    // Add test cases
    testFrameWorkDlg->addItem("INFO DLG");
    testFrameWorkDlg->addItem("CANCEL DLG");
    testFrameWorkDlg->addItem("TXTEDIT DLG");

    // The dialog under testing.
    Pokitto::DialogBase* testDlg = nullptr;

    char* keyboardtext = new char[6];
    strcpy(keyboardtext, "ABCDEF");
    while (game.isRunning()) {
        if (game.update()) {

            // Check if the selection has been made.
            if (testFrameWorkDlg->isDone() && testDlg ==  nullptr) {

                switch(testFrameWorkDlg->getSelectedIndex()) {

                    case 0: // Info dialog
                        testDlg = new(std::nothrow) Pokitto::InfoDlg("HELLO!", "ACK" );
                        break;

                    case 1: // Cancel dialog
                        testDlg = new(std::nothrow) Pokitto::CancelDlg("SURE?");
                       break;

                    case 2: // Text edit dialog
                        testDlg = new(std::nothrow) Pokitto::TextInputDlg("POKITTO");
                        // Note: the text entered will be available in TextInputDlg::GetVkbText();
                       break;
                }
            }

            // Check if dialog is done.
            if (testDlg && testDlg->isDone()) {

                // remove the test dialog
                delete(testDlg);
                testDlg = nullptr;

                // Start the main dialog again.
                testFrameWorkDlg->setDone(false);
            }

            // Draw the test framework dialog.
            testFrameWorkDlg->update();
            testFrameWorkDlg->draw();

            // Draw test dialog
            if (testDlg)
                testDlg->draw();

//            keyboardtext[5] = '\0';
//            Pokitto::WidgetBase::keyboard(keyboardtext,6);
//            //game.keyboard(keyboardtext,6);

            //draw the keyboard
//			int8_t startChar = 32, numChars = 64;
//			int8_t i = 0;
//			for (; i <= numChars; i++) {
//                if(i%10 == 0)
//                    game.display.println( (char)(startChar + i));
//                else
//                    game.display.print( (char)(startChar + i));
//			}
        }
    }
    delete(testDlg);
    delete(testFrameWorkDlg);
    return 1;
}
