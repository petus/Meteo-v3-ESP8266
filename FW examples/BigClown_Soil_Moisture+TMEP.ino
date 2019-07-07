/**
 * Meteo-v3 
 * Soil Moisture sensor and TMEP.CZ service example - the current value is sent to tmep.cz (tmep.eu)
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 *
 * Soil Moisture Arduino library: 
 * https://github.com/podija/SoilSensor
 *
 * DS28B17:
 * https://github.com/podija/DS28E17
 *
 * Soil Moisture tutorial: 
 * https://developers.bigclown.com/hardware/about-soil-moisture-sensor
 * https://developers.bigclown.com/firmware/how-to-soil-moisture-sensor
 * 
 */

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <SoilSensor.h>
#include <DS28E17.h>

#define ARDUINO_ARCH_ESP8266

#define SLEEP_DELAY_IN_SECONDS  300

// Add a 4k7 pull-up resistor to this pin (R4 on MeteoV3)
// 1-wire connector, DATA pin
#define SOIL_SENSOR_PIN 0

const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu

OneWire oneWire(SOIL_SENSOR_PIN);
SoilSensor soilSensor(&oneWire);

void setup() {
  unsigned int numberOfConnections= 0;
  
  Serial.begin(9600); // Open serial connection to report values to host
  delay(10);
   
  Serial.println();
  Serial.println();

  Serial.print("Soil Moisture Sensor by BigClown and MeteoV3\n");
  Serial.print("http://chiptron.cz\n");
  Serial.print("http://time4ee.com\n");
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    numberOfConnections++;

    Serial.println("Number Of Connections:");
    Serial.println(numberOfConnections);

    // if ESP12E can't connect to WiFi -> enable deep.sleep
    if (numberOfConnections > 10)
    {
        //if you want to use deep sleep, connect RST with D0 (GPIO16)
        ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
        delay(1000);
        return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  soilSensor.begin();

}


void loop() {
  // wake-up Soil Sensor
  soilSensor.wakeUp();
  float temperature;
  uint8_t moisture;
  
  // measure temperature and soil moisture
  soilSensor.readTemperatureCelsius(&temperature);
  soilSensor.readMoisture(&moisture);

  Serial.println(temperature);
  Serial.println(moisture);

  // Sleep Soil Sensor
  soilSensor.sleep();

  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }

    // We now create a URI for the request
  String url = "/index.php?";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
    client.print(String("GET ") + url + "tempC=" + temperature + "&humV=" + moisture + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" + 
             "Connection: close\r\n\r\n");

  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

  //if you want to use deep sleep, connect RST with D0 (GPIO16)
  ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
  delay(1000);
  
}
