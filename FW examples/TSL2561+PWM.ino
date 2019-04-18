/************************************
 *                                  *
 *  FW is still in development      *
 *                                  *
 ************************************/


/*
 * Meteo-v3 
 * TSL2561 and PWM
 * TSL2561 module is connected to I2C connector. 
 * The light intensity is measured and compared with requirements and based on 
 * conditions is PWM controled. 
 * Output PWM is GPIO 12.
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 * 
 * TSL2561 library - https://github.com/joba-1/Joba_Tsl2561
*/
#include <ESP8266WiFi.h>
#include <Esp.h>

// Library for TSL2561 
#include <Tsl2561.h>

// TSL2561
Tsl2561 Tsl(Wire);

int pwm = 0;

#define SDA 4 // GPIO4 on D2
#define SCL 5 // GPIO5 on D1

// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  Serial.begin(9600); // initialize Serial monitor with 9600
  pinMode(12, OUTPUT);

  Wire.begin(SDA, SCL);
}

// the loop function runs over and over again forever
void loop() {

  Tsl.begin();

  if( Tsl.available() )
  {
    uint8_t id;
    uint16_t full, ir;

    Tsl.on();

    Tsl.setSensitivity(true, Tsl2561::EXP_14);
    delay(16);

    Tsl.id(id);
    Tsl.fullLuminosity(full);
    Tsl.irLuminosity(ir);

    Serial.print(full); 
    Serial.println(" lux");
    Serial.print("PWM value: ");
    Serial.println(pwm);

    if(full < 40) // comparable value
    {
      if(pwm > 200)
      {
        // skip
      }
      else
      {
        pwm = pwm + 10;
        analogWrite(12, pwm);
      }
    }
    else
    {
      // do nothing
    }
    
    if(full > 45) // comparable value
    {
      if(pwm == 0)
      {
        //skip
      }
      else
      {
        pwm = pwm - 10;
        analogWrite(12, pwm);
      }
    }
    else
    {
      // do nothing
    }
  }
  else 
  {
    Serial.print(format("No Tsl2561 found. Check wiring: SCL=%u, SDA=%u\n", TSL2561_SCL, TSL2561_SDA));
  }

  delay(200);

}
