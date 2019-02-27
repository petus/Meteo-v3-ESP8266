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

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(D7, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
