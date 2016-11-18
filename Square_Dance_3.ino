#include <Servo.h> 

// Square Dance program 3
// Navigates outside of cones instead of inside
// Clockwise square

int analogDistRight = 0;    // variable for right distance sensor
unsigned long time1 = 0;    // variables for several timers
unsigned long time2 = 0;

// Note: writing 0 to right motor moves it forward and
//       writing 0 to left motor moves it backwards
//       writing 180 to right motor moves it backwards
//       writing 180 to left motor moves it forward
//       writing 90 to either motor does not move it at all
 
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control left servo

void setup()
{
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  gate.attach(25);    // attaches the gate servo on pin 25 to the servo object
  analogDistRight = analogRead(A9);     // attaches the left distance sensor to analogread pin 6
  gate.write(90);                       // lift gate up

  for (int i = 1000; i > 0; i--)           // go forward a little to start
    forward();

  loop();
}

void forward()
{
  left.write(180);    // set left motor to full forward
  right.write(0);     // set right motor to full forward
}

void stopCar()
{
  left.write(90);     // stop left motor
  right.write(90);    // stop right motor
}

void turnRight()
{
  for (int i = 1200; i > 0; i--)
   {
     left.write(180);    // set left motor to full forward
     right.write(90);    // stop right motor
   }
}

void loop()
{
  
  do                                      // go forward until reach next cone
  {
    forward();
    analogDistRight = analogRead(A9);
  } while(analogDistRight < 400);         // <------update this value
  
  do                                      // go forward until past cone, then turn right
  {
    forward();
    analogDistRight = analogRead(A9);
  } while(analogDistRight > 200);          // <------update this value

  for (int i = 200; i > 0; i--)           // go forward a LITTLE more
    forward();

  turnRight();                             // finally turn right

  do                                       // go forward until past cone, then repeat to next cone
  {
    forward();
    analogDistRight = analogRead(A9);
  } while(analogDistRight > 200);          // <------update this value

  
}
