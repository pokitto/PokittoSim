#include "Pokitto.h"
#include <new>          // std::nothrow SIMULATOR!!!


Pokitto::Core game;
Pokitto::PokWindow window;

int main () {
    game.begin();
    // Next 4 lines are just to show the C64 font, you can comment them out by adding // in the start of the line
    game.display.setFont(fntC64gfx);
    game.display.palette[0] = game.display.RGBto565(0x0, 0x0, 0x0); //default background is palette[0]
    game.display.palette[1] = game.display.RGBto565(0x00, 0xff, 0x00); //default foreground is palette[1]
    game.display.palette[2] = game.display.RGBto565(0xff, 0x00, 0x00); //default foreground is palette[1]
    game.display.palette[3] = game.display.RGBto565(0x00, 0xff, 0x00); //default foreground is palette[1]
    game.display.charSpacingAdjust = 0; //needed for the non-proportional C64 font (normal value=1)

    Pokitto::PokWindow* win1 = new(std::nothrow) Pokitto::PokWindow();
    win1->setTitle("POKITTO");
    Pokitto::PokWindowBase* win2 = new(std::nothrow) Pokitto::PokWindowBase();
    //win->setRect(0, 0, game.display.getWidth(), game.display.getHeight());
    //win->setRect(0, 0, 64, 64);

	bool mustDraw = true;
	int16_t sx=128, sy=128;
    while (game.isRunning()) {
        if (game.update()) {
            //game.display.print("Hello World!");
            //game.display.print("**** COMMODORE 64 LIVES ****\n\n");
            //game.display.println(" 32K RAM POKITTO SYSTEM \n");
            //game.display.println("READY.");

            // Draw
            if (mustDraw) {

                game.display.color = 1;
                win1->setRect(0, 0, sx, sy);
                win1->draw();
                //win2->setRect(40, 40, sx, sy);
                //win2->draw();

                game.display.color = 2;
                game.display.drawRect(0, 0, sx, sy);

                //game.display.println(0,130,"aabacadaeafagahaiajakalamanaoapaqarasatauavaw");
                //game.display.println("abcdefghijklmnopqrstuvw");
                //game.display.println("ABCDEFGHIJKLMNOPQRSTUVW");
                //game.display.println("a b c d e f g h i j k l m n o p q r s t u v w");

            }

            // Read key
            if(game.buttons.repeat(BTN_RIGHT,0)) {
                mustDraw = true;
                sx+=2;
                //if(sx > 0  )
                //    sx = 0;
            }
            if(game.buttons.repeat(BTN_LEFT,0)) {
                mustDraw = true;
                sx-=2;
                //if (sx < game.display.width-imageW)
                //    sx = game.display.width-imageW;
            }
            if(game.buttons.repeat(BTN_UP,0)) {
                mustDraw = true;
                sy-=2;
                //if (sy < game.display.height-imageH)
                //    sy = game.display.height-imageH;
            }
            if(game.buttons.repeat(BTN_DOWN,0)) {
                mustDraw = true;
                sy+=2;
                //if(sy > 0  )
                //    sy = 0;
            }
        }
    }

    delete(win2);
    delete(win1);

    return 1;
}

#if 0

#define BLINKYPERIOD 500

int main () {
game.begin();
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
#endif
