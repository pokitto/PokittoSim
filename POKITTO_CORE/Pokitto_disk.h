/**************************************************************************/
/*!
    @file     Pokitto_disk.h
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

#ifndef POKITTO_DISK_H
#define POKITTO_DISK_H

#ifndef POK_SIM
// real hardware disk driver
#include "diskio.h"
#include "pff.h"
#include "connect.h"
#include "mbed.h"
extern BYTE res;
extern FATFS fs;            /* File system object */
extern FATDIR dir;            /* Directory object */
extern FILINFO fno;        /* File information */
extern SPI device;
extern DigitalOut mmccs;

/**************************************************************************/
/**                          SD CONTROL MACROS                           **/
/**************************************************************************/

// CS ... #define CONNECT_CS      P0_7 //p13
#define CLR_SD_CS LPC_GPIO_PORT->CLR[0] = (1 << 7)
#define SET_SD_CS LPC_GPIO_PORT->SET[0] = (1 << 7)
#define GET_SD_CS LPC_GPIO_PORT->PIN[0] & (1 << 7)

#else
// simulated disk driver
#endif

#include <stdint.h>



extern int pokInitSD();

// File IO modes
#define FILE_MODE_APPEND 0x1
#define FILE_MODE_OVERWRITE 0
#define FILE_MODE_READONLY 0x2
#define FILE_MODE_READWRITE 0
#define FILE_MODE_BINARY 0x4
#define FILE_MODE_ASCII 0
#define FILE_MODE_FAILED 0x8
#define FILE_MODE_UNINITIALIZED 0x10

extern uint8_t fileOpen(char*, char);
extern void fileClose();
extern int fileGetChar();
extern void filePutChar(char);
extern void fileWriteBytes(uint8_t *, uint16_t);
extern uint16_t fileReadBytes(uint8_t *, uint16_t);
extern void fileSeekAbsolute(long);
extern void fileSeekRelative(long);
extern void fileRewind();
extern void fileEnd();
extern long int fileGetPosition();
#define fileSetPosition(n)  (fileSeekAbsolute(n))
extern uint8_t filePeek(long);
extern void filePoke(long, uint8_t);
extern char* getCurrentFileName ();
extern int isThisFileOpen(char*);
extern int fileOK();

#endif // POKITTO_DISK_H

