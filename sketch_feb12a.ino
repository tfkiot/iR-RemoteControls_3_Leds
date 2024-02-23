#include "IRremote.hpp"

const int irReceiverPin = D5;

const int ledPin1 = D0;      
const int ledPin2 = D1;
const int ledPin3 = D3;

unsigned long lastSignalTime = 0;
unsigned long signalIgnoreInterval = 100; // 100 milliseconds

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(irReceiverPin , ENABLE_LED_FEEDBACK);  
  
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT); 
}

void loop() {
  if (IrReceiver.decode()) {

    unsigned long int decCode = IrReceiver.decodedIRData.command;
    Serial.println(decCode, HEX);

  unsigned long currentTime = millis();
    if (currentTime - lastSignalTime > signalIgnoreInterval) {

      if (decCode == 0xA) {
        digitalWrite(ledPin1, !digitalRead(ledPin1));
      } else if (decCode == 0x1B) {
        digitalWrite(ledPin2, !digitalRead(ledPin2));
      } else if (decCode == 0x1F) {
        digitalWrite(ledPin3, !digitalRead(ledPin3));
      }
      
      lastSignalTime = currentTime;
    }

    IrReceiver.resume();
  }
}