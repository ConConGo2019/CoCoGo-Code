//Same code as fix.io, just cleaner (i.e., less messy comments)
//adapted from example code in the Adafruit GPS Library
bool initial = true;
bool first = true;
bool second = true;
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 3
// Connect the GPS RX (receive) pin to Digital 2

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

void setup()
{

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  delay(5000);


  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);


  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate

  // Request updates on antenna status
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

}

uint32_t timer = millis();
void loop()                     // run over and over again
{
 
  char c = GPS.read();
  if ((c) && (GPSECHO))
   // Serial.write(c);

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    if (GPS.fix) {
      //Serial.println(GPS.latitude);
      if (GPS.latitude >4122.65 && initial == true){ //start somewhere in front of Fanning
        Serial.println("Start"); //The Python code for the Pi will look for this word to know when to play the first video
        initial = false; //set this to make sure that the video only plays once
      }
      else if (GPS.latitude < 4122.68 && second == true){ //a little before Bill Hall
        Serial.println("Bill");
        second = false;
      }
    }
  }
}
