/* RECIEVER FOR LEO
 *  
 * PIN LAYOUT FOR nRF24L01
 * LEFT TO RIGHT TO DOWN (GND, VCC, CE, CNS, SCK, MOSI, MISO, IRQ)
 * GND to GND
 * VCC to 3.3V
 * CE to 7
 * CNS to 8
 * SCK to 13
 * MOSI to 11
 * MISO to 12
 * 
 * IMU MPU6040 PIN LAYOUT
 * VCC to 5V
 * GND to GND
 * SCL to A5
 * SDA to A4
 * 
 * SERVO:ROLL RIGHT LAYOUT
 * GND to GND
 * 5V to 5V
 * CONTROL to D5
 * 
 * SERVO:ROLL LEFT LAYOUT
 * GND to GND
 * 5V to 5V
 * CONTROL to D6
 * 
 * SERVO:PITCH LAYOUT
 * GND to GND
 * 5V to 5V
 * CONTROL to D9
 * 
 * SERVO:YAW LAYOUT
 * GND to GND
 * 5V to 5V
 * CONTROL to D3
 * 
 * ESC:PROP
 * VCC to 5V
 * GND to GND
 * CONTROL to D2
 * 
 * GPS MODULE PIN LAYOUT
 * TX to RX
 * RX to TX
 * VCC to 3.3V
 * GND to GND
 * 
 * BMP180 PIN LAYOUT
 * VCC to 5V
 * GND to GND
 * SCL to A5
 * SDA to A4
 * 
 * LED:MODE
 * D3
 * 
 * LED:BATTERY LIFE
 * D4
 * 
 */

//Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <Adafruit_BMP085.h>

//Defined Pins
#define yawPin 3 //Yaw Pin Number
#define rollPinR 5 //RollR Pin Number
#define rollPinL 6 //RollL Pin Number
#define pitchPin 9 //Pitch Pin Number
#define thottlePin 10 //Throttle Pin Number
#define ledMode 3 //LED Mode Pin Number
#define ledBatt 4 //LED Battery Pin Number
#define radioCNS 7 //nRF24L01 CNS Pin
#define radioCE 8 //nRF24L01 CE Pin
const byte address[][6] = {"BE001","00002"}; //Address byte

//Global Variables
int pitchOffset = 95;
int rollOffset = 100;
int yawOffset = 90;
int pitchVal;
int rollRVal;
int rollLVal;
int yawVal;
int thrustVal;

//Object Define
RF24 radio(radioCNS,radioCE); //Radio Object
Servo pitchServo; //Pitch Servo Object
Servo rollRServo; //RollR Servo Object
Servo rollLServo; //RollL Servo Object
Servo yawServo; //Yaw Servo Object
Servo throttleESC; //trottleESC Servo Object
struct Data_received //data received struct
{
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};
Data_received data_received;

//Setup Function
void setup() {
  //Pin Intialization
  pinMode(ledMode,OUTPUT);
  pinMode(ledBatt,OUTPUT);
  
  //Servo Intialization
  pitchServo.attach(pitchPin);
  rollRServo.attach(rollPinR);
  rollLServo.attach(rollRVal);
  yawServo.attach(yawPin);
  throttleESC.attach(thottlePin);
  rollRServo.write(rollOffset);
  rollLServo.write(rollOffset);
  yawServo.write(yawOffset);
  pitchServo.write(pitchOffset);
  
  //Radio Inialization
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  data_received.ch1 = 127;
  data_received.ch2 = 127;
  data_received.ch3 = 127;
  data_received.ch4 = 127;

  //Serial Inialization
  Serial.begin(9600);
  
  delay(5);
}

void loop() {
  while(radio.available())
  {
    delay(5);
    radio.read(&data_received,sizeof(Data_received));
    
    pitchVal = data_received.ch1;
    rollRVal = data_received.ch2;
    yawVal = data_received.ch3;
    thrustVal = data_received.ch4;
    Serial.println(pitchVal);
    pitchVal = map(pitchVal,0,255,pitchOffset-45,pitchOffset+45);
    rollRVal = map(rollRVal,0,255,rollOffset-45,rollOffset+45);
    if((rollRVal-rollOffset)>0){
      rollLVal = rollOffset - (rollRVal-rollOffset);
    }
    yawVal = map(yawVal,0,255,yawOffset-45,yawOffset+45);
    thrustVal = map(thrustVal,127,255,1000,1500); //might change
    pitchServo.write(pitchVal);
    rollRServo.write(rollRVal);
    rollLServo.write(rollLVal);
    yawServo.write(yawVal);
    throttleESC.writeMicroseconds(thrustVal);
  }
}
