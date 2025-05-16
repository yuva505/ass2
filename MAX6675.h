#ifndef MAX6675_H
#define MAX6675_H

#include <Arduino.h>
#include <SPI.h>

class MAX6675 {
public:
    enum Scale { CELSIUS, KELVIN, FAHRENHEIT };
    
    MAX6675(int8_t cs_pin);
    float readTempC();
    float readTempF();
    float readTempK();
    void setScale(Scale scale) { currentScale = scale; }
    Scale getScale() { return currentScale; }  // Added this line
    float getTemp();
    
private:
    int8_t _cs;
    Scale currentScale = CELSIUS;
    uint16_t readData();
};

#endif
