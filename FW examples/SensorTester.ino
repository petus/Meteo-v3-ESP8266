
/**
 * *****************************************************************************************
 *                              FW still in development
 * *****************************************************************************************
 * 
 * Meteo-v3 
 * Testing FW for Meteo-v3, connect your device and write command to Serial terminal.
 * FW checks and reads sensor and write values.
 * Write "help" for available commands
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 *
 * Si7021 library - https://github.com/LowPowerLab/SI7021
 * Adafruit Unified Sensor library https://github.com/adafruit/Adafruit_Sensor
 * BMP180 library - https://github.com/adafruit/Adafruit-BMP085-Library (BMP180 is supported)
 * TSL2561 libray - https://github.com/adafruit/Adafruit_TSL2561
 * DS18B20 library - https://github.com/milesburton/Arduino-Temperature-Control-Library
 */

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SI7021.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SDA 4 // GPIO4 on D2
#define SCL 5 // GPIO5 on D1

#define ONE_WIRE_BUS 0

#define ARDUINO_ARCH_ESP8266

String readString;

void setup() 
{
  Serial.begin(9600); // Open serial connection to report values to host
  while(!Serial)
  {
    // waiting for opening of Serial
  }

  Serial.println("Serial is open");
  Serial.println("For Help - write 'help'");

}


void loop() 
{
  readString = Serial.readString();

  if (readString == "help")
  {
    Serial.println("*****HELP*****");
    Serial.println("Write 'i2scanner' for scanning of I2C bus");
    Serial.println("Write 'si7021' for reading from Si7021");
    Serial.println("Write 'bmp180' for reading from BMP180");
    Serial.println("Write 'ds18b20' for reading from DS18B20");
    Serial.println("Write 'tsl2561' for reading from TSL2561");

  }
  else if (readString == "i2scanner")
  {
    Serial.println("*****I2C Scanner*****");
    //code developed by https://playground.arduino.cc/Main/I2cScanner/
    byte error, address;
    int nDevices;
  
    Serial.println("Scanning...");
  
    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
  
      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("  !");
  
        nDevices++;
      }
      else if (error==4)
      {
        Serial.print("Unknown error at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.println(address,HEX);
      }    
    }
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");

    Serial.println("*****I2C Scanner*****");
  }
  else if (readString == "si7021")
  {
    Serial.println("*****Si7021*****");
    Serial.println("Connect SDA to 4, SCL to 5");

    SI7021 sensor;
    sensor.begin(SDA,SCL);
    /*if(!sensor)
    {
      Serial.println("Sensor is not connected.");
    }
    else*/
    {
      int temperature = sensor.getCelsiusHundredths();
      unsigned int humidity = sensor.getHumidityPercent();
      Serial.println("Temperature");
      Serial.print(String(temperature/100.0, 2));
      Serial.println(" °C");
      Serial.println("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    }
 
    Serial.println("*****Si7021*****");
    //sensor.flush();
  }
  else if (readString == "bmp180")
  {
    Serial.println("*****BMP180*****");
    Serial.println("Connect SDA to 4, SCL to 5");

    Adafruit_BMP085 bmp180;
    bmp180.begin();
    /*if(!bmp180)
    {
      Serial.println("Sensor is not connected.");
    }
    else*/
    {
      int temperature = bmp180.readTemperature();  // read temperature
      int pressure = bmp180.readPressure();  // read pressure
      Serial.println("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
      Serial.println("Pressure: ");
      Serial.print(pressure);
      Serial.println(" Pa");
    }

    Serial.println("*****BMP180*****");
    //bmp180.flush();
  }
  else if (readString == "tsl2561")
  {
    Serial.println("*****TSL2561*****");
    Serial.println("Connect SDA to 4, SCL to 5");

    Adafruit_TSL2561_Unified TSL2561 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
    sensor_t sensor;
    /*if(!TSL2561)
    {
      Serial.println("Sensor is not connected.");
    }
    else*/
    {
      TSL2561.getSensor(&sensor);
      TSL2561.enableAutoRange(true);
      TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
      sensors_event_t event;
      TSL2561.getEvent(&event)  ;
      Serial.println("Light");
      Serial.print(event.light); 
      Serial.println(" lux"); 
    }
    
    Serial.println("*****TSL2561*****");
    //TSL2561.flush();

  }
  else if (readString == "ds18b20")
  {
    Serial.println("*****DS18B20*****");
    Serial.println("Connect DS18B20 Data to GPIO0 (D3)");
    
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature DS18B20(&oneWire);
    /*if(!DS18B20)
    {
      Serial.println("Sensor is not connected.");
    }
    else*/
    {
      DS18B20.requestTemperatures();
      Serial.println("Temperature: ");
      Serial.print(DS18B20.getTempCByIndex(0));
      Serial.println(" °C");
    }

    Serial.println("*****DS18B20*****");
    //DS18B20.flush();
  }
  else
  {
    Serial.println("Unknown command");
    Serial.println("Write 'help'");
  }
  Serial.flush();
}
