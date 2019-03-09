/*
 * Meteo-v3 
 * 1-wire example - Temperature sensor DS18B20 is connected to GPIO0 (D3)
 * the temperature is sent to Serial Monitor
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 * 
 * Based on example from https://github.com/milesburton/Arduino-Temperature-Control-Library
 * Library: https://github.com/milesburton/Arduino-Temperature-Control-Library
*/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO0 - D3 of ESP8266
#define ONE_WIRE_BUS 0

// Set oneWire bus
OneWire oneWire(ONE_WIRE_BUS);

// Set oneWire bus for Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  // Set Serial Com Port
  Serial.begin(9600);

  // Sensor begin
  sensors.begin();
}

// the loop function runs over and over again forever
void loop() {
  // Temperature request, send command to get the temperatures
  sensors.requestTemperatures();
  Serial.print(" The temperature for the first device (index 0): ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" °C");
  //Serial.print(" The temperature for the second device (index 1)");
  //Serial.print(sensors.getTempCByIndex(1));
  //Serial.println(" °C");
  delay(1000);
}
