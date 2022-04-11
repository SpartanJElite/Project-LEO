
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
void setup() {
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
}

void loop() {
  if (radio.available()) {
    radio.read(&dataRec, sizeof(dataPack));
    int rollCon = dataRec.rollControl;
    int thrustCon = dataRec.thrustControl;
    int yawCon = dataRec.yawControl;
    int pitchCon = dataRec.pitchControl;
    int buttonCon = dataRec.buttonControl;
    Serial.println(dataRec.rollControl);
    if(buttonCon == 0){
      manualMode(rollCon,thrustCon,yawCon,pitchCon);
    }
  }
}
