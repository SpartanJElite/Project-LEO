#define RXpin A3             //this is the pin that the Arduino will use to receive data from the GPS
#define TXpin A4              //this is the pin that the Arduino can use to send data (commands) to the GPS - not used


#include <SoftwareSerial.h>
SoftwareSerial GPS(RXpin, TXpin);

void loop()
{
  while (GPS.available())
  {
    Serial.write(GPS.read());
  }
}

void setup()
{
  GPS.begin(9600);
  Serial.begin(115200);
  Serial.println("GPS_Echo Starting");
}
