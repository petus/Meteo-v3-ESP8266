/*
 * Meteo-v3 
 * PIR example
 * The PIR module is connected to GPIO12 and 3.3V and GND. 
 * If the sensor is active, the LED (GPIO13) on board is switched on. 
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 * 
 * Based on example from arduino.cc
*/

  int val = 0;
  
// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  
  pinMode(12, INPUT);   // initialize digital pin as an input
  pinMode(13, OUTPUT);  // initialize digital pin as an output

}

// the loop function runs over and over again forever
void loop() {

  val = digitalRead(12);   // read the input pin
  digitalWrite(13, val);  // sets the LED to the button's value
}
