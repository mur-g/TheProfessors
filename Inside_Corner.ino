#include <Servo.h> 

int analogValueRight = 0;    // variable to hold the analog value

 
Servo right;  // create servo object to control right servo 
Servo left;   // create servo object to control left servo



void setup() {
 
  right.attach(24);  // attaches the right servo on pin 23 to the servo object 
  left.attach(23);  // attaches the left servo on pin 24 to the servo object
  
}

void loop() {

  analogValueRight = analogRead(A1);

  if(analogValueRight > 2700){
    left.write(180);
    right.write(120);
    delay(750);
   // Serial.println(analogValueFront);
  }else{
    left.write(140);
    right.write(0);
    //Serial.println(analogValueBack);
  }

//  if(analogValueRight > 3000, analogValueLeft > 3000){
//    left.write(90);
//    right.write(160);
//    delay(1500);
//  }
}
