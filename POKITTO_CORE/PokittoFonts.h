#ifndef POK_FONTS_H
#define POK_FONTS_H

#include "Pokitto_settings.h"

extern const unsigned char fontMini[];
extern const unsigned char fontDonut[];
extern const unsigned char fontDragon[];
extern const unsigned char fontKarateka[];
extern const unsigned char fontKoubit[];
extern const unsigned char fontRunes[];
extern const unsigned char fontTight[];
extern const unsigned char fontTiny[];
extern const unsigned char fontAdventurer[];
extern const unsigned char font5x7[];
extern const unsigned char font3x5[];
extern const unsigned char font3x3[];

#if POK_GAMEBUINO_SUPPORT > 0
#define DEFAULT_FONT font3x5
#else
#define DEFAULT_FONT font5x7
#endif // POK_GAMEBUINO_SUPPORT


#endif
