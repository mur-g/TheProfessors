int analogValueLeft = 0;    // variable to hold the analog value of the sensor
int analogValueFront = 0;
#include <Servo.h>

Servo right;                // creates servo object to control the right servo
Servo left;                 // creates servo object to control the left servo


void setup() {
  Serial.begin(9600);       // setup serial

  right.attach(24);         // attaches the right servo on pin 24 to the servo object
  left.attach(23);          // attaches the left servo on pin 23 to the servo object

  delay(1000);
}

void loop() {
  analogValueLeft = analogRead(A4);                               // reads the distance sensor values
  analogValueFront = analogRead(A1);
  
  if(analogValueLeft < 2000) {                                    // if the wall is farther than 15 cm away from the left,
    right.write(0);                                               // turn left
    left.write(100);                                              
    delay(2250);                                                  // delay for 2.25 seconds

    right.write(0);                                               // then go straight
    left.write(150);
    delay(1000);                                                  // delay for one second
  }
  if(analogValueFront > 2700 and analogValueFront < 3000) {  
    right.write(120);                                             // if the wall is around 10 cm away from the front, 
    left.write(180);                                              // turn right
    delay(800);
  }
  else {
    right.write(0);
    left.write(150);
  }
}
