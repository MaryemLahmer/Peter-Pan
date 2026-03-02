#include "OracleTouch.h"
#include <limits.h>
#include "Arduino.h"
#include <stdint.h>

OracleTouch::OracleTouch(uint8_t pin) {
    _pin = pin;
    _nPeople = 0;
    _latestTouchValue = UINT_MAX;
    _noTouch = UINT_MAX;
    _threshold = 0;
}

uint8_t OracleTouch::getTouchCount() {
    return _nPeople;
}

void OracleTouch::begin() {
    autoCalibration();
}

void OracleTouch::update() {
    touchSetCycles(65500, 256);
    uint16_t touchReadValue =  touchRead(_pin);
    if (touchReadValue > _noTouch - _threshold) _nPeople = 0;
    else {
        if (touchReadValue > _latestTouchValue + _threshold) _nPeople--;
        else if (touchReadValue < _latestTouchValue - _threshold) _nPeople++;
    }
    _latestTouchValue = touchReadValue;
}

void OracleTouch::setup(uint16_t noTouch, uint16_t threshold) {
    _threshold = threshold;
    _noTouch = noTouch;
}

void OracleTouch::autoCalibration() {
    unsigned int size = 500;
    uint16_t readouts[size];
    for (int j=0; j<size; j++) {
        touchSetCycles(65500, 256);
        delay(10);
        readouts[j] = touchRead(_pin);
    }
    float emptyVal = std::round(mean(readouts, size));
    uint16_t threshold = std::ceil(1.5*std_dev(readouts, size));
    setup(emptyVal, threshold);
}

float OracleTouch::mean(uint16_t arr[], unsigned int length) {
    float mean = 0;
    for (int i=0; i<length; i++) {
        mean += arr[i];
    }
    return mean/length;
}

float OracleTouch::mean(float arr[], unsigned int length) {
    float mean = 0;
    for (int i=0; i<length; i++) {
        mean += arr[i];
    }
    return mean/length;
}

float OracleTouch::std_dev(uint16_t arr[], unsigned int length) {
    float dev[length];
    float m = mean(arr, length);
    for (int i=0; i<length; i++) {
        dev[i] = (arr[i] - m)*(arr[i] - m);
    }

    return (float) sqrt(mean(dev, length));
}



