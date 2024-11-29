# ST7735Bitmap
ST7735にビットマップ画像を表示できるスケッチです。  
ArduinoUnoなどのmegaAVRシリーズはもちろん、tinyAVRシリーズ、ESP32、RaspberryPiPicoなどほぼすべてのArduinoマイコンに対応しています。~~DigitalWriteしか使ってないもん~~  
しかし、フルカラーのビットマップは容量が大きいため注意が必要です。例えば、160x80なら25KB、160x128なら40KB必要です。  
このスケッチは16ビットカラーで動作しています。  
[配線](#haisen)  
[ビットマップの表示](#bmp)  
[コマンドリスト](#cmd)  
[ST7735の基礎知識](#chishiki)  
<a id="haisen"></a>  
## 配線
この表はデフォルトの配線です。15行目から18行目をいじることによってピン配置は自由に変えることができます。

## ビットマップの表示  

## コマンドリスト  
  
### メインのコマンド  
**tft_fill** (color ,x ,y ,width ,height )  
**color**色で塗りつぶしたサイズ**width**,**height**の四角形を**x**,**y**に表示する。  
  
**tft_drawBitmap** (bitmap ,x ,y ,width ,height )  
サイズ**width**,**height**のビットマップ画像**bitmap**を**x**,**y**に表示する。  
ビットマップはPROGMEMで保存する必要がある。  
### その他コマンド  
**tft_setpos**(x ,y ,width ,height ) 描く範囲と座標を設定する。  
**tft_color16**(color) 16ビットの色を送る。  
**tft_command**(command) データなしのコマンドを送る。  
**tft_byte**(data) 1バイトのデータを送る。  
## ST7735の基礎知識  
