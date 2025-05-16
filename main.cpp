#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX6675.h"

// LCD Configuration (use address from scanner)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MAX6675 Configuration
MAX6675 thermocouple(5); // CS on pin 5

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Initializing...");
  
  // Initialize MAX6675
  thermocouple.setScale(MAX6675::CELSIUS);
  
  delay(1000);
  lcd.clear();
}

void loop() {
  float temp = thermocouple.getTemp();
  
  // Update LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1); // 1 decimal place
  lcd.print(" ");
  
  switch(thermocouple.getScale()) {
    case MAX6675::KELVIN: lcd.print("K"); break;
    case MAX6675::FAHRENHEIT: lcd.print("F"); break;
    default: lcd.print("C");
  }
  
  // Update Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");
  
  delay(1000);
}
