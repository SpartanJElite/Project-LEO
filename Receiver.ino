//Reciever for SS Leo

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

RF24 radio(9,10);
const byte address[][6] = {"00001","00002"};
Servo pitchServo;
Servo rollServo;
Servo yawServo;
Servo roll2Servo;
Servo tho;
int pitchstater = 95;
int rollstater = 100;
int yawstater = 90;
int pitchVal;
int rollVal;
int yawVal;
int thrustVal;

struct Data_received
{
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};

Data_received data_received;

void setup() {
  Serial.begin(9600);
  data_received.ch1 = 127;
  data_received.ch2 = 127;
  data_received.ch3 = 127;
  data_received.ch4 = 127;
  pitchServo.attach(6);
  rollServo.attach(5);
  yawServo.attach(4);
  tho.attach(2);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,address[1]);
  radio.setPALevel(RF24_PA_MAX);
  rollServo.write(rollstater);
  yawServo.write(yawstater);
  pitchServo.write(pitchstater);
  radio.startListening();
  delay(5);


}

void loop() {
  while(radio.available())
  {
    delay(5);
    radio.read(&data_received,sizeof(Data_received));
    pitchVal = data_received.ch1;
    rollVal = data_received.ch2;
    yawVal = data_received.ch3;
    thrustVal = data_received.ch4;
    pitchVal = map(pitchVal,0,255,pitchstater-45,pitchstater+45);
    rollVal = map(rollVal,0,255,rollstater-45,rollstater+45);
    rollVal = 100;
    yawVal = map(yawVal,0,255,yawstater-45,yawstater+45);
    thrustVal = map(thrustVal,127,255,1000,1500); //might change
    pitchServo.write(pitchVal);
    rollServo.write(rollVal);
    yawServo.write(yawVal);
    tho.writeMicroseconds(thrustVal);
    Serial.println(rollVal);
  }
  //rollServo.write(100);
  Serial.println(rollVal);
}
