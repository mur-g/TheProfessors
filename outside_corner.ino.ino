int analogValueLeft = 0;    // variable to hold the analog value of the sensor
                            // on the right side of the robot
#include <Servo.h>

Servo right;                // creates servo object to control the right servo
Servo left;                 // creates servo object to control the left servo


void setup() {
  Serial.begin(9600);       // setup serial

  right.attach(24);         // attaches the right servo on pin 24 to the servo object
  left.attach(23);          // attaches the left servo on pin 23 to the servo object
  
}

void loop() {
  analogValueLeft = analogRead(A4);   // reads the distance sensor value
  
  if(analogValueLeft < 2000) {        // if the sensor doesn't see the wall,
    right.write(0);                   // right wheel continues speed
    left.write(100);                  // left wheel slows down
  }
  else {                              // otherwise, continue going straight
    right.write(0);
    left.write(140);
  }
  
}
