
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int delayTimer = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN,HIGH);
  delay(delayTimer);
  digitalWrite(LED_BUILTIN,LOW);  
  delay(delayTimer);
}
