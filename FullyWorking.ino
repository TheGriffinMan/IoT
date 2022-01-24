#include <SPI.h>
#include <WiFiNINA.h>
#include "ThingSpeak.h"
int ledPin = 13; // Pin connected to LED
int inputPin = 2; // Pin connected to PIR sensor
int pirState = LOW; // Start PIR state LOW with no motion
int val = 0; // Variable for reading the pin status
int pinSpeaker = 10; // Pin connected to piezo
int distance =0; 
const unsigned long channel_id = "1629220";
const char write_api_key[] = "0ETO7EOUSELZQCES";

void setup() {
char ssid[] = "DIGI-8ZTw";   
char pass[] = "BJj57Wmy";    
int status = WL_IDLE_STATUS;   
pinMode(ledPin, OUTPUT); // Set LED as output
 pinMode(inputPin, INPUT); // Set sensor as input
 pinMode(pinSpeaker, OUTPUT);
   
Serial.begin(9600);
Serial.println("Attempting to connect to WPA network...");
status = WiFi.begin(ssid, pass);
if (status != WL_CONNECTED) {
Serial.println("Couldn't get a wifi connection");
while(true);
 }
else {
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("with IP address: ");
 Serial.println(WiFi.localIP());
  }
}
void loop() {
 val = digitalRead(inputPin); // Read PIR input value
 if (val == HIGH) { // Check if input is HIGH
 digitalWrite(ledPin, HIGH); // If it is, turn ON LED
 playTone(300, 160);
 delay(150);
 if (pirState == LOW) {
 // Print to the Serial Monitor if motion detected
 Serial.println("Motion detected!");
 distance=100;
ThingSpeak.setField(1, int(distance, 1));
Serial.println("Posting " + String(distance, 1) + " to ThingSpeak");
 pirState = HIGH;
 }
 } else {
 digitalWrite(ledPin, LOW); // If input is not HIGH, 
 // turn OFF LED
 playTone(0, 0);
 delay(300); 
 if (pirState == HIGH) {
 Serial.println("Motion ended!");
 pirState = LOW;
 }
 }
}
void playTone(long duration, int freq) { // Duration in ms, 
 // frequency in Hz
 duration *= 1000;
 int period = (1.0 / freq) * 1000000;
 long elapsed_time = 0;
 while (elapsed_time < duration) {
 digitalWrite(pinSpeaker, HIGH);
 delayMicroseconds(period / 2);
 digitalWrite(pinSpeaker, LOW);
 delayMicroseconds(period / 2);
 elapsed_time += (period);
 }
}
