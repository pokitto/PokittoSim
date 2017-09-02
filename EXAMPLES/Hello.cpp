#include "Pokitto.h"

Pokitto::Core game;

#define BLINKYPERIOD 500

int main () {
game.begin();
game.sound.playTone(1,440,1,0);
// Next 4 lines are just to show the C64 font, you can comment them out by adding // in the start of the line
game.display.setFont(fontC64);
game.display.palette[0] = game.display.RGBto565(0x42, 0x42, 0xe7); //default background is palette[0]
game.display.palette[1] = game.display.RGBto565(0xa5, 0xa5, 0xff); //default foreground is palette[1]
game.display.charSpacingAdjust = 0; //needed for the non-proportional C64 font (normal value=1)
int blinkybox = 0;
long blinkytime = game.getTime();

while (game.isRunning()) {
    if (game.update()) {
        // game.display.print("Hello World!");
        game.display.print("**** COMMODORE 64 LIVES ****\n\n");
        game.display.println(" 32K RAM POKITTO SYSTEM \n");
        game.display.println("READY.");
        if (game.getTime()>blinkytime+BLINKYPERIOD) {
           blinkybox = 1 - blinkybox; //toggle blinky
           blinkytime = game.getTime(); // store new time
        }
        if (blinkybox) {
            game.display.bgcolor = 1; // reverse whitespace color
            game.display.print(" ");  // print whitespace
            game.display.bgcolor = 0; // put color the right way again
        }
    }
}

return 1;
}
