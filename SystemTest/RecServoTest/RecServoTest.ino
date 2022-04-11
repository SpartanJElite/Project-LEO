#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define leftAileronPin 3
#define rightAileronPin 5
#define rudderServoPin 6
#define elevatorServoPin 9
#define thrustPropPin 10

RF24 radio(7, 8); // CE, CSN
Servo leftAileron;
Servo rightAileron;
Servo elevatorServo;
Servo rudderServo;
Servo thrustProp;

const byte address[6] = "A01A0";

struct dataPack{
  int rollControl;
  int thrustControl;
  int yawControl;
  int pitchControl;
  int buttonControl;
};
dataPack dataRec;

int rollCon;
int thrustCon;
int yawCon;
int pitchCon;
int buttonCon;

int rollServoVal;
int thrustServoVal;
int pitchServoVal;
int yawServoVal;

void manualMode(int rollCon,int thrustCon,int yawCon,int pitchCon){
  rollServoVal = map(rollCon,0,1024,0,180);
  pitchServoVal = map(pitchCon,0,1024,0,180);
  yawServoVal = map(yawCon,0,1024,0,180);
  thrustServoVal = map(thrustCon,0,1024,0,180);
  
  leftAileron.write(rollServoVal);
  rightAileron.write(180-rollServoVal);
  elevatorServo.write(pitchServoVal);
  rudderServo.write(yawServoVal);
  thrustProp.write(thrustServoVal);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

    radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  thrustProp.attach(thrustPropPin,1000,2000);
  leftAileron.attach(leftAileronPin);
  rightAileron.attach(rightAileronPin);
  elevatorServo.attach(elevatorServoPin);
  rudderServo.attach(rudderServoPin);
  


  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(&dataRec, sizeof(dataPack));
    rollCon = dataRec.rollControl;
    thrustCon = dataRec.thrustControl;
    yawCon = dataRec.yawControl;
    pitchCon = dataRec.pitchControl;
    buttonCon = dataRec.buttonControl;
    if(buttonCon == 0){
      manualMode(rollCon,thrustCon,yawCon,pitchCon);
    }
  }
}
