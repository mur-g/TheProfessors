#include <Servo.h>

Servo right;               // create servo object to control right servo
Servo left;                // create servo object to control left servo
                           // a maximum of eight servos can be controlled
                

int analogValueFront = 0;   // variable to hold the analog value of the front sensor
int analogValueBack = 0;    // variable to hold the analog value of the back sensor

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


void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  analogValueFront = analogRead(A2);    // read the analog input of the front sensor on analog pin 3
  analogValueBack = analogRead(A1);     // read the analog input of the back sensor on analog pin 4
  
  Serial.println(analogValueFront);       // print as an ASCII-encoded decimal
  Serial.println(analogValueBack);        // print as an ASCII-encoded decimal

  if(analogValueFront < analogValueBack) {                  // if back sensor has a larger reading than the front sensor,
    right.write(90*analogValueFront/analogValueBack);    // adjust the right right wheel to compensate and make sensor values equal
    left.write(180);
  }
  else if (analogValueFront > analogValueBack) {            // if front sensor has a larger reading than the back sensor,                                       
    right.write(0);                                         // adjust the left wheel to compensate and make sensor values equal
    left.write(90*analogValueBack/analogValueFront);
  }
  else {                                                    // if back and front sensors have equal readings,
    right.write(0);                                         // continue going straight
    left.write(180);
  }
}
