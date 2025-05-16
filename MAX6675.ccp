#include "MAX6675.h"

MAX6675::MAX6675(int8_t cs_pin) : _cs(cs_pin) {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    SPI.begin();
}

uint16_t MAX6675::readData() {
    digitalWrite(_cs, LOW);
    delayMicroseconds(1);
    
    uint16_t data = SPI.transfer16(0);
    
    digitalWrite(_cs, HIGH);
    
    if (data & 0x4) {
        return 0xFFFF; // Error value
    }
    return data;
}

float MAX6675::readTempC() {
    uint16_t data = readData();
    if (data == 0xFFFF) return NAN;
    return (data >> 3) * 0.25;
}

float MAX6675::readTempF() {
    float tempC = readTempC();
    if (isnan(tempC)) return NAN;
    return tempC * 9.0/5.0 + 32;
}

float MAX6675::readTempK() {
    float tempC = readTempC();
    if (isnan(tempC)) return NAN;
    return tempC + 273.15;
}

float MAX6675::getTemp() {
    switch(currentScale) {
        case KELVIN: return readTempK();
        case FAHRENHEIT: return readTempF();
        default: return readTempC();
    }
}
