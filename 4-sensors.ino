//Adapted from code I found here: 
//https://www.instructables.com/id/Arduino-Wondering-Robot/

#include <Servo.h>       
  
//  You need to include Servo.h as it is used by the HB-25 Library

#include <HB25MotorControl.h>

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

  Serial.begin( 9600 );
  motorControl.begin();
  motorControl2.begin();

}

void loop() {
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
//  if (distance2>50) { //we took out the going backwards feature
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

 else{
  //Serial.println("Object detected");
  
 }

 

// if (distance<5) {
//  Serial.println("Turning");
//   motorControl.moveAtSpeed(200);
//   motorControl2.moveAtSpeed(300);
// }
// else if (distance>50){
//  motorControl.moveAtSpeed(200);
//  motorControl2.moveAtSpeed(200);
//
//
// }
//
//  else{
//    motorControl.moveAtSpeed(-200);
//    motorControl2.moveAtSpeed(-200);
//   
//  }
    
  
//long microsecondsToInches(long microseconds) {
//  // According to Parallax's datasheet for the PING))), there are 73.746
//  // microseconds per inch (i.e. sound travels at 1130 feet per second).
//  // This gives the distance travelled by the ping, outbound and return,
//  // so we divide by 2 to get the distance of the obstacle.
//  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
//  return microseconds / 74 / 2;
//}
//
//long microsecondsToCentimeters(long microseconds) {
//  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
//  // The ping travels out and back, so to find the distance of the object we
//  // take half of the distance travelled.
//  return microseconds / 29 / 2;
//}

    
 
  

  
}
