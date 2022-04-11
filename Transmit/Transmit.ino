/* TRANSMITTER FOR LEO
 * 
 * PIN LAYOUT FOR nRF24L01
 * LEFT TO RIGHT TO DOWN (GND, VCC, CE, CNS, SCK, MOSI, MISO, IRQ)
 * GND to GND
 * VCC to 3.3V
 * CE to 10
 * CNS to 9
 * SCK to 13
 * MOSI to 11
 * MISO to 12
 * 
 * PIN LAYOUT FOR ANALOG STICK 1
 * LEFT TO RIGHT (GND, +5V, VRX, VRY, SW)
 * GND to GND
 * +5V to 5V
 * VRX to A0
 * VRY to A1
 * SW to D4
 * 
 * PIN LAYOUT FOR ANALOG STICK 2
 * LEFT TO RIGHT (GND, +5V, VRX, VRY, SW)
 * GND to GND
 * +5V to 5V
 * VRX to A2
 * VRY to A3
 * SW to D7
 * 
 * Button1 LAYOUT 
 * D0
 * 
 * Button2 LAYOUT
 * D1
 * 
 * LED:MODE
 * D2
 * 
 * LED:BATTERY LIFE
 * D3
 * 
 */

//Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Defined Pins
#define joy1X A2 //joystick left x-axis(Controls Thrust) Pin
#define joy1Y A3 //joystick left y-axis(Controls Roll) Pin
#define joy1S 4 //joystick left switch Pin
#define joy2X A0 //joystick right x-axis(Controls Pitch) Pin
#define joy2Y A1 //joystick right y-axis(Controls Yaw) Pin
#define joy2S 7 //joystick right switch Pin
#define button1 2 //button for Mode 1 Pin
#define button2 3 //button for Mode 2 Pin
#define ledMode 0 //LED for MODE Pin
#define ledBatt 1 //LED for Battery Pin
#define radioCNS 9 //nRF24L01 CNS Pin
#define radioCE 10 //nRF24L01 CE Pin
const byte address[][6] = {"BE001","00002"};

//Global Variables
int pitchVal;
int rollVal;
int yawVal;
int thrustVal;

//Object Setup
RF24 radio(radioCNS,radioCE); //setup radio object
struct Data_sent //struct of data to send over to reciever
{
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};
Data_sent data_collection; //setup for data struct

//Setup Function
void setup() {
  //Pin Intialization
  pinMode(joy1S,INPUT);
  pinMode(joy2S,INPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(ledMode,OUTPUT);
  pinMode(ledBatt,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button1),modeChange,FALLING);
  
  //Radio Intialization
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  data_collection.ch1 = 127;
  data_collection.ch2 = 127;
  data_collection.ch3 = 127;
  data_collection.ch4 = 127;

  //Serial Moniter Intialization
  Serial.begin(9600);
  
  delay(5);
}

void loop() {
  yawVal = map(analogRead(joy2Y),0,1024,0,255);
  pitchVal = map(analogRead(joy2X),0,1024,0,255);
  thrustVal = map(analogRead(joy1X),0,1024,0,255);
  rollVal = map(analogRead(joy1Y),0,1024,0,255);
  data_collection.ch1 = pitchVal;
  data_collection.ch2 = rollVal;
  data_collection.ch3 = yawVal;
  data_collection.ch4 = thrustVal;
  radio.write(&data_collection,sizeof(Data_sent));
  Serial.println(pitchVal);
}

void modeChange(){
  
}
