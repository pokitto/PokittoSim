/**************************************************************************/
/*!
    @file     Pokitto.h
    @author   Jonne Valola

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

#ifndef __POKITTO_H__
#define __POKITTO_H__

#include "Pokitto_settings.h"
#include "PokittoCore.h"

//typedef void (*funcptr)(PokittoApp&);

#ifndef POK_SIM
    #include "mbed.h"
    #include "HWLCD.h"
    #include "Pokitto_timer.h"
    #include "Pokitto_extport.h"
    #include "PokittoEEPROM.h"
#else
    #include "PokittoSimulator.h"
#endif // if not POK_SIM


#if POK_ENABLE_SD > 0
    #ifndef POK_SIM
        #include "Pokitto_disk.h"
    #else
        #include "FileIO.h"
    #endif // if not POK_SIM
#endif // if SD ENABLED

#if POK_ENABLE_SOUND > 0
    #include "Synth.h"
    extern uint8_t soundbuf[];
    #ifndef POK_SIM
        #include "HWSound.h"
    #endif // if not POK_SIM
#endif // if POK_ENABLE_SOUND

/*extern void dac_write(uint8_t);
extern void ext_write(uint32_t);
extern uint16_t pokGetBattP1();
extern uint16_t pokGetBattP2();
extern void pokInitRandom();
extern void pokSoundIRQ();
*/

#endif //__POKITTO_H__
