#include <Servo.h>

Servo right;               // create servo object to control right servo
Servo left;                // create servo object to control left servo
                           // a maximum of eight servos can be controlled
                
int pos = 0;               // variable to store the servo position

void setup() {
  right.attach(23);        // attaches the right servo on pin 23 to the servo object
  left.attach(24);        // attaches the left servo on pin 24 to the servo object
}

void loop() { 
   right.write(180);      // right servo go to 180 degrees
   left.write(0);         // left servo go to 0 degrees
   delay(1000);           // wait 1000ms for the servos to reach these positions
   right.write(0);        // right servo go to 0 degrees
   left.write(180);       // left servo go to 180 degrees
   delay(1000);           // wait 1000ms for the servos to reach these positions
}
