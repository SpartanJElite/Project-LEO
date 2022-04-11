#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "A01A0";

String myCmd;
int idx;


struct dataSent{
  char longGPS[18];
  char latGPS[18];
};

dataSent dataCollect;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
//  while(Serial.available()==0){
//  }
  
//  myCmd = Serial.readStringUntil('\r');
  myCmd = "-14.222685745347366,-51.67077746549359";
  for(int i = 0;i < myCmd.length();i++){
    if(myCmd[i] == ','){
      idx = i;
      break;
    }
  }
  int gpsIdxlong = 0;
  int gpsIdxlat = 0;
  for(int j = 0;j < myCmd.length();j++){
    if(j < idx){
      if((gpsIdxlong<20)){
        dataCollect.longGPS[gpsIdxlong] = myCmd[j];
        gpsIdxlong++;
      }
    }
    if(j > idx){
      if((gpsIdxlat<20)){
        dataCollect.latGPS[gpsIdxlat] = myCmd[j];;
        gpsIdxlat++;
      }
    }
  }
  radio.write(&dataCollect, sizeof(dataSent));
  Serial.println(sizeof(dataCollect.longGPS));
    for(int k = 0;k < sizeof(dataCollect.longGPS);k++){
      Serial.print(dataCollect.longGPS[k]);
    }
    Serial.println(" ");
    Serial.println(sizeof(dataCollect.latGPS));
    for(int k = 0;k < sizeof(dataCollect.latGPS);k++){
      Serial.print(dataCollect.latGPS[k]);
    }
    Serial.println(" ");
}
