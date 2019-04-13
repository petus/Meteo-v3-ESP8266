/*
 * Meteo-v3 
 * BMP180
 * BMP180 module is connected to I2C connector. Temperature and 
 * pressure are shown on Serial Monitor (9600)
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 * 
 * Adafruit BMP085 library (BMP180 is supported) API v2
 * https://github.com/adafruit/Adafruit_BMP085_Unified
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  
  Serial.begin(9600); // initialize Serial monitor with 9600
  bmp.begin();  

}

// the loop function runs over and over again forever
void loop() {

  sensors_event_t event;
  bmp.getEvent(&event);

  if(event.pressure)
  {
    float temperature;
    bmp.getTemperature(&temperature);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Pressure: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");

  }
  delay(1000);  // wait one second
  
}
