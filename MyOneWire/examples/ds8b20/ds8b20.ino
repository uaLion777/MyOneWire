#include "MyOneWire.h"
MyOneWire t(4);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
t.resetPresence(); // инициализация
 t.masterWrite(SKIP_ROM); // отправляем 8-bit команды
 t.masterWrite(CONVERT_T);
 delay(1);
 t.resetPresence();
 t.masterWrite(SKIP_ROM);
 t.masterWrite(READ_SCRATCHPAD); 
 
 byte data[8] = {0};
 uint8_t cntByte = 0;
 uint8_t cntBit = 0;
 
 for (int i=0; i < 64; i++){
  
  
    //if(t.masterRead() == 1){
      data[cntByte] |= t.masterRead() << cntBit; // читаем ответ по одному биту и пишем в байт
    //}
    if(cntBit++ == 7){
    cntBit = 0;
    cntByte++;
    }
  }
  int16_t raw = (data[1] << 8) | data[0];
 Serial.println(raw/16.0);
delay(2000);
}
