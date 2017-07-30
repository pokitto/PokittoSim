#include "Pokitto.h"
#include "UIWidget.h"
#include <new>

Pokitto::Core game;

/** MAIN */
int main() {  //
    game.begin();

    game.display.setFont(fntC64gfx);
    game.display.palette[0] = game.display.RGBto565(0x0, 0x0, 0x0); // black (backgound)
    game.display.palette[1] = game.display.RGBto565(0x00, 0xff, 0x00); // green
    game.display.palette[2] = game.display.RGBto565(0xff, 0x00, 0x00); // red
    game.display.palette[3] = game.display.RGBto565(0xff, 0xff, 0xff); // white
    game.display.charSpacingAdjust = 0; //needed for the non-proportional C64 font (normal value=1)
    game.display.fixedWidthFont = true;

    bool dialogDone = false;
    int16_t selIndex = 0;
    char selText[256];
    Pokitto::ListBoxDlg* pdlg = new(std::nothrow) Pokitto::ListBoxDlg(
        "TESTS", 0, 10, game.display.getWidth()-1, game.display.getHeight()-10, 50 );

    pdlg->addItem("INFO DLG");
    pdlg->addItem("CANCEL DLG");

    Pokitto::DialogBase* testDlg = nullptr;

    while (game.isRunning()) {
        if (game.update()) {

            // Check if the selection has been made.
            if (pdlg->isDone() && testDlg ==  nullptr) {

                switch(pdlg->getSelectedIndex()) {

                    case 0: // Info dialog
                        testDlg = new(std::nothrow) Pokitto::InfoDlg("HELLO!", "ACK" );
                        break;

                    case 1: // Cancel dialog
                        testDlg = new(std::nothrow) Pokitto::CancelDlg("DO IT?");
                       break;
                }
            }

            // Check if dialog is done.
            if (testDlg && testDlg->isDone()) {

                // remove the test dialog
                delete(testDlg);
                testDlg = nullptr;

                // Start the main dialog again.
                pdlg->setDone(false);
            }

            // Draw dialog
            if (pdlg) {
                pdlg->update();
                pdlg->draw();
            }

           // Draw test dialog
           if (testDlg)
                testDlg->draw();
        }
   }
    delete(pdlg);
    return 1;
}



