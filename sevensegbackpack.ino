#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment seg = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
  seg.begin(0x70);
}

void loop(){
  for (uint16_t counter = 300; counter > 0; counter--) {
    seg.writeDigitNum(1, (counter / 60));
    seg.writeDigitNum(3, (counter % 60) / 10);
    seg.writeDigitNum(4, (counter % 60) % 10);
    seg.writeDisplay();
    delay(1000);
  }
  seg.writeDigitNum(4,0);
  seg.writeDisplay();
  delay(1000);
  while (1){
    int brightness = 15;
    while (brightness > 0) {
      seg.setBrightness(brightness);
      brightness -= 1;
      delay(70);
    }
    while (brightness < 15) {
      seg.setBrightness(brightness);
      brightness += 1;
      delay(70);
    }
  }
}
