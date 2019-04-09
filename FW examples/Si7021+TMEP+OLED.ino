
/**
 * Meteo-v3 
 * Si7021, OLED and TMEP.EU service example - The temperature and humidity are sent to tmep.cz (tmep.eu)
 * and shown on OLED (0.96", SSD1306).
 * If the WiFi network is not available, sending data through WiFi is skipped.
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 *
 * Si7021 library - https://github.com/LowPowerLab/SI7021
 * Adafruit GFX library https://github.com/adafruit/Adafruit-GFX-Library
 * Adafruit SSD1306 library https://github.com/adafruit/Adafruit_SSD1306
 * 
 */

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SI7021.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA 4 // GPIO4 on D2
#define SCL 5 // GPIO5 on D1
#define ARDUINO_ARCH_ESP8266
#define SLEEP_DELAY_IN_SECONDS  300

// Type of display - only GND, VCC, SCL, SDA, no reset pin
Adafruit_SSD1306 display(NULL);

const char* ssid     = "SSID";
const char* password = "PASSWORD";
const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu

SI7021 sensor;
int wifiEn = 1;

void setup() {
  unsigned int numberOfConnection= 0;
  
  Serial.begin(9600); // Open serial connection to report values to host
  delay(10);
   
  Serial.println();
  Serial.println("Made by chiptron.cz");
  Serial.println("www.chiptron.cz");
  Serial.println("www.time4ee.com");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  delay(100);
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("chiptron.cz");
  display.setCursor(0,10);
  display.println("time4ee.com");
  display.setCursor(0,20);
  display.println("Meteo-v3");
  display.display();
  delay(2000);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    numberOfConnection++;
    Serial.println("Trials:");
    Serial.println(numberOfConnection);
    // if ESPxx can't connect to WiFi -> skip WiFi 
    if (numberOfConnection > 9)
    {
      Serial.println("WiFi connection failed");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Connection ");
      display.println("failed");
      display.println("SSID");
      display.println(ssid);
      display.display();
      delay(3000);

      wifiEn = 0;
      return;
    }
  }
  if(wifiEn == 1)
  {
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  sensor.begin(SDA,SCL);
}
void loop() {
  int temperature = sensor.getCelsiusHundredths();
  unsigned int humidity = sensor.getHumidityPercent();

  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(String(temperature/100.0, 2));
  display.println(" 'C");
  display.setCursor(0, 15);
  display.print(humidity);
  display.println(" %");
  display.display();

  if(wifiEn == 1)
  {
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
  }

  //if you want to use deep sleep, connect RST with D0 (GPIO16)
  //ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
  delay(60000);
  
}
