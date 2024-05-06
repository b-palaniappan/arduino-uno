#define RXpin A3              //this is the pin that the Arduino will use to receive data from the GPS
#define TXpin A2              //this is the pin that the Arduino can use to send data (commands) to the GPS - not used

#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

SoftwareSerial mySerial(RXpin, TXpin);
Adafruit_GPS GPS(&mySerial);

void setup()
{
  GPS.begin(9600);
  Serial.begin(115200);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
}

void loop() {
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }
    
    Serial.println("-------");
    Serial.print("Time: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    
    Serial.print("Location: ");
    Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
    Serial.print(", ");
    Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
    
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
  }
}
