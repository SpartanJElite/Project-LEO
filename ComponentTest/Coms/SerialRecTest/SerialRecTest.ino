#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "A01A0";

struct dataPack{
  char longGPS[18];
  char latGPS[18];
};

dataPack dataRec;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(&dataRec, sizeof(dataPack));
    Serial.println(sizeof(dataRec.longGPS));
    for(int k = 0;k < sizeof(dataRec.longGPS);k++){
      Serial.print(dataRec.longGPS[k]);
    }
    Serial.println(" ");
    Serial.println(sizeof(dataRec.latGPS));
    for(int k = 0;k < sizeof(dataRec.latGPS);k++){
      Serial.print(dataRec.latGPS[k]);
    }
    Serial.println(" ");
  }
  
}
