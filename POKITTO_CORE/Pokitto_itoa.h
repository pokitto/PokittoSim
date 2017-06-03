/**************************************************************************/
/*!
    @file     Pokitto_itoa.h
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

#ifndef POKITTO_ITOA_H
#define POKITTO_ITOA_H

#include <stdint.h>

/** MBED online compiler has no itoa or strrev **/

extern void pokItoa(uint16_t, char*,int);
extern void pokUtoa(int16_t, char*,int);
extern void pokLtoa(long, char*,int);

#endif // POKITTO_ITOA_H
