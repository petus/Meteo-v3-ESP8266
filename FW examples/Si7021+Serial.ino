/**
 * Meteo-v3
 * Si7021 exmaple - connect Si7021 module to I2C connector and check the serial monitor
 *
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 *
 * Si7021 library - https://github.com/LowPowerLab/SI7021
 * 
 */

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SI7021.h>

#define SDA 4 // GPIO4 on D2
#define SCL 5 // GPIO5 on D1

SI7021 sensor;

void setup() {
  Serial.begin(9600); // Open serial connection to report values to host
  delay(100);
   
  Serial.println("Weather station by chiptron.cz");
  Serial.println("www.chiptron.cz");
  Serial.println("www.time4ee.com");
  Serial.println("FW version: 0.1");
  
  sensor.begin(SDA,SCL);

}


void loop() {
  int temperature = sensor.getCelsiusHundredths();
  unsigned int humidity = sensor.getHumidityPercent();

  Serial.print("Temperature: ");
  Serial.print(String(temperature/100.0, 2));
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  //if you want to use deep sleep, connect RST with D0 (GPIO16)
  //ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
  delay(10000);
  
}
