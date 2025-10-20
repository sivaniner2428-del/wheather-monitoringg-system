#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// --------- USER SETUP ---------
// DHT11 sensor
#define DHTPIN 2       // D4 on NodeMCU
#define DHTTYPE DHT11

// I2C LCD setup
// Check your LCD I2C address: usually 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Initialize DHT11
  dht.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if reading failed
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223); // degree symbol
    lcd.print("C  ");

    lcd.setCursor(0, 1);
    lcd.print("Hum:  ");
    lcd.print(humidity);
    lcd.print("%   ");
  }

  delay(2000); // update every 2 seconds
}
