/*
ST7735 Arduino
2024-11-27 jyujyun

https://3shokudango.web.fc2.com
*/


#include "image.h"

/*
ピン設定
どのGPIOでもOK!
*/
#define CLK 13 //Clock
#define DAT 11 //Data
#define RST 9  //Reset
#define DC 8   //Data Command


void setup() {
  //ピン設定
  pinMode(CLK,OUTPUT);
  pinMode(DAT,OUTPUT);
  pinMode(RST,OUTPUT);
  pinMode(DC,OUTPUT);

  //ハードウェアリセット
  digitalWrite(RST,1);
  delay(300);
  digitalWrite(RST,0);
  delay(100);
  digitalWrite(RST,1);
  delay(300);

  tft_command(0x01); //ソフトウェアリセット
  delay(500);
  tft_command(0x28); //画面オフ
  tft_command(0x11); //スリープ解除

  //色設定
  digitalWrite(DC,0);
  tft_byte(0x3A);
  digitalWrite(DC,1);
  tft_byte(0x5);
  digitalWrite(DC,0);

  //画面設定
  digitalWrite(DC,0);
  tft_byte(0x36);
  digitalWrite(DC,1);
  tft_byte(0b01101000);
  digitalWrite(DC,0);
  
  /*Pガンマ*/
  digitalWrite(DC,0);
  tft_byte(0xE0);
  digitalWrite(DC,1);
  tft_byte(0x09);
  tft_byte(0x16);
  tft_byte(0x09);
  tft_byte(0x20);
  tft_byte(0x21);
  tft_byte(0x1B);
  tft_byte(0x13);
  tft_byte(0x19);
  tft_byte(0x17);
  tft_byte(0x15);
  tft_byte(0x1E);
  tft_byte(0x2B);
  tft_byte(0x04);
  tft_byte(0x05);
  tft_byte(0x02);
  tft_byte(0x0E);
  digitalWrite(DC,0);

  /*Nガンマ*/
  digitalWrite(DC,0);
  tft_byte(0xE1);
  digitalWrite(DC,1);
  tft_byte(0x0B);
  tft_byte(0x14);
  tft_byte(0x08);
  tft_byte(0x1E);
  tft_byte(0x22);
  tft_byte(0x1D);
  tft_byte(0x18);
  tft_byte(0x1E);
  tft_byte(0x1B);
  tft_byte(0x1A);
  tft_byte(0x24);
  tft_byte(0x2B);
  tft_byte(0x06);
  tft_byte(0x06);
  tft_byte(0x02);
  tft_byte(0x0F);
  digitalWrite(DC,0);
  
  //ふつうモード
  tft_command(0x13);
  tft_command(0x20);



  tft_command(0x29);  //画面オン

  delay(100);

  tft_fill(0xFFFF); //画面クリア


  drawfullbitmap(img1,0,0,160,80); //ビットマップ転送


}
//色を送る
void tft_color16(int cc)
{
  tft_byte(~(cc >> 8));
  tft_byte(~(cc & 0x00FF));
}
//サイズと座標設定
void tft_setpos(uint8_t cx,uint8_t cy,uint8_t cw,uint8_t ch)
{
  digitalWrite(DC,0);
  tft_byte(0x2A);
  digitalWrite(DC,1);
  tft_byte(0);
  tft_byte(cx + 1);
  tft_byte(0);
  tft_byte(cx + cw);
  digitalWrite(DC,0);

  digitalWrite(DC,0);
  tft_byte(0x2B);
  digitalWrite(DC,1);
  tft_byte(0);
  tft_byte(cy + 26);
  tft_byte(0);
  tft_byte(cy + ch + 25);
  digitalWrite(DC,0);
}
//コマンド送る
void tft_command(uint8_t sbyte)
{
  digitalWrite(DC,0);
  tft_byte(sbyte);
  digitalWrite(DC,1);
}
//1バイト送る
void tft_byte(uint8_t sbyte)
{
  //ハードウェアSPIにするべきだった?
  for (char i = 0;i < 8;i ++)
  {
    digitalWrite(CLK,0);
    digitalWrite(DAT,(sbyte >> (7 - i)) & 0x01);
    digitalWrite(CLK,1);
  }
}
//画面を1色で埋める
void tft_fill(uint16_t cc)
{
  tft_setpos(0,0,160,80);
  digitalWrite(DC,0);
  tft_byte(0x2C);
  digitalWrite(DC,1);
  for (int i = 0;i < 160*80;i ++)
  {
    tft_color16(cc);
  }
  digitalWrite(DC,0);

}
//160x80のビットマップを描く
void drawfullbitmap(const uint16_t  bmp[],uint8_t cx,uint8_t cy,uint8_t cw,uint8_t ch)
{
  tft_setpos(cx,cy,cw,ch);

  digitalWrite(DC,0);
  tft_byte(0x2C);
  digitalWrite(DC,1);
  for (int i = 0;i < cw*ch;i ++)
  {
    tft_color16(pgm_read_word(&bmp[i]));
  }
  digitalWrite(DC,0); 
}

void loop() {



  
}
