/**************************************************************************/
/*!
    @file     Pokitto_fakeavr.h
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

#ifndef _POKITTO_FAKEAVR_H_
#define _POKITTO_FAKEAVR_H_

#include "Pokitto_itoa.h"
#include "binary.h"
#include <stdint.h>
#include <stdlib.h>

#ifdef POK_SIM
#include <stdbool.h>
#else
#include <stdbool.h>
#endif // POK_SIM

#define _BV(bit) (1 << (bit)) //jonne

/** data types */
typedef bool boolean;
typedef uint8_t byte;

/** PROGMEM */
#define PROGMEM
#define F

/** AVR program memory string functions **/
#define sprintf_P sprintf
#define strstr_P strstr
#define strcpy_P strcpy

#define utoa pokItoa
#define ultoa pokItoa

/** PROGMEM hacks **/
#define PROGMEM
    #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
    #ifndef WIN32
    #define pgm_read_word(addr) (*(const unsigned short *)(addr))
    #else
    #define pgm_read_word(addr) (*(const unsigned int *)(addr))
    #endif // WIN32

/** min max & others **/


#ifndef DISABLEAVRMIN
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#endif // DISABLEAVRMIN
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define min2(a,b) (((a)<(b))?(a):(b))



#ifdef __cplusplus
extern "C" {
#endif

void cli();
void sei();

#ifdef __cplusplus
}
#endif
#endif
