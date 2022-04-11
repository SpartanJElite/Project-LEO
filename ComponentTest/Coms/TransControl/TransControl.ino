#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define leftXPin A3
#define leftYPin A2
#define rightXPin A0
#define rightYPin A1
#define buttonPin 2

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "A01A0";


int buttonNew;
int buttonOld = 1;
int delayRate = 100;

struct dataSent{
  int leftX;
  int leftY;
  int rightX;
  int rightY;
  int buttonState = 0;
};
dataSent dataCollect;
void setup() {
  // put your setup code here, to run once:
//  Serial.begin(115200);
  pinMode(leftXPin,INPUT);
  pinMode(leftYPin,INPUT);
  pinMode(rightXPin,INPUT);
  pinMode(rightYPin,INPUT);
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  dataCollect.leftX = analogRead(leftXPin);
  dataCollect.leftY = analogRead(leftYPin);
  dataCollect.rightX = analogRead(rightXPin);
  dataCollect.rightY = analogRead(rightYPin);
  buttonNew = digitalRead(buttonPin);
  if(buttonOld == 0 && buttonNew == 1){
    if(dataCollect.buttonState == 0){
      dataCollect.buttonState = 1;
    }else{
      dataCollect.buttonState = 0;
    }
  }
  buttonOld = buttonNew;

  radio.write(&dataCollect, sizeof(dataSent));
  delay(delayRate);
//  Serial.print("Left X Value = ");
//  Serial.println(dataCollect.leftX);
//  Serial.print("Left Y Value = ");
//  Serial.println(dataCollect.leftY);
//  Serial.print("Right X Value = ");
//  Serial.println(dataCollect.rightX);
//  Serial.print("Right Y Value = ");
//  Serial.println(dataCollect.rightY);
//  Serial.print("Switch = ");
//  Serial.println(dataCollect.buttonState);
}
