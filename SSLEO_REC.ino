
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

RF24 radio(7,8); //CNS,CE
const byte address[][6] = {"00001","00002"};
Servo myServo;
boolean buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  myServo.attach(5);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1,address[1]);
  radio.setPALevel(RF24_PA_MIN);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
  radio.startListening();
  if(radio.available())
  {
    while(radio.available())
    {
      int angleV = 0;
      radio.read(&angleV,sizeof(angleV));
      myServo.write(angleV);
    }
    delay(5);
    radio.stopListening();
    buttonState = digitalRead(2);
    radio.write(&buttonState,sizeof(buttonState));
  }
}
