
/**
 * Meteo-v3 
 * Si7021 and TMEP.EU service example - The temperature and humidity are sent to tmep.cz (tmep.eu)
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

#define ARDUINO_ARCH_ESP8266

#define SLEEP_DELAY_IN_SECONDS  30

const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu

SI7021 sensor;

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
  sensor.begin(SDA,SCL);

}


void loop() {
  int temperature = sensor.getCelsiusHundredths();
  unsigned int humidity = sensor.getHumidityPercent();

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

  //temperatureH = String(temperature/100.0, 2);

  // This will send the request to the server
    client.print(String("GET ") + url + "tempC=" + String(temperature/100.0, 2) + "&humV=" + humidity + " HTTP/1.1\r\n" +
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
