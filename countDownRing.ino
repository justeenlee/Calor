// NeoPixel Ring simple sketch modified by Justeen on 03082015

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN            24 //data in
#define NUMPIXELS      24 //24-pixel ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint16_t delayTime = 50;
//set up color library
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t sunFlower = pixels.Color(241, 196, 15);
uint32_t orange = pixels.Color(243, 156, 18);
uint32_t myMix = pixels.Color(240, 180, 0);
uint32_t black = pixels.Color(0,0,0);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
}

void loop() {
  allOn(myMix);
  delay(1000);
  countDown();
}

void radialWipe(uint32_t c) {
  for(uint16_t i=0; i<24; i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(delayTime); 
  }
}


void allOn(uint32_t color){
  for (uint16_t i=0; i<24; i++){
      pixels.setPixelColor(i, color);
      pixels.show();
  }
}

void countDown(){
  for (uint16_t i=0; i<24; i++){
    pixels.setPixelColor(i, black);
    //pixels.setBrightness(0);
    pixels.show();
    delay(500);
  }
}
