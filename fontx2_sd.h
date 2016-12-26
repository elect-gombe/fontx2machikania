#ifndef _FONTX2_SD_H
#define _FONTX2_SD_H

#include <stdbool.h>
#include <stdint.h>
#include "ff.h"

#define _FX2_MAX_CODE_BLOCK 100

typedef struct {
  uint8_t width;
  uint8_t height;
} fontx2_hankaku_hand_t;

typedef struct {
  uint8_t width;
  uint8_t height;
  unsigned int code_blocks;
  unsigned int sizeof_font;
  uint8_t code_block_data[_FX2_MAX_CODE_BLOCK*4];
} fontx2_zenkaku_hand_t;

FRESULT fx2_openfont(FIL *fp,const char *path);
void fx2_setfcolor(uint8_t col);
void fx2_setbcolor(uint8_t col);
void fx2_displayFont(uint16_t code,int x,int y);
void displayString_on_a_line(const unsigned char *str);

extern 
fontx2_zenkaku_hand_t zn_fontx2;

#endif
