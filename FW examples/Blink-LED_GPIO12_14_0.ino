/*
 * Meteo-v3 
 * Blink example
 * LEDs are connected to GPIO12 or/and GPIO14 or/and GPIO0
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
  // initialize digital pins as an output.
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
