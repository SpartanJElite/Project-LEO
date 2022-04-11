#include <Servo.h>
#define leftAileronPin 3
#define rightAileronPin 5
#define rudderServoPin 6
#define elevatorServoPin 9
#define thrustPropPin 10

Servo leftAileron;
Servo rightAileron;
Servo elevatorServo;
Servo rudderServo;
Servo thrustProp;


void arm(){
  thrustProp.write(0);
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
  thrustProp.attach(thrustPropPin);
  leftAileron.attach(leftAileronPin);
  rightAileron.attach(rightAileronPin);
  elevatorServo.attach(elevatorServoPin);
  rudderServo.attach(rudderServoPin);
  thrustProp.write(0);
  thrustProp.write(180);
  delay(2000);
  arm();
}

void loop() {
  // put your main code here, to run repeatedly:
  thrustProp.write(90);
  leftAileron.write(90);
  rightAileron.write(90);
  elevatorServo.write(90);
  rudderServo.write(90);
//  for(int i = 30;i < 150; i++){
//    elevatorServo.write(i);
//  rudderServo.write(i);
//  delay(500);
//  }

  

}
