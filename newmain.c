#define _SUPPRESS_PLIB_WARNING
// TETRIS（キャラクターベース） Rev.1.0 2013/8/22
// 　with テキストVRAMコンポジット出力システム for PIC32MX1xx/2xx by K.Tanaka
// rev.2 PS/2キーボードシステムに対応

#include <plib.h>
#include <stdlib.h>
#include "composite32-high4.h"

#include "ff.h"
#include <stdint.h>
#include "fontx2_sd.h"

// 入力ボタンのポート、ビット定義
#define KEYPORT PORTB
#define KEYUP 0x0400
#define KEYDOWN 0x0080
#define KEYLEFT 0x0100
#define KEYRIGHT 0x0200
#define KEYSTART 0x0800
#define KEYFIRE 0x4000



#define SAMPLING_FREQ 32000
#define OUTPUT_FREQ 100000
#define CLOCK_FREQ (3.58*1000000*15)


#define SIZEOFSOUNDBF 2048


//外付けクリスタル with PLL (15倍)
#pragma config PMDL1WAY = OFF, IOL1WAY = OFF
#pragma config FPLLIDIV = DIV_1, FPLLMUL = MUL_15, FPLLODIV = DIV_1
#pragma config FNOSC = PRIPLL, FSOSCEN = OFF, POSCMOD = XT, OSCIOFNC = OFF
#pragma config FPBDIV = DIV_1, FWDTEN = OFF, JTAGEN = OFF, ICESEL = ICS_PGx1

typedef unsigned int uint;

void audiotask(void);

unsigned char sounddata[SIZEOFSOUNDBF] = {0};

unsigned char *cursor; //カーソル位置
unsigned char cursorc; //カーソル色

FIL fhandle;
FATFS fatfs;


int isZENKAKU(unsigned char c){
   if(((c>=0x81)&&(c<=0x9f))||((c>=0xe0)&&(c<=0xfc)))return 1;
   else return 0;
}

void main(void) {
  int read;
  static volatile FRESULT res;

  OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_1, 0);

  // 周辺機能ピン割り当て
  SDI2R = 2; //RPA4:SDI2
  RPB5R = 4; //RPB5:SDO2

  //ポートの初期設定
  TRISA = 0x0010; // RA4は入力
  CNPUA = 0x0010; // RA4をプルアップ
  ANSELA = 0x0000; // 全てデジタル
  TRISB = KEYSTART | KEYFIRE | KEYUP | KEYDOWN | KEYLEFT | KEYRIGHT; // ボタン接続ポート入力設定
  CNPUBSET = KEYSTART | KEYFIRE | KEYUP | KEYDOWN | KEYLEFT | KEYRIGHT; // プルアップ設定
  ANSELB = 0x0000; // 全てデジタル
  LATACLR = 2; // RA1=0（ボタンモード）

  init_composite(); // ビデオ出力システムの初期化

  int curr=0;
  printstr(3, curr++*10, 13, -1, "SD INIT...");
  if (disk_initialize(0) != 0) {
    printstr(7, curr++*10, 13, -1, "SD INIT ERR");
    while (1) asm("wait");
  }
  if (res = f_mount(&fatfs, "", 0) != FR_OK) {
    printstr(7, curr++*10, 13, -1, "SD INIT ERR");
    while (1) asm("wait");
  }
  printstr(3, curr++*10, 13, -1, "SD OK");
    
  FIL font;
  res = fx2_openfont(&font, "MISAKI.FNT");

  if(res){
    printstr(7,curr++*10,13,-1,"<MISAKI.FNT>""CANNOT OPEN");
    while(1) asm("wait");
  }
  printstr(3, curr++*10, 13, -1, "FONT_OK");
  
  int p=0;
  char buff[20000+1];
  char *str;
  FIL txt;
  res = f_open(&txt, "test.txt", FA_READ);
  if(res){
    printstr(7,curr++*10,13,-1,"<test.txt>""CANNOT OPEN");
    while(1) asm("wait");
  }
  printstr(3, curr++*10, 13, -1, "text_OK");

    displayString_on_a_line("\x82\xa8\x82\xcd\x82\xe6\x82\xa4\x82\xb2\x82\xb4\x82\xa2\x82\xdc\x82\xb7\x81\x42\n\x83\x65\x83\x4c\x83\x58\x83\x67\x83\x65\x83\x58\x83\x67\x82\xc5\x82\xb7\x81\x42\x97\xc7\x8d\x44\x82\xc5\x82\xb7\x82\xcb\x81\x49\x81\x49\xe3\x59\x97\xed\x82\xc9\x9f\x54\x82\xc1\x82\xc4\x82\xdc\x82\xb7\x81\x42\n\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x2e\x20\x54\x68\x69\x73\x20\x64\x65\x6d\x6f\x20\x69\x6e\x63\x6c\x75\x64\x65\x20\x73\x6f\x6d\x65\x20\x6d\x75\x6c\x74\x69\x62\x79\x74\x65\x20\x63\x68\x61\x72\x61\x63\x74\x6f\x72\x73\x20\x6c\x69\x6b\x65\x20\x81\x67\x82\x60\x81\x68\x2e\x20\n\x4f\x68\x2c\x20\x69\x73\x20\x69\x74\x20\x73\x6f\x20\x67\x6f\x6f\x64\x3f\n\x93\xfa\x96\x7b\x8c\xea\x82\xe0\x45\x6e\x67\x6c\x69\x73\x68\x82\xe0\x8d\xac\x8d\x87\x95\x5c\x8e\xa6\x82\xe0\x82\xe0\x82\xbf\x82\xeb\x82\xf1\x89\xc2\x94\x5c\x82\xc5\x82\xb7\x81\x42\x44\x4d\x41\x82\xf0\x97\x70\x82\xa2\x82\xbd\x53\x44\x83\x4a\x81\x5b\x83\x68\x93\x5d\x91\x97\x82\xc6\x8d\x87\x82\xed\x82\xb9\x82\xc4\x31\x30\x30\x30\x95\xb6\x8e\x9a\x2f\x82\x93\x82\xd9\x82\xc7\x91\xac\x93\x78\x82\xaa\x8f\x6f\x82\xdc\x82\xb7\x81\x42\n\x0e\xe0\x3d");

    while(1)asm("wait");

  
  while(1){
    str=buff;
    f_read(&txt, buff, 3200, &read);
    while(1){
      fx2_displayFont((unsigned char)str[0]*0x100+(unsigned char)str[1], (p%(256/zn_fontx2.width))*zn_fontx2.width, ((p++/(256/zn_fontx2.width))%(224/zn_fontx2.height))*zn_fontx2.height);
      while(!isZENKAKU(*str))str++;
      str+=2;
      if(*str==0||*str=='\n');
      if(str-buff >= 3200)break;
    }
  }
}
