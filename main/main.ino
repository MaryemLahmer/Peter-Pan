#include "OracleTouch.h"
#include <Adafruit_NeoPixel.h>

#define STEP 51

OracleTouch touch(4);

Adafruit_NeoPixel strip(8, 2, NEO_GRB + NEO_KHZ800);

uint32_t MAX_COLOR = strip.Color(255, 100, 0);


uint32_t colors[6] = {strip.Color(255, 196, 137), //3500K
                      strip.Color(255, 180, 107), //3000K
                      strip.Color(255, 161, 72), //2500K
                      strip.Color(255, 138, 18), //2000K
                      strip.Color(255, 109, 0), //1500K
                      strip.Color(255, 56, 0)}; //1000K

uint32_t color=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(32, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(26, OUTPUT);

  for (int i=0; i<8; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  touch.begin();
  for (int i=0; i<8; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  delay(1000);

}

void loop() {
  touch.update();
  Serial.println(touch.getTouchCount());
  int p = touch.getTouchCount();
  exp2(p);
  //exp2(p);
  //pixieDustExplosion();
  delay(10);
  
}

void exp1(int n) {
  switch (n) {
    case 0 : 
      color = 0;
      lightUp(0);
      break;
    case 1 : 
      color = colors[1];
      lightUp(1);
      break;
    case 2 : 
      color = colors[2];
      lightUp(2);
      break;
    case 3 : 
      color = colors[3];
      lightUp(3);
      break;
    case 4 : 
      color = colors[4];
      lightUp(4);
      break;
    default: 
      color = colors[5];
      lightUp(5);
      break;
  }
  for (int i=0; i<8; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void exp2(int n) {
  switch (n) {
    case 0 : 
      strip.setPixelColor(0, 0);
      strip.setPixelColor(1, 0);
      strip.setPixelColor(2, 0);
      strip.setPixelColor(3, 0);
      strip.setPixelColor(4, 0);
      strip.setPixelColor(5, 0);
      strip.setPixelColor(6, 0);
      strip.setPixelColor(7, 0);
      lightUp(0);
      break;
    case 1 : 
      strip.setPixelColor(0, MAX_COLOR);
      strip.setPixelColor(1, 0);
      strip.setPixelColor(2, 0);
      strip.setPixelColor(3, 0);
      strip.setPixelColor(4, MAX_COLOR);
      strip.setPixelColor(5, 0);
      strip.setPixelColor(6, 0);
      strip.setPixelColor(7, 0);
      lightUp(1);
      break;
    case 2 : 
      strip.setPixelColor(0, MAX_COLOR);
      strip.setPixelColor(1, 0);
      strip.setPixelColor(2, MAX_COLOR);
      strip.setPixelColor(3, 0);
      strip.setPixelColor(4, MAX_COLOR);
      strip.setPixelColor(5, 0);
      strip.setPixelColor(6, MAX_COLOR);
      strip.setPixelColor(7, 0);
      lightUp(2);
      break;
    case 3 : 
      strip.setPixelColor(0, MAX_COLOR);
      strip.setPixelColor(1, MAX_COLOR);
      strip.setPixelColor(2, MAX_COLOR);
      strip.setPixelColor(3, 0);
      strip.setPixelColor(4, MAX_COLOR);
      strip.setPixelColor(5, MAX_COLOR);
      strip.setPixelColor(6, MAX_COLOR);
      strip.setPixelColor(7, 0);
      lightUp(3);
      break;
    case 4 : 
      strip.setPixelColor(0, MAX_COLOR);
      strip.setPixelColor(1, MAX_COLOR);
      strip.setPixelColor(2, MAX_COLOR);
      strip.setPixelColor(3, MAX_COLOR);
      strip.setPixelColor(4, MAX_COLOR);
      strip.setPixelColor(5, MAX_COLOR);
      strip.setPixelColor(6, MAX_COLOR);
      strip.setPixelColor(7, MAX_COLOR);
      lightUp(4);
      break;
    default :
      lightUp(5);
      pixieDustExplosion();
      break;
  }
  strip.show();
}

void pixieDustExplosion() {
  unsigned long lastChange = 0;
  unsigned long duration = 1000;
  unsigned long cycleStart = millis();

  while (cycleStart + duration - millis() > 0) {
    if (millis() - lastChange > 40) {
        for (int i = 0; i < 8; i++) {
          strip.setPixelColor(i, strip.Color(
            255,
            random(50, 150),
            0
          ));
        }
      strip.show();
      lastChange = millis();
    }
  }
}

void lightUp(int stepCount) {
  analogWrite(32, stepCount * STEP);
  analogWrite(33, stepCount * STEP);
  analogWrite(25, stepCount * STEP);
  analogWrite(26, stepCount * STEP);
  analogWrite(27, stepCount * STEP);
  analogWrite(12, stepCount * STEP);
  analogWrite(14, stepCount * STEP);
}


