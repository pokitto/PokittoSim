/**************************************************************************/
/*!
    @file     PokittoCore.cpp
    @author   Jonne Valola

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Jonne Valola
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

#include "PokittoCore.h"
#include "Pokitto_settings.h"
#include "PokittoConsole.h"
#include "PokittoFonts.h"
#include "PokittoTimer.h"
#include "PokittoLogos.h"
#include <stdlib.h>
#ifndef DISABLEAVRMIN
#define max(a,b) ((a)>(b)?(a):(b))
#endif // DISABLEAVRMIN

char selectedfile[25];

// returns a random integar between 0 and maxVal
int random(int maxVal)
{
  return random( 0, maxVal);
}

// returns a random integar between minVal and maxVal
int random(int minVal, int maxVal)
{
  // int rand(void); included by default from newlib
  return rand() % (maxVal-minVal+1) + minVal;
}

using namespace Pokitto;

bool Core::run_state; // this definition needed

/** Components */
Backlight Core::backlight;
Buttons Core::buttons;
Battery Core::battery;
#if POK_ENABLE_SOUND > 0
Sound Core::sound;
#endif
Display Core::display;

//GB Related
uint8_t Core::startMenuTimer;
uint8_t Core::timePerFrame;
uint32_t Core::nextFrameMillis;
uint32_t Core::frameCount;
const char* Core::popupText;
uint8_t Core::popupTimeLeft;
uint16_t Core::frameDurationMicros;
uint32_t Core::frameStartMicros, Core::frameEndMicros;


Core::Core() {

}

void Core::begin() {

    init(); // original functions
    timePerFrame = POK_FRAMEDURATION;
	//nextFrameMillis = 0;
	//frameCount = 0;
	frameEndMicros = 1;
	startMenuTimer = 255;
	//read default settings from flash memory (set using settings.hex)
	readSettings();
	//init everything
	backlight.begin();
	backlight.set(BACKLIGHT_MAX);
	buttons.begin();
	buttons.update();
	battery.begin();
	display.begin();
	#if POK_DISPLAYLOGO
        showLogo();
	#endif // POK_DISPLAYLOGO
	#if POK_ENABLE_SOUND > 0
        sound.begin();

	//mute when B is held during start up or if battery is low
	battery.update();
	if(buttons.pressed(BTN_B) || (battery.level == 0)){
		sound.setVolume(0);
	}
	else{ //play the startup sound on each channel for it to be louder
		#if POK_GBSOUND > 0
		#if(NUM_CHANNELS > 0)
			sound.playPattern(startupSound, 0);
		#endif
		#if(NUM_CHANNELS > 1)
			sound.playPattern(startupSound, 1);
		#endif
		#if(NUM_CHANNELS > 2)
			sound.playPattern(startupSound, 2);
		#endif
		#if(NUM_CHANNELS > 3)
			sound.playPattern(startupSound, 3);
		#endif
		#endif // POK_GBSOUND
	}
	#endif // POK ENABLE_SOUND
}

void Core::init() {
    run_state = true;
    display.enableDirectPrinting(false);
    display.setFont(DEFAULT_FONT);
    initClock();
    initGPIO();
    initButtons();
    initRandom();
    //initAudio();
    //initDisplay();
}

void Core::init(uint8_t switches) {
    run_state = true;
    display.enableDirectPrinting(false);
    display.setFont(DEFAULT_FONT);
    initClock();
    initGPIO();
    initButtons();
    initRandom();
    //initAudio();
    //initDisplay();
}

void Core::initButtons() {
    #ifndef POK_SIM
    Pokitto::initButtons();
    #endif
}

bool Core::isRunning() {
    #ifdef POK_SIM
    run_state = simulator.isRunning();
    #endif // POK_SIM
    return run_state;
}

void Core::initDisplay() {
    #if POK_DISPLAYLOGO > 0
        showLogo();
    #endif
    #if POK_USE_CONSOLE > 0
        console.AddMessage(MSOURCE_LCD,MSG_INIT_OK);
    #endif
}

void Core::showLogo() {
    uint32_t now;
    uint8_t state=0; //jump directly to logo, bypass teeth
    uint16_t i=0;
    uint16_t sc;
    while (state < 255/6) {
    now=getTime();
    if (now>refreshtime) {
            refreshtime=now+30;
            switch (state) {
            case 0:
                /** POKITTO CLEAN **/
                display.directbgcolor = COLOR_BLACK;
                display.fillLCD(display.directbgcolor);
                sc = COLOR_BLACK;
                state++;
                break;
            case 1:
                /** POKITTO FADE IN **/
                display.directcolor = display.interpolateColor(sc, COLOR_GREEN, i);
                display.directBitmap(POK_LCD_W/2 - (*Pokitto_logo/2),POK_LCD_H/2-(*(Pokitto_logo+1)/2),Pokitto_logo,1,1);
                i += 28;
                if (i>=0xFF) { state++; i=0;}
                break;
            case 2:
                /** POKITTO WAIT **/
                display.directcolor = COLOR_GREEN;
                display.directBitmap(POK_LCD_W/2 - (*Pokitto_logo/2),POK_LCD_H/2-(*(Pokitto_logo+1)/2),Pokitto_logo,1,1);
                i+= 0x3F;
                if (i>0x3FF) state = 255;
                break;
            }
            if(buttons.aBtn()) state=255;
    }
    }
}

void Core::readSettings() {
    // ToDo
        /*display.contrast = SCR_CONTRAST;
		backlight.backlightMin = BACKLIGHT_MIN;
		backlight.backlightMax = BACKLIGHT_MAX;
		backlight.ambientLightMin = AMBIENTLIGHT_MIN;
		backlight.ambientLightMax = AMBIENTLIGHT_MAX;
*/
		sound.volumeMax = VOLUME_GLOBAL_MAX;
		sound.globalVolume = 1; //was VOLUME_GLOBAL_MAX;

		startMenuTimer = START_MENU_TIMER;
/*
		battery.thresolds[0] = BAT_LVL_CRITIC;
		battery.thresolds[1] = BAT_LVL_LOW;
		battery.thresolds[2] = BAT_LVL_MED;
		battery.thresolds[3] = BAT_LVL_FULL;*/
}

void Core::titleScreen(const char* name){
	titleScreen(name, 0);
}

void Core::titleScreen(const uint8_t* logo){
	titleScreen(F(""), logo);
}

void Core::titleScreen(){
	titleScreen(F(""));
}

void Core::titleScreen(const char*  name, const uint8_t *logo){
	if(startMenuTimer){
		display.fontSize = 1;
		display.textWrap = false;
		display.persistence = false;
		battery.show = false;
		display.setColor(BLACK);
		while(1){
			if(update()){
				uint8_t logoOffset = name[0]?display.fontHeight:0; //add an offset the logo when there is a name to display
				//draw graphics
				display.setColorDepth(1);
				display.setColor(3);
				//display.drawBitmap(0,0, gamebuinoLogo);
				display.setColor(1);
				if(logo){
					display.drawBitmap(0, 12+logoOffset, logo);
				}
				display.cursorX = 0;
				display.cursorY = 12;
				display.print(name);

				//A button
				display.cursorX = LCDWIDTH - display.fontWidth*3 -1;
				display.cursorY = LCDHEIGHT - display.fontHeight*3 - 3;
				if((frameCount/16)%2)
				  display.println(F("\25 \20"));
				else
				  display.println(F("\25\20 "));
				//B button
				display.cursorX = LCDWIDTH - display.fontWidth*3 - 1;
				display.cursorY++;
				if(sound.globalVolume)
					display.println(F("\26\23\24"));
				else
					display.println(F("\26\23x"));
				//C button
				display.cursorX = LCDWIDTH - display.fontWidth*3 - 1;
				display.cursorY++;
				display.println(F("\27SD"));

				//toggle volume when B is pressed
				if(buttons.pressed(BTN_B)){
					sound.setVolume(sound.getVolume() + 1);
					sound.playTick();
				}
				//leave the menu
				if(buttons.pressed(BTN_A) || ((frameCount>=startMenuTimer)&&(startMenuTimer != 255))){
					startMenuTimer = 255; //don't automatically skip the title screen next time it's displayed
					sound.stopPattern(0);
					sound.playOK();
					break;
				}
				//flash the loader
				//if(buttons.pressed(BTN_C))
					// ToDo changeGame();
			}
		}
		battery.show = true;
	}
}

bool Core::update(bool useDirectMode) {
#if POK_STREAMING_MUSIC
        sound.updateStream();
    #endif

	if ((((nextFrameMillis - getTime())) > timePerFrame) && frameEndMicros) { //if time to render a new frame is reached and the frame end has ran once
		nextFrameMillis = getTime() + timePerFrame;
		frameCount++;

		frameEndMicros = 0;
		backlight.update();
		buttons.update();
		battery.update();

		return true;

	} else {
		if (!frameEndMicros) { //runs once at the end of the frame
			#if POK_ENABLE_SOUND > 0
			sound.updateTrack();
			sound.updatePattern();
			sound.updateNote();
			#endif
			updatePopup();
			displayBattery();

			if(!useDirectMode)
				display.update(); //send the buffer to the screen

            frameEndMicros = 1; //jonne

		}
		return false;
	}
}

void Core::displayBattery(){
#if (ENABLE_BATTERY > 0)
	//display.setColor(BLACK, WHITE);
	uint8_t ox,oy;
	ox=display.cursorX;
	oy=display.cursorY;
	display.cursorX = LCDWIDTH-display.fontWidth+1;
	display.cursorY = 0;
	switch(battery.level){
	case 0://battery critic, power down
		sound.stopPattern();
		backlight.set(0);
		display.clear();
		display.fontSize = 1;
		display.print(F("LOW BATTERY\n"));
		display.print(battery.voltage);
		display.print(F("mV\n\nPLEASE\nTURN OFF"));
		display.update();
		break;
	case 1: //empty battery
		if((frameCount % 16) < 8) display.print('\7'); //blinking battery
		else display.print('x');
		break;
	case 2://low battery
	case 3://full battery
	case 4://full battery
		if(battery.show){
			display.print(char(5+battery.level));
		}
		break;
	default:
		if(battery.show){
			display.print('/');
		}
		break;
	}
display.cursorX = ox;
display.cursorY = oy;
#endif
}

char* Core::filemenu(char *ext) {
    #if POK_ENABLE_SD > 0
    display.persistence = false;
    uint16_t oldpal0=display.palette[0];
    uint16_t oldpal1=display.palette[1];
    uint16_t oldpal2=display.palette[2];
    display.palette[2]=COLOR_GREEN;
    display.palette[1]=COLOR_WHITE;
    display.palette[0]=COLOR_BLACK;
    uint8_t oldbg=display.bgcolor;
    uint8_t oldfg=display.color;
    display.color=1;
    display.bgcolor=0;

    int8_t activeItem = 0;
	int16_t currentY = 100;
	int16_t targetY = 0, rowh = display.fontHeight + 2;
	boolean exit = false;

	char* txt;


	while (isRunning()) {
		if (update()) {
            getFirstFile(ext);
			if (buttons.pressed(BTN_A) || buttons.pressed(BTN_B) || buttons.pressed(BTN_C)) {
				exit = true; //time to exit menu !
				targetY = - display.fontHeight * 10 - 2; //send the menu out of the screen
				if (buttons.pressed(BTN_A)) {
					//answer = activeItem;
					sound.playOK();
				} else {
					sound.playCancel();
				}
			}
			if (exit == false) {
				if (buttons.repeat(BTN_DOWN,4)) {
					activeItem++;
					sound.playTick();
				}
				if (buttons.repeat(BTN_UP,4)) {
					activeItem--;
					sound.playTick();
				}
				//don't go out of the menu
				//if (activeItem == length) activeItem = 0;
				//if (activeItem < 0) activeItem = length - 1;
                if (currentY>targetY) currentY-=16;
                if (currentY<targetY) currentY=targetY;
				//targetY = -rowh * activeItem + (rowh+4); //center the menu on the active item
			} else { //exit :
			    if (currentY>targetY) currentY-=16;
                if (currentY<targetY) currentY=targetY;
				if ((currentY - targetY) <= 1)
				{
				    display.bgcolor=oldbg;
				    display.color=oldfg;
				    display.palette[0] = oldpal0;
				    display.palette[1] = oldpal1;
				    display.palette[2] = oldpal2;
				    return selectedfile;
				}

			}
			//draw a fancy menu
			//currentY = 0;//(currentY + targetY) / 2 + 5;
			display.cursorX = 0;
			display.cursorY = currentY;
			display.textWrap = false;
            //getFirstFile(ext);
			for (int i = 0; i<20; i++) {
				display.invisiblecolor=255;
				display.cursorY = currentY + rowh * i;
				if (i==3) display.color=1;
				if (i == activeItem){
					display.cursorX = 3;

                    //display.fillRoundRect(0, currentY + display.fontHeight * activeItem - 2, LCDWIDTH, (display.fontHeight+3), 3);
                    display.color=2;
                    display.fillRect(0, currentY + rowh * activeItem - 2, LCDWIDTH, (rowh));
                    display.setColor(0,2);
				} else display.setColor(1,0);
				//display.println((char*)*(const unsigned int*)(items+i));
				//display.println((int)i);
                txt = getNextFile(ext);
                if (txt) {
                        display.println(txt);
                        if (i == activeItem) {
                            strcpy(selectedfile,txt);
                        }
                } else i--;
                display.setColor(1,0);
			} // draw menu loop
		} // update
	}
	#else
	return 0; //SD is not enabled
	#endif // POK_ENABLE_SD

}

char* Core::filemenu() {
    return filemenu("");
}

int8_t Core::menu(const char* const* items, uint8_t length) {
#if (ENABLE_GUI > 0)
	display.persistence = false;
	int8_t activeItem = 0;
	int16_t currentY = display.height;
	int16_t targetY = 0, rowh = display.fontHeight + 2;
	boolean exit = false;
	int8_t answer = -1;
	while (isRunning()) {
		if (update()) {
			if (buttons.pressed(BTN_A) || buttons.pressed(BTN_B) || buttons.pressed(BTN_C)) {
				exit = true; //time to exit menu !
				targetY = - display.fontHeight * length - 2; //send the menu out of the screen
				if (buttons.pressed(BTN_A)) {
					answer = activeItem;
					sound.playOK();
				} else {
					sound.playCancel();
				}
			}
			if (exit == false) {
				if (buttons.repeat(BTN_DOWN,4)) {
					activeItem++;
					sound.playTick();
				}
				if (buttons.repeat(BTN_UP,4)) {
					activeItem--;
					sound.playTick();
				}
				//don't go out of the menu
				if (activeItem == length) activeItem = 0;
				if (activeItem < 0) activeItem = length - 1;

				targetY = -rowh * activeItem + (rowh+4); //center the menu on the active item
			} else { //exit :
				if ((currentY - targetY) <= 1)
				return (answer);
			}
			//draw a fancy menu
			currentY = (currentY + targetY) / 2;
			display.cursorX = 0;
			display.cursorY = currentY;
			display.textWrap = false;
			uint16_t fc,bc;
			fc = display.color;
            bc = display.bgcolor;
			for (byte i = 0; i < length; i++) {
				display.cursorY = currentY + rowh * i;
				if (i == activeItem){
					display.cursorX = 3;

                    //display.fillRoundRect(0, currentY + display.fontHeight * activeItem - 2, LCDWIDTH, (display.fontHeight+3), 3);
                    display.fillRect(0, currentY + rowh * activeItem - 2, LCDWIDTH, (rowh));
                    display.setColor(bc,fc);
				} else display.setColor(fc,bc);

				display.println((char*)*(const unsigned int*)(items+i));
				display.setColor(fc,bc);
			}

		}
	}
#else
	return 0;
#endif
}

void Core::keyboard(char* text, uint8_t length) {
#if (ENABLE_GUI > 0)
	display.persistence = false;
	//memset(text, 0, length); //clear the text
	text[length-1] = '\0';
	//active character in the typing area
	int8_t activeChar = 0;
	//selected char on the keyboard
	int8_t activeX = 0;
	int8_t activeY = 2;
	//position of the keyboard on the screen
	int8_t currentX = LCDWIDTH;
	int8_t currentY = LCDHEIGHT;
	int8_t targetX = 0;
	int8_t targetY = 0;

	while (1) {
		if (update()) {
			//move the character selector
			if (buttons.repeat(BTN_DOWN, 4)) {
				activeY++;
				sound.playTick();
			}
			if (buttons.repeat(BTN_UP, 4)) {
				activeY--;
				sound.playTick();
			}
			if (buttons.repeat(BTN_RIGHT, 4)) {
				activeX++;
				sound.playTick();
			}
			if (buttons.repeat(BTN_LEFT, 4)) {
				activeX--;
				sound.playTick();
			}
			//don't go out of the keyboard
			if (activeX == KEYBOARD_W) activeX = 0;
			if (activeX < 0) activeX = KEYBOARD_W - 1;
			if (activeY == KEYBOARD_H) activeY = 0;
			if (activeY < 0) activeY = KEYBOARD_H - 1;
			//set the keyboard position on screen
			targetX = -(display.fontWidth+1) * activeX + LCDWIDTH / 2 - 3;
			targetY = -(display.fontHeight+1) * activeY + LCDHEIGHT / 2 - 4 - display.fontHeight;
			//smooth the keyboard displacement
			currentX = (targetX + currentX) / 2;
			currentY = (targetY + currentY) / 2;
			//type character
			if (buttons.pressed(BTN_A)) {
				if (activeChar < (length-1)) {
					byte thisChar = activeX + KEYBOARD_W * activeY;
					if((thisChar == 0)||(thisChar == 10)||(thisChar == 13)) //avoid line feed and carriage return
					continue;
					text[activeChar] = thisChar;
					text[activeChar+1] = '\0';
				}
				activeChar++;
				sound.playOK();
				if (activeChar > length)
				activeChar = length;
			}
			//erase character
			if (buttons.pressed(BTN_B)) {
				activeChar--;
				sound.playCancel();
				if (activeChar >= 0)
				text[activeChar] = 0;
				else
				activeChar = 0;
			}
			//leave menu
			if (buttons.pressed(BTN_C)) {
				sound.playOK();
				while (1) {
					if (update()) {
						//display.setCursor(0,0);
						display.println(F("You entered\n"));
						display.print(text);
						display.println(F("\n\n\n\x15:okay \x16:edit"));
						if(buttons.pressed(BTN_A)){
							sound.playOK();
							return;
						}
						if(buttons.pressed(BTN_B)){
							sound.playCancel();
							break;
						}
					}
				}
			}
			//draw the keyboard
			for (int8_t y = 0; y < KEYBOARD_H; y++) {
				for (int8_t x = 0; x < KEYBOARD_W; x++) {
					display.drawChar(currentX + x * (display.fontWidth+1), currentY + y * (display.fontHeight+1), x + y * KEYBOARD_W, 1);
				}
			}
			//draw instruction
			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+1*(display.fontHeight+1);
			display.print(F("\25type"));

			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+2*(display.fontHeight+1);
			display.print(F("\26back"));

			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+3*(display.fontHeight+1);
			display.print(F("\27save"));

			//erase some pixels around the selected character
			display.setColor(WHITE);
			display.drawFastHLine(currentX + activeX * (display.fontWidth+1) - 1, currentY + activeY * (display.fontHeight+1) - 2, 7);
			//draw the selection rectangle
			display.setColor(BLACK);
			display.drawRoundRect(currentX + activeX * (display.fontWidth+1) - 2, currentY + activeY * (display.fontHeight+1) - 3, (display.fontWidth+2)+(display.fontWidth-1)%2, (display.fontHeight+5), 3);
			//draw keyboard outline
			//display.drawRoundRect(currentX - 6, currentY - 6, KEYBOARD_W * (display.fontWidth+1) + 12, KEYBOARD_H * (display.fontHeight+1) + 12, 8, BLACK);
			//text field
			display.drawFastHLine(0, LCDHEIGHT-display.fontHeight-2, LCDWIDTH);
			display.setColor(WHITE);
			display.fillRect(0, LCDHEIGHT-display.fontHeight-1, LCDWIDTH, display.fontHeight+1);
			//typed text
			display.cursorX = 0;
			display.cursorY = LCDHEIGHT-display.fontHeight;
			display.setColor(BLACK);
			display.print(text);
			//blinking cursor
			if (((frameCount % 8) < 4) && (activeChar < (length-1)))
			display.drawChar(display.fontWidth * activeChar, LCDHEIGHT-display.fontHeight, '_',1);
		}
	}
#endif
}

void Core::popup(const char* text, uint8_t duration){
#if (ENABLE_GUI > 0)
	popupText = text;
	popupTimeLeft = duration+12;
#endif
}

void Core::updatePopup(){
#if (ENABLE_GUI > 0)
	if (popupTimeLeft){
		uint8_t yOffset = 0;
		if(popupTimeLeft<12){
			yOffset = 12-popupTimeLeft;
		}
		display.fontSize = 1;
		display.setColor(WHITE);
		display.fillRoundRect(0,LCDHEIGHT-display.fontHeight+yOffset-3,84,display.fontHeight+3,3);
		display.setColor(BLACK);
		display.drawRoundRect(0,LCDHEIGHT-display.fontHeight+yOffset-3,84,display.fontHeight+3,3);
		display.cursorX = 4;
		display.cursorY = LCDHEIGHT-display.fontHeight+yOffset-1;
		display.print(popupText);
		popupTimeLeft--;
	}
#endif
}

void Core::setFrameRate(uint8_t fps) {
	timePerFrame = 1000 / fps;
	sound.prescaler = fps / 20;
	sound.prescaler = __avrmax(1, sound.prescaler);
}

void Core::pickRandomSeed(){
        initRandom();
}

bool Core::collidePointRect(int16_t x1, int16_t y1 ,int16_t x2 ,int16_t y2, int16_t w, int16_t h){
	if((x1>=x2)&&(x1<x2+w))
	if((y1>=y2)&&(y1<y2+h))
	return true;
	return false;
}

bool Core::collideRectRect(int16_t x1, int16_t y1, int16_t w1, int16_t h1 ,int16_t x2 ,int16_t y2, int16_t w2, int16_t h2){
  return !( x2     >=  x1+w1  ||
            x2+w2  <=  x1     ||
            y2     >=  y1+h1  ||
            y2+h2  <=  y1     );
}

bool Core::collideBitmapBitmap(int16_t x1, int16_t y1, const uint8_t* b1, int16_t x2, int16_t y2, const uint8_t* b2){
  int16_t w1 = pgm_read_byte(b1);
  int16_t h1 = pgm_read_byte(b1 + 1);
  int16_t w2 = pgm_read_byte(b2);
  int16_t h2 = pgm_read_byte(b2 + 1);

  if(collideRectRect(x1, y1, w1, h1, x2, y2, w2, h2) == false){
    return false;
  }

  int16_t xmin = (x1>=x2)? 0 : x2-x1;
  int16_t ymin = (y1>=y2)? 0 : y2-y1;
  int16_t xmax = (x1+w1>=x2+w2)? x2+w2-x1 : w1;
  int16_t ymax = (y1+h1>=y2+h2)? y2+h2-y1 : h1;
  for(uint8_t y = ymin; y < ymax; y++){
    for(uint8_t x = xmin; x < xmax; x++){
      if(display.getBitmapPixel(b1, x, y) && display.getBitmapPixel(b2, x1+x-x2, y1+y-y2)){
        return true;
      }
    }
  }
  return false;
}


//** EOF **//







