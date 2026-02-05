#ifndef OracleTouch_h
#define OracleTouch_h

#pragma once
#include "Arduino.h"
#include <stdint.h>

class OracleTouch {
    public : 
        OracleTouch(uint8_t pin, uint8_t buttonPin);
        uint8_t getTouchCount();
        void update();
        void begin();
        void setup(uint16_t noTouch, uint16_t threshold);
        void autoCalibration();
        float mean(uint16_t arr[], unsigned int length);
        float mean(float arr[], unsigned int length);
        uint16_t min(uint16_t arr[], unsigned int length);
        uint16_t max(uint16_t arr[], unsigned int length);
        float std_dev(uint16_t arr[], unsigned int length);
    private:
        uint8_t _pin;
        uint8_t _nPeople;
        uint16_t _latestTouchValue;
        uint16_t _noTouch;
        uint16_t _threshold;
        uint8_t _buttonPin;
};

#endif 