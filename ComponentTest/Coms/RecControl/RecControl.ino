#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "A01A0";

struct dataPack{
  int rollCon;
  int thrustCon;
  int yawCon;
  int pitchCon;
  int buttonState;
};
dataPack dataRec;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(&dataRec, sizeof(dataPack));
    Serial.print("Left X Value = ");
    Serial.println(dataRec.rollCon);
    Serial.print("Left Y Value = ");
    Serial.println(dataRec.thrustCon);
    Serial.print("Right X Value = ");
    Serial.println(dataRec.yawCon);
    Serial.print("Right Y Value = ");
    Serial.println(dataRec.pitchCon);
    Serial.print("Switch = ");
    Serial.println(dataRec.buttonState);
  }
}
