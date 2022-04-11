#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
 
 
#define BNO055_SAMPLERATE_DELAY_MS (100)
 
Adafruit_BNO055 myIMU = Adafruit_BNO055();
float pi = 3.14159265359;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myIMU.begin();
delay(1000);
int8_t temp=myIMU.getTemp();
myIMU.setExtCrystalUse(true);
}
 
void loop() {
  // put your main code here, to run repeatedly:
uint8_t system, gyro, accel, mg = 0;
myIMU.getCalibration(&system, &gyro, &accel, &mg);
 
imu::Quaternion quat=myIMU.getQuat();

float q0 = quat.w();
float q1 = quat.x();
float q2 = quat.y();
float q3 = quat.z();



float roll=atan2(2*(q0*q1+q2*q3),1-2*(q1*q1+q2*q2));
float pitch=asin(2*(q0*q2-q3*q1));
float yaw=-atan2(2*(q0*q3+q1*q2),1-2*(q2*q2+q3*q3))-(pi/2);
roll=roll/(2*3.141592654)*360;
pitch=pitch/(2*3.141592654)*360;
yaw=yaw/(2*3.141592654)*360;
 
Serial.print(roll);
Serial.print(",");
Serial.print(pitch);
Serial.print(",");
Serial.print(yaw);
Serial.println(system);
 
delay(BNO055_SAMPLERATE_DELAY_MS);
}
