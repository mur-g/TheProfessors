#include <Servo.h> 

// Square Dance program 1
// Clockwise square

int analogDistRight = 0;    // variable for distance sensor on right side of the robot near the front
int cones = 0;              // variable for the for loop

// Note: writing 0 to right motor moves it forward and
//       writing 0 to left motor moves it backwards
//       writing 180 to right motor moves it backwards
//       writing 180 to left motor moves it forward
//       writing 90 to either motor does not move it at all
 
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo

void setup() {
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  analogDistRight = analogRead(A0);     // attaches the front distance sensor to analog pin 0

  loop();
  }

void forward()
{
  left.write(130);      // moves forward in a straight line
  right.write(30);      // not full forward to allow for reaction time with distance sensor
}

void stopCar()
{
  left.write(90);     // stop left motor
  right.write(90);    // stop right motor
}

void turnRight()
{
   left.write(130);   // a rounded right turn to avoid crashing into the cones- change values as needed
   right.write(80);    
   delay(2000);       // delay two seconds until the full turn is made- change value as needed
}

void loop()
{
  while (cones < 4)                       // runs the code until the robot turns right four times
  {
    forward();
    delay(1500);                          // waits 1.5 seconds for robot to clear cone when looping- change value as needed
    analogDistRight = analogRead(A0);
    if (analogDistRight > 1500)           // once it detects the cone closer than 15 cm
    {
      forward();
      delay(1500);
      if (analogDistRight < 800)          // waits to pass the cone before turning to avoid running into it- change value as needed
      {
        turnRight();
        cones++                           // increases turn count by one                     
      }                                   
    }
  }
  stopCar();                              // stay stopped
  delay(10000000000000000000);
}  
