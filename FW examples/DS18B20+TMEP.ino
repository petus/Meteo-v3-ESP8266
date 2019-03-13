/**
 * Meteo-v3 
 * DS18B20 and TMEP.EU service example - The temperature is sent to tmep.cz (tmep.eu)
 * Temperature sensor DS18B20 is connected to GPIO0 (D3)
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 *
 * Based on example from https://github.com/milesburton/Arduino-Temperature-Control-Library
 * Library: https://github.com/milesburton/Arduino-Temperature-Control-Library
 * 
 */

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// Data wire is connected to GPIO0 - D3 of ESP8266
#define ONE_WIRE_BUS 0

// Set oneWire bus
OneWire oneWire(ONE_WIRE_BUS);

#define ARDUINO_ARCH_ESP8266

#define SLEEP_DELAY_IN_SECONDS  300

const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu

// Set oneWire bus for Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  unsigned int numberOfConnections= 0;
  
  Serial.begin(9600); // Open serial connection to report values to host
  delay(10);
   
  Serial.println();
  Serial.println();

  Serial.println("Made by chiptron.cz");
  Serial.println("http://chiptron.cz");
  Serial.println("http://time4ee.com");
  Serial.println("FW version: 1.3");
  
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
        //ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
        delay(1000);
        return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Sensor begin
  sensors.begin();
}


void loop() {
  sensors.requestTemperatures();
  sensors.setResolution(9);
  int temperature = sensors.getTempCByIndex(0);

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
    client.print(String("GET ") + url + "tempC=" + String(temperature) + " HTTP/1.1\r\n" +
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
  //ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
  delay(10000);
  
}
