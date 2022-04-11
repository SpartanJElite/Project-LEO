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
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()==0){
    pinMode(13,OUTPUT);
  }
  char longGPS[18];
  char latGPS[18];
  myCmd = Serial.readStringUntil('\r');
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
