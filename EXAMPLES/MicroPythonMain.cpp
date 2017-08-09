/**************************************************************************/
/*!
    @file     MicroPythonMain.cpp
    @author   Hannu Viitala

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

#include "Pokitto.h"
#include "UIWidget.h"
#include <new>

#include <time.h>
#include <sys/time.h>

#include "PythonBindings_SIM.h"

Pokitto::Core game;


/** MAIN */
int main () {

    game.begin();

    // Set the color map
    game.display.palette[0] = 0; // black (backgound)
    game.display.palette[1] = 6438;
    game.display.palette[2] = 18917;
    game.display.palette[3] = 10825;
    game.display.palette[4] = 47398;
    game.display.palette[5] = 688;
    game.display.palette[6] = 41764;
    game.display.palette[7] = 17475;
    game.display.palette[8] = 58225;
    game.display.palette[9] = 13598;
    game.display.palette[10] = 60486;
    game.display.palette[11] = 40179;
    game.display.palette[12] = 42596;
    game.display.palette[13] = 46845;
    game.display.palette[14] = 63245;
    game.display.palette[15] = 65535;
    game.display.persistence = 0;

    #if PROJ_PYTHON_REPL==1

    PythonMain(0, nullptr);

    #else // Run python script

    // Load the python script and start running it.
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wwrite-strings" // The strings below will not be changed in the function called
    char* argv[] = {
        "pokitto_sim.exe",
        "..\\..\\..\\EXAMPLES\\gamemain.py"
    };
    #pragma GCC diagnostic pop

    PythonMain(2, argv);

    #endif

    return 1;
}
