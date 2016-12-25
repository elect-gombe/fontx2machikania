#include <stdio.h>

#include "ff.h"
#include "fontx2_sd.h"
#include "lib_composite32-high.h"

static FIL *fontx2;

#define _STACK_SIZE 256

#define FONT_MAX_WIDTH 32
#define FONT_MAX_HEIGHT 32

/*DON'T EDIT*/
#define OFS_WIDTH 14
#define OFS_HEIGHT 15
#define HEADER_MINSIZE 17

uint8_t fcolor = 7;
uint8_t bcolor = 8;

fontx2_zenkaku_hand_t zn_fontx2;
static FIL *ffp;

const uint8_t fonthn[]={
#include "fonthn.h"
};

int px,py;

FRESULT fx2_openfont(FIL *fp,const char *path){
  FRESULT fr;
  int read;

  fr = f_open(fp, path,FA_READ);

  if(fr!=FR_OK){
    return fr;
  }  
  
  uint8_t temp[HEADER_MINSIZE];
  f_read(fp,temp,HEADER_MINSIZE,&read);

  /*is this zenkaku?*/
  if(temp[16]){
    zn_fontx2.width = temp[14];
    zn_fontx2.height = temp[15];
    zn_fontx2.sizeof_font = ((zn_fontx2.width+7)/8)*zn_fontx2.height;
    /*read about code block*/
    f_read(fp,temp,1,&read);
    zn_fontx2.code_blocks = temp[0];
    f_read(fp,zn_fontx2.code_block_data,4*zn_fontx2.code_blocks,&read);
  }else{
    /*is hankaku. DON'T SUPPORT only embedded*/
    return FR_NO_FILE;
  }

  ffp = fp;
  
  return FR_OK;
}

static
const uint8_t *getFont(uint16_t code){
  static uint8_t data[FONT_MAX_WIDTH*FONT_MAX_HEIGHT/8];
  unsigned int ofs = 0;
  
  {
    unsigned int nc, bc, sb, eb;
    const uint8_t *cblk;

  
    if(code < 0x100){
      ofs = 17+code * ((fonthn[OFS_WIDTH]+7)/8)*fonthn[OFS_HEIGHT];
      return fonthn + ofs;
    }else{
      cblk = zn_fontx2.code_block_data;nc=0;
      bc = zn_fontx2.code_blocks;
      while(bc--){
	sb = cblk[0]+(cblk[1]<<8);
	eb = cblk[2]+(cblk[3]<<8);
	if(code >= sb && code <= eb) {
	  nc += code - sb;
	  ofs = 18 + zn_fontx2.code_blocks * 4 + nc * zn_fontx2.sizeof_font;
	  break;
	}
	nc += eb - sb + 1;
	cblk += 4;
      }
    }

    if(ofs == 0){
      return NULL;
    }
  }
  {
    int read;

    f_lseek(ffp, ofs);
    f_read(ffp, data, zn_fontx2.sizeof_font, &read);

    return data;
  }
}

void fx2_setfcolor(uint8_t col){
  fcolor = col;
}
void fx2_setbcolor(uint8_t col){
  bcolor = col;
}

static
int isZENKAKU(unsigned char c){
   if(((c>=0x81)&&(c<=0x9f))||((c>=0xe0)&&(c<=0xfc)))return 1;
   else return 0;
}

void displayString_on_a_line(const unsigned char *str){
  uint16_t code;
  uint8_t width,height;
  while(*str){
    if(isZENKAKU(*str)){
      width = zn_fontx2.width;
      height = zn_fontx2.height;
      code = *str++;
      code <<= 8;
      code |= *str++;
    }else{
      width = fonthn[OFS_WIDTH];
      height = fonthn[OFS_HEIGHT];
      code = *str++;
    }
    
    if(px+width >= 256){
      py+=height;
      if(py+height >= 224){
	py=0;
      }
      px=0;
    }
  
    fx2_displayFont(code, px, py);
    px+=width;
  }
}

void fx2_displayFont(uint16_t code,int x,int y){
  int px;
  int py;

  unsigned int b;
  unsigned int n;
  const uint8_t *data;

  uint8_t width,height;

  data = getFont(code);
  if(data==NULL)return;

  if(code>0x100){
    width = zn_fontx2.width;
    height = zn_fontx2.height;
  }else{
    width = fonthn[OFS_WIDTH];
    height = fonthn[OFS_HEIGHT];
  }
  
  for(py=0;py<height;py++){
    for(px=0;px<width;px++){
      n = (px / 8) + py * ((zn_fontx2.width + 7) / 8);
      b = 7 - (px % 8);

      if(data[n]&0x01<<b){
	pset(x+px,y+py,fcolor);
      }else{
	pset(x+px,y+py,bcolor);
      }
    }
  }
  
}













