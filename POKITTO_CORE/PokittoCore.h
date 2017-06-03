/**************************************************************************/
/*!
    @file     PokittoCore.h
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

#ifndef POKITTOCORE_H
#define POKITTOCORE_H

#include <stdint.h>
#include <math.h>
#ifndef POK_SIM
    #include "pwmout_api.h"
    #include "HWButtons.h"
#else
    #include "PokittoSimulator.h"
#endif
#if POK_USE_CONSOLE > 0
    #include "PokittoConsole.h"
#endif // POK_USE_CONSOLE
#if POK_ENABLE_SD > 0
    #include "Pokitto_disk.h"
#endif

#include "PokittoFonts.h"
#include "PokittoPalettes.h"
#include "PokittoDisplay.h"
#include "PokittoButtons.h"
#include "PokittoBattery.h"
#include "PokittoBacklight.h"
#include "PokittoSound.h"
#include "Pokitto_fakeavr.h"

#define PALETTE_SIZE 16
#define PI 3.141592741f

/** For GB compatibility */
#if PROJ_GAMEBUINO > 0
extern void setup();
extern void loop();
#endif // PROJ_GAMEBUINO

extern uint32_t* ptimer; // re-directed tick counter

namespace Pokitto {

/** Core class.
 *  The Core class is a class consisting of static data and methods.
 *  It handles the lowlevel hardware functions of the Pokitto.
 *  It is declared as static to prevent several instances running at same time.
 */
class Core
{
public:
  /** Create Runtime instance */
  Core();

  /** Components */
  static Backlight backlight;
  static Buttons buttons;
  static Battery battery;
  static Sound sound;
  static Display display;

  // EXCECUTION CONTROL
public:
  /** initialize runtime, GB compatibility */
  static void begin();
  /** initialize runtime */
  static void init();
  /** initialize runtime with switches */
  static void init(uint8_t);
  /** return run state */
  static bool isRunning();
  /** stop running */
  static void quit();
  /** master run state is true as long as program is running */
private:
  static bool run_state;

public:
  // INITIALIZATION
  /** initialize display */
  static void initDisplay();
  /** initialize random generator */
  static void initRandom();
  /** initialize GPIO */
  static void initGPIO();
  /** initialize LCD */
  static void initLCD();
  /** initialize Audio */
  static void initAudio();


  // DISPLAY
public:
  /** initialize backlight */
  static void initBacklight();
private:


private:
  /** backlight PWM pointer*/
  #ifndef POK_SIM
  static pwmout_t backlightpwm;
  #endif

  // TIMEKEEPING
public:
  /** initialize runtime clock */
  static void initClock();
  /** get value of time counter */
  static uint32_t getTime();
  /** wait for milliseconds */
  static void wait(uint16_t);
private:
  /** time of next refresh */
  static uint32_t refreshtime;

  // DIRECT TO SCREEN
public:
  static void showLogo();
  /** immediately clear screen (no buffering) */



  // BUTTON INPUT HANDLING
private:
  static uint8_t heldStates[];
public:
  static void initButtons();
  static void pollButtons();
  static uint8_t leftBtn();
  static uint8_t rightBtn();
  static uint8_t upBtn();
  static uint8_t downBtn();
  static uint8_t aBtn();
  static uint8_t bBtn();
  static uint8_t cBtn();
  static uint8_t leftHeld();
  static uint8_t rightHeld();
  static uint8_t upHeld();
  static uint8_t downHeld();
  static uint8_t aHeld();
  static uint8_t bHeld();
  static uint8_t cHeld();

  static uint8_t leftReleased();
  static uint8_t rightReleased();
  static uint8_t upReleased();
  static uint8_t downReleased();
  static uint8_t aReleased();
  static uint8_t bReleased();
  static uint8_t cReleased();

  // AUDIO RELATED
  static uint8_t ampIsOn();
  static void ampEnable(uint8_t);
  static uint8_t soundbyte;

  // GB RELATED
public:
    static void readSettings();
    static void titleScreen(const char* name, const uint8_t *logo);
	static void titleScreen(const char* name);
	static void titleScreen(const uint8_t* logo);
    static void titleScreen();
    static bool update();
    static uint32_t frameCount;
    static int8_t menu(const char* const* items, uint8_t length);
    static void keyboard(char* text, uint8_t length);
    static void popup(const char* text, uint8_t duration);
    static void setFrameRate(uint8_t fps);
	static void pickRandomSeed();

	static uint8_t getCpuLoad();
    static uint16_t getFreeRam();

    static bool collidePointRect(int16_t x1, int16_t y1 ,int16_t x2 ,int16_t y2, int16_t w, int16_t h);
	static bool collideRectRect(int16_t x1, int16_t y1, int16_t w1, int16_t h1 ,int16_t x2 ,int16_t y2, int16_t w2, int16_t h2);
    static bool collideBitmapBitmap(int16_t x1, int16_t y1, const uint8_t* b1, int16_t x2, int16_t y2, const uint8_t* b2);

private:
    static uint8_t timePerFrame;
    static uint32_t nextFrameMillis;
    static void updatePopup();
    static const char* popupText;
    static uint8_t popupTimeLeft;
    static void displayBattery();
    static uint16_t frameDurationMicros;
    static uint32_t frameStartMicros, frameEndMicros;
    static uint8_t startMenuTimer;

};

// this is the instance used by the system
extern Core core;


}

#endif // POKITTOCORE_H

