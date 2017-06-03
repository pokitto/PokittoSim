/**************************************************************************/
/*!
    @file     Pokitto_extport.cpp
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

#include "Pokitto.h"

void ext_write(uint32_t value) {
    #if POK_USE_EXT > 0
    /*
    if (value & 1) SET_EXT0 else CLR_EXT0;
    value >>= 1;
    if (value & 1) SET_EXT1 else CLR_EXT1;
    value >>= 1;
    if (value & 1) SET_EXT2 else CLR_EXT2;
    value >>= 1;
    if (value & 1) SET_EXT3 else CLR_EXT3;
    value >>= 1;
    if (value & 1) SET_EXT4 else CLR_EXT4;
    value >>= 1;
    if (value & 1) SET_EXT5 else CLR_EXT5;
    value >>= 1;
    if (value & 1) SET_EXT6 else CLR_EXT6;
    value >>= 1;
    if (value & 1) SET_EXT7 else CLR_EXT7;
    value >>= 1;
    if (value & 1) SET_EXT8 else CLR_EXT8;
    value >>= 1;
    if (value & 1) SET_EXT9 else CLR_EXT9;
    value >>= 1;
    if (value & 1) SET_EXT10 else CLR_EXT10;
    value >>= 1;
    if (value & 1) SET_EXT11 else CLR_EXT11;
    value >>= 1;
    if (value & 1) SET_EXT12 else CLR_EXT12;
    value >>= 1;
    if (value & 1) SET_EXT13 else CLR_EXT13;
    value >>= 1;
    if (value & 1) SET_EXT14 else CLR_EXT14;
    value >>= 1;
    if (value & 1) SET_EXT15 else CLR_EXT15;
    value >>= 1;
    if (value & 1) SET_EXT16 else CLR_EXT16;
    value >>= 1;
    if (value & 1) SET_EXT17 else CLR_EXT17;*/
    #endif
}

