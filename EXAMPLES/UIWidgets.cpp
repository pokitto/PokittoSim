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

    // The dialog under testing.
    Pokitto::DialogBase* testDlg = nullptr;

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
        }
    }
    delete(testDlg);
    delete(testFrameWorkDlg);
    return 1;
}
