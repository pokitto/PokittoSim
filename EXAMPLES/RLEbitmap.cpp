#include "Pokitto.h"
Pokitto::Core game;

/** Select the test code */
#define TEST_MAIN 0

/** Test: Hello World */
#if TEST_MAIN == 0

int main () {
game.begin();

while (game.isRunning()) {

    if (game.update()) {
        game.display.print("Hello World!");
    }

}

return 1;
}

/** Test: Read 16 color BMP format image. */
#elif TEST_MAIN == 1

/*
	In this tutorial we are using fast screen mode.
	It means screen resolution is 110x88

*/

#if POK_SCREENMODE != MODE_FAST_16COLOR
#error Wrong color mode for the test code. Should be MODE_FAST_16COLOR.
#endif

int main(){
	game.begin();
	game.display.width = 110;
	game.display.height = 88;
	game.setFrameRate(60);
	game.display.persistence = 1 ;

	bool firstTime = true;
	bool ready = false;
    uint8_t *bitmap = 0;
	while (game.isRunning()) {
    	if (game.update()) {

            if (firstTime) {
                firstTime = false;
                uint16_t *palette = 0;
                int ret = openImageFileFromSD("..\\..\\..\\EXAMPLES\\test.bmp", &palette, &bitmap);

                game.display.load565Palette(palette);
                free( palette );
                ready = true;
            }

            if( ready == true )
                game.display.drawBitmap(0,0,bitmap);
    	}
	}

	free( bitmap );

	return(1);
}

/** Test: Read 16 color BMP-RLE format image. */
#elif TEST_MAIN == 2

/*
	In this tutorial we are using fast screen mode.
	It means screen resolution is 110x88

*/

#if POK_SCREENMODE != MODE_FAST_16COLOR
#error Wrong color mode for the test code. Should be MODE_FAST_16COLOR.
#endif

int main(){
	game.begin();
	game.display.width = 110;
	game.display.height = 88;
	game.setFrameRate(60);
	game.display.persistence = 1 ;

	bool firstTime = true;
	bool ready = false;
    uint8_t *bitmap = 0;
	while (game.isRunning()) {
    	if (game.update()) {

            if (firstTime) {
                firstTime = false;
                uint16_t *palette = 0;
                int ret = openImageFileFromSD("..\\..\\..\\EXAMPLES\\rletest_pochand.bmp", &palette, &bitmap);

                game.display.load565Palette(palette);
                free( palette );
                ready = true;
            }

            if( ready == true )
                game.display.drawRleBitmap(0,0,bitmap);
    	}
	}

	free( bitmap );

	return(1);
}

/** Test: Open 24-bit color BMP format image from SD card and draw directly to the screen */
#elif TEST_MAIN == 3  // Test: Open 16 color BMP format image from SD.

#if POK_SCREENMODE != MODE_HI_4COLOR
#error Wrong color mode for the test code. Should be MODE_HI_4COLOR.
#endif

int main(){
	game.begin();
	game.display.persistence=1;
	game.display.width = 220; // full size
	game.display.height = 174;
	game.setFrameRate(60);

	bool mustDraw = true;
	int sx = 0, sy=0;
	int imageW = 300, imageH = 400;
    while (game.isRunning()) {
        if (game.update(true)) {

            if(mustDraw) {
                int ret = directDrawImageFileFromSD(0,0,0,0,sx,sy,"..\\..\\..\\EXAMPLES\\test_24bit_300x400.bmp");
                mustDraw = false;
            }

            if(game.buttons.repeat(BTN_LEFT,0)) {
                mustDraw = true;
                sx+=2;
                if(sx > 0  )
                    sx = 0;
            }
            if(game.buttons.repeat(BTN_RIGHT,0)) {
                mustDraw = true;
                sx-=2;
                if (sx < game.display.width-imageW)
                    sx = game.display.width-imageW;
            }
            if(game.buttons.repeat(BTN_DOWN,0)) {
                mustDraw = true;
                sy-=2;
                if (sy < game.display.height-imageH)
                    sy = game.display.height-imageH;
            }
            if(game.buttons.repeat(BTN_UP,0)) {
                mustDraw = true;
                sy+=2;
                if(sy > 0  )
                    sy = 0;
            }
        }
    }
    return 1;
}
#endif

