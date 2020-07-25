/**
 * 
 * The project with MeteoV3.1 with ESP8266 and air temperature and humidity sensor Si7021
 * and temperature and soil moisture sensor made by hardwario
 * The data is sent to The IoT Guru cloud
 * 
 * Made by chiptron.cz (7/2020)
 * 
 */
#include <ESP8266WiFi.h>
#include <IoTGuru.h>
#include <OneWire.h>
#include <SoilSensor.h>
#include <SI7021.h>

#define SOIL_SENSOR_PIN 0 //data pin of soil sensor
#define SOIL_VCC_PIN  12 // pin which is used as power supply of soil sensor
#define SDA 4 // GPIO4 on D2 - I2C
#define SCL 5 // GPIO5 on D1 - I2C

#define WakeUpDuration  900

const char* ssid      = "SSID";
const char* password  = "PASSWORD";

String userShortId    = "UserShortID";
String deviceShortId  = "DeviceShortID";
String deviceKey      = "DeviceKey";
String nodeKey        = "NodeKey";
IoTGuru iotGuru = IoTGuru(userShortId, deviceShortId, deviceKey);

OneWire oneWire(SOIL_SENSOR_PIN);
SoilSensor soilSensor(&oneWire);
SI7021 sensor;

int count = 0;

void setup() 
{
  WiFi.forceSleepBegin();
  
  Serial.begin(115200);
  delay(10);
  
  pinMode(SOIL_VCC_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);
  // Enable GPIO pin 12 as Vcc pin of Hardwario Soil Moisture sensor
  digitalWrite(SOIL_VCC_PIN, HIGH);

  // Initialize Si7021
  if(!sensor.begin(SDA,SCL))
  {
    Serial.println("Si7021 sensor is not connected");
    Serial.flush();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SOIL_VCC_PIN, LOW);
    ESP.deepSleep(WakeUpDuration * 1000000, WAKE_RF_DEFAULT);  
  }
  // Set heater for better precision
  sensor.setHeater(true);
  delay(5000);
  sensor.setHeater(false);

  // soil moisture sensor
  if(!soilSensor.begin())
  {
    Serial.println("Soil moisture sensor is not connected");
    Serial.flush();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SOIL_VCC_PIN, LOW);
    ESP.deepSleep(WakeUpDuration * 1000000, WAKE_RF_DEFAULT);  
  }

  // Switch to WiFi mode
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
    if(count >= 40)
    {
      Serial.println("SSID or Password is not valid");
      Serial.flush();
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(SOIL_VCC_PIN, LOW);
      ESP.deepSleep(WakeUpDuration * 1000000, WAKE_RF_DEFAULT);  
    }
    count++;
  }
  Serial.println("");
  
  //Set check in duration, the default is 60000 milliseconds.
  iotGuru.setCheckDuration(60000);
  
  //Set the debug printer.
  iotGuru.setDebugPrinter(&Serial);

  delay(100);
}

void loop() 
{
  iotGuru.check();

  float temperatureSoil;
  uint16_t moistureSoil;

  // Measure air temperature and humidity
  float temperatureSi = sensor.getCelsiusHundredths()/100;
  int humiditySi = sensor.getHumidityPercent();
  
  // Measure temperature and soil moisture
  soilSensor.readTemperatureCelsius(&temperatureSoil);
  soilSensor.readMoistureRaw(&moistureSoil);

  Serial.println(temperatureSoil);
  Serial.println(moistureSoil);

  iotGuru.sendHttpValue(nodeKey, "tempkytka1balkon", temperatureSoil);
  iotGuru.sendHttpValue(nodeKey, "humkytka1balkon", moistureSoil); 

  Serial.println(temperatureSi);
  Serial.println(humiditySi);
  
  iotGuru.sendHttpValue(nodeKey, "tempbalkon", temperatureSi);
  iotGuru.sendHttpValue(nodeKey, "humbalkon", humiditySi);  

  digitalWrite(SOIL_VCC_PIN, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.flush();
  ESP.deepSleep(WakeUpDuration * 1000000, WAKE_RF_DEFAULT);

}
