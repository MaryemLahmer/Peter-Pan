#include "OracleTouch.h"
#include <limits.h>
#include "Arduino.h"
#include <stdint.h>

OracleTouch::OracleTouch(uint8_t pin, uint8_t buttonPin) {
    _pin = pin;
    _nPeople = 0;
    _latestTouchValue = UINT_MAX;
    _noTouch = UINT_MAX;
    _threshold = 0;
    _buttonPin = buttonPin;
}

uint8_t OracleTouch::getTouchCount() {
    return _nPeople;
}

void OracleTouch::begin() {
    pinMode(_buttonPin, INPUT_PULLUP);
    Serial.begin(115200);
    autoCalibration();
}

void OracleTouch::update() {
    touchSetCycles(65500, 256);
    uint16_t touchReadValue =  touchRead(_pin);
    Serial.println(touchReadValue);
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
    touchSetCycles(65500, 256);
    unsigned int size = 500;
    uint16_t threshold = 0;
    float margin = 1.7;
    uint16_t emptyVal = 0;
    uint16_t readouts[size];
    for (int j=0; j<size; j++) {
        touchSetCycles(65500, 256);
        delay(10);
        readouts[j] = touchRead(_pin);
        Serial.println(readouts[j]);
    }

    float tempMean = mean(readouts, size);
    uint16_t tempThreshold = std::ceil(1.5*std_dev(readouts, size));
    if (tempThreshold > threshold) threshold = tempThreshold;

    emptyVal = std::round(tempMean);
    setup(emptyVal, threshold);
    Serial.println("Results :");
    Serial.println(emptyVal);
    Serial.println(threshold);
    Serial.println("Touch calibrated !");
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

uint16_t OracleTouch::max(uint16_t arr[], unsigned int length) {
    uint16_t max = 0;
    for (int i=0; i<length; i++) {
        if (arr[i]>max) max = arr[i];
    }
    return max;
}

uint16_t OracleTouch::min(uint16_t arr[], unsigned int length) {
    uint16_t min = UINT_MAX;
    for (int i=0; i<length; i++) {
        if (arr[i]<min) min = arr[i];
    }
    return min;
}

float OracleTouch::std_dev(uint16_t arr[], unsigned int length) {
    float dev[length];
    float m = mean(arr, length);
    for (int i=0; i<length; i++) {
        dev[i] = (arr[i] - m)*(arr[i] - m);
    }

    return (float) sqrt(mean(dev, length));
}



