//Adapted from code I found here: 
//https://www.instructables.com/id/Arduino-Wondering-Robot/

#include <Servo.h>       
  
//  You need to include Servo.h as it is used by the HB-25 Library
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <HB25MotorControl.h>

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean);

bool first = true;
const byte controlPin = 5;              //  Pin for left front wheel
const byte controlPin2 = 9;             // Pin for right front wheel
String readString;
String myString;
HB25MotorControl motorControl(controlPin);  //left front wheel
HB25MotorControl motorControl2(controlPin2);  //right front wheel
const int pingPin = 7;  //front
const int pingPin2 = 8;  //back 
const int pingPin3 = 4;   //left side
const int pingPin4 = 12;  //rigth side

void setup() {

  Serial.begin( 115200 );
  motorControl.begin();
  motorControl2.begin();
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}


uint32_t timer = millis();

void loop() {

  GPSgo();
  MotorGo();
}


void GPSgo(){
  if (! usingInterrupt) {
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  }
  if (GPS.newNMEAreceived()) {

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  if (timer > millis())  timer = millis();
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer

    if (GPS.fix) {
     //Serial.println("Hello");
      Serial.println(GPS.latitude);
      if (GPS.latitude < 4122.70 && first == true){
        Serial.println("Fanning");
        first = false;
      }

    }
    
  }
  
}



void MotorGo() {
    int duration, distance;
  int duration2, distance2;
  int duration3, distance3;
  int duration4, distance4;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  distance = (duration / 2) / 29.1;   //front middle
  //Serial.print(distance);
  //Serial.println(" cm");
  delay(0);
  
  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);
  pinMode(pingPin2, INPUT);
  duration2 = pulseIn(pingPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;
  //Serial.print(distance2);
  //Serial.println(" cm");
  delay(0);


  pinMode(pingPin3, OUTPUT);
  digitalWrite(pingPin3, LOW);
  delayMicroseconds(3);
  digitalWrite(pingPin3, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin3, LOW);
  pinMode(pingPin3, INPUT);
  duration3 = pulseIn(pingPin3, HIGH);  //front left side
  distance3 = (duration3 / 2) / 29.1;
  //Serial.print(distance3);
  //Serial.println(" cm");
  delay(0);


  pinMode(pingPin4, OUTPUT);
  digitalWrite(pingPin4, LOW);
  delayMicroseconds(3);
  digitalWrite(pingPin4, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin4, LOW);
  pinMode(pingPin4, INPUT);
  duration4 = pulseIn(pingPin4, HIGH);   //front right side
  distance4 = (duration4 / 2) / 29.1;
  //Serial.print(distance4);
  //Serial.println(" cm");
  delay(0);

  float leftside = 1;
  float rightside = 1;




  if(distance3 <50 && distance4 <50){
    leftside = 0;
    rightside = 0;
  }
  else if (distance3<50){
    leftside = 1.4;   //apply to left wheel
    //Serial.print("left side: ");
  }
  
  else if(distance4<50){
    rightside = 1.4;    //apply to right wheel
  }

  //Serial.print(leftside);

  if (distance>50) {
  //  Serial.println("Going forward :)");
    
    motorControl.moveAtSpeed(200 * leftside);   //we can get rid of the negative signs if we switch the wires that are connected to the motor controller 
    motorControl2.moveAtSpeed(226 * rightside);
    delay(100);
    
 }
 else if (distance<50) {
//  if (distance2>50) {
//    motorControl.moveAtSpeed(-180);
//    motorControl2.moveAtSpeed(-200);
//    delay(50);
//  }
//  else{
    motorControl.moveAtSpeed(0);
    motorControl2.moveAtSpeed(0);
    delay(50);
//  }

 }

}
