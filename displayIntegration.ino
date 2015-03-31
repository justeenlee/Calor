#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"


#define PIN            24 //data in
#define NUMPIXELS      24 //24-pixel ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint16_t delayTime = 50;
//set up color library
uint32_t orange = pixels.Color(243, 156, 18);
uint32_t myMix = pixels.Color(250, 130, 0);
uint32_t black = pixels.Color(0,0,0);
Adafruit_7segment seg = Adafruit_7segment();




void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
  seg.begin(0x70);

}

void loop() {
  allOn(myMix);
  delay(1000);
  countDown();
}


void allOn(uint32_t color){
  seg.writeDigitNum(1, (24 / 60));
  seg.writeDigitNum(3, (24 % 60) / 10);
  seg.writeDigitNum(4, (24 % 60) % 10);
  seg.writeDisplay();
  for (uint16_t i=0; i<24; i++){
      pixels.setPixelColor(i, color);
      pixels.show();
  }
  
}

void countDown(){
  uint16_t counter;
  for (uint16_t i=0; i<24; i++){
    counter = 23 - i;
    seg.writeDigitNum(1, (counter / 60));
    seg.writeDigitNum(3, (counter % 60) / 10);
    seg.writeDigitNum(4, (counter % 60) % 10);
    seg.writeDisplay();
    pixels.setPixelColor(i, black);
    pixels.show();
    delay(1000);
  }
}
