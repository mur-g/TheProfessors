#include <Servo.h>

int analogDistRight = 0;      // variable for distance sensor on right side of robot near the front
int analogDistLeft = 0;       // variable for distance sensor on left side of robot near the front
int cones = 0;                // variable for the cone count while loop

Servo right;                  // create servo object to control right servo
Servo left;                   // create servo object to control left servo

void setup() 
{
  right.attach(24);                   // attaches right servo to pin 24
  left.attach(23);                    // attaches left servo to pin 23
  analogDistRight = analogRead(A0)    // attaches right distance sensor to analog pin zero

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
   delay(4000);       // delay four seconds until the full turn is made- change value as needed
}

void turnLeft()
{
  left.write(110);    // a rounded left turn to avoid crashing into the cones- change values as needed
  right.write(60);
  delay(4000);        // delay four seconds until the full turn is made- change value as needed
}

void loop() 
{
  while (cones < 2)                       // runs the code until the robot turns right four times
  {
    forward();
    delay(1500);                          // waits 1.5 seconds for robot to clear cone when looping- change value as needed
    analogDistRight = analogRead(A0);
    if (analogDistRight > 1500)           // once it detects the cone on the right closer than 15 cm
    {
      forward();
      delay(1000);
      if (analogDistRight < 800)          // waits to pass the cone before turning to avoid running into it- change value as needed
      {
        turnRight();
        cones++                           // increases turn count by one                     
      }                                   
    }
    if (analogDistLeft > 1500)            // once it detects the cone on the left closer than 15 cm
    {
      forward();
      delay(1000);
      if (analogDistLeft < 800)           // waits to pass the cone before turning to avoid running into it- change value as needed
      {
        turnLeft();
        cones++                           // increases turn count by one
      }
    }
  }
  stopCar();                              // stay stopped
  delay(10000000000000000000);  
}
