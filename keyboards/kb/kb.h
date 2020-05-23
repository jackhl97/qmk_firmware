#ifndef KB_H
#define KB_H

#include "quantum.h"

void encoder_update_user(uint8_t index, bool clockwise);

#define KEYMAP( \
	K00, K01, K02, K03, K04  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }  \
}

#endif