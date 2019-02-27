/*
 * Meteo-v3 
 * Blink example - the LED is conencted to GPIO13 (D7)
 * 
 * made by chiptron.cz (2019)
 * 
 * czech website www.chiptron.cz
 * english website www.time4ee.com
 * 
 * Based on example from arduino.cc (Blink)
*/

// the setup function runs once when you disconnect DTR pin or power the board
void setup() {
  // initialize digital pin GPIO13 (D7) as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
