int analogValueFront = 0;    // variable to hold the analog value
int analogValueBack = 0;
#include <Servo.h> 
 
Servo right;  // create servo object to control right servo 
Servo left;   // create servo object to control left servo



void setup() {
  Serial.begin(9600);     // setup serial
 
  right.attach(19);  // attaches the right servo on pin 23 to the servo object 
  left.attach(23);  // attaches the left servo on pin 24 to the servo object
  
}

void loop() {

  analogValueFront = analogRead(A2);
  analogValueBack = analogRead(A1);

  if(analogValueFront <= analogValueBack){
    left.write(80);
    right.write(180);
    //Serial.println(analogValueFront);
  }else{
    left.write(0);
    right.write(105);
  }
//  if(analogValueBack < analogValueFront){
//    left.write(0);
//    right.write(105);
//    //Serial.println(analogValueBack);
//  }
//  if(analogValueFront < 1000){
//    left.write(180);
//    right.write(30);
//    delay(750);
//  }
    Serial.println(analogValueFront);
    Serial.println(analogValueBack);
    Serial.println("");
    delay(250);
}
