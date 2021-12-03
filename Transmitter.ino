//Transmitter for SS Leo

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); //CNS,CE


int pitchVal;
int rollVal;
int yawVal;
int thrustVal;

struct Data_sent
{
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};

Data_sent data_collection;

const byte address[][6] = {"00001","00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address[1]);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  data_collection.ch1 = 127;
  data_collection.ch2 = 127;
  data_collection.ch3 = 127;
  data_collection.ch4 = 127;
  delay(5);
}

void loop() {
  yawVal = map(analogRead(A1),0,1024,0,255);
  pitchVal = map(analogRead(A2),0,1024,0,255);
  thrustVal = map(analogRead(A4),0,1024,255,0);
  rollVal = map(analogRead(A3),0,1024,0,255);
  data_collection.ch1 = pitchVal;
  data_collection.ch2 = rollVal;
  data_collection.ch3 = yawVal;
  data_collection.ch4 = thrustVal;
  radio.write(&data_collection,sizeof(Data_sent));
  
}
