#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Servo.h>

#define leftAileronPin 3
#define rightAileronPin 5
#define rudderServoPin 6
#define elevatorServoPin 9
#define thrustPropPin 10 
#define BNO055_SAMPLERATE_DELAY_MS (100)

Servo leftAileron;
Servo rightAileron;
Servo elevatorServo;
Servo rudderServo;
Servo thrustProp;
Adafruit_BNO055 myIMU = Adafruit_BNO055();

float pi = 3.14159265359;
float q0;
float q1;
float q2;
float q3;

float k1=.5;
float k2=55;
float k3=.00001;

int milliOld;
int milliNew;
int dt;

float rollTarget=0;
float rollActual;
float rollError=0;
float rollErrorOld;
float rollErrorChange;
float rollErrorSlope=0;
float rollErrorArea=0;
float rollServoVal=90;
 
float pitchTarget=0;
float pitchActual;
float pitchError=0;
float pitchErrorOld;
float pitchErrorChange;
float pitchErrorSlope=0;
float pitchErrorArea=0;
float pitchServoVal=90;

float yawTarget=0;
float yawActual;
float yawError=0;
float yawErrorOld;
float yawErrorChange;
float yawErrorSlope=0;
float yawErrorArea=0;
float yawServoVal=90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myIMU.begin();
  delay(1000);
  int8_t temp=myIMU.getTemp();
  myIMU.setExtCrystalUse(true);
  thrustProp.attach(thrustPropPin,1000,2000);
  leftAileron.attach(leftAileronPin);
  rightAileron.attach(rightAileronPin);
  elevatorServo.attach(elevatorServoPin);
  rudderServo.attach(rudderServoPin);
  leftAileron.write(90);
  rightAileron.write(90);
  elevatorServo.write(90);
  rudderServo.write(90);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  uint8_t system, gyro, accel, mg = 0;
  myIMU.getCalibration(&system, &gyro, &accel, &mg);
   
  imu::Quaternion quat=myIMU.getQuat();
  
  q0 = quat.w();
  q1 = quat.x();
  q2 = quat.y();
  q3 = quat.z();
  
  
  
  float rollActual = atan2(2*(q0*q1+q2*q3),1-2*(q1*q1+q2*q2));
  float pitchActual = asin(2*(q0*q2-q3*q1));
  float yaw=-atan2(2*(q0*q3+q1*q2),1-2*(q2*q2+q3*q3))-(pi/2);
  rollActual = rollActual/(2*3.141592654)*360;
  pitchActual = pitchActual/(2*3.141592654)*360;
  yawActual = yawActual /(2*3.141592654)*360;

  milliOld = milliNew;
  milliNew = millis();
  dt = milliNew-milliOld;

  rollErrorOld = rollError;
  rollError = rollTarget-rollActual;
  rollErrorChange = rollError-rollErrorOld;
  rollErrorSlope = rollErrorChange/dt;
  rollErrorArea = rollErrorArea+rollError*dt;
 
  pitchErrorOld = pitchError;
  pitchError = pitchTarget-pitchActual;
  pitchErrorChange = pitchError-pitchErrorOld;
  pitchErrorSlope = pitchErrorChange/dt;
  pitchErrorArea = pitchErrorArea+pitchError*dt;

  yawErrorOld = yawError;
  yawError = yawTarget-yawActual;
  yawErrorChange = yawError-yawErrorOld;
  yawErrorSlope = yawErrorChange/dt;
  yawErrorArea = yawErrorArea+yawError*dt;

  rollServoVal=rollServoVal+k1*rollError+k2*rollErrorSlope+k3*rollErrorArea;
  pitchServoVal=pitchServoVal+k1*pitchError+k2*pitchErrorSlope+k3*pitchErrorArea;
  yawServoVal=yawServoVal+k1*yawError+k2*yawErrorSlope+k3*yawErrorArea;
  
  Serial.print(rollTarget);
  Serial.print(",");
  Serial.print(rollActual);
  Serial.print(",");
  Serial.print(rollServoVal);
  Serial.print(",");
  Serial.print(pitchTarget);
  Serial.print(",");
  Serial.print(pitchActual);
  Serial.print(",");
  Serial.print(pitchServoVal);
  Serial.print(",");
  Serial.print(yawTarget);
  Serial.print(",");
  Serial.print(yawActual);
  Serial.print(",");
  Serial.print(yawServoVal);
  Serial.print(",");
  Serial.println(system);
   
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
