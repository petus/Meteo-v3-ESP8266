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
 * Adafruit BMP085 library (BMP180 is supported)
 * https://github.com/adafruit/Adafruit-BMP085-Library/
*/
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
  
// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  
  Serial.begin(9600); // initialize Serial monitor with 9600
  bmp.begin();  

}

// the loop function runs over and over again forever
void loop() {

  int temperature = bmp.readTemperature();  // read temperature
  int pressure = bmp.readPressure();  // read pressure

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  delay(1000);  // wait one second
  
}
