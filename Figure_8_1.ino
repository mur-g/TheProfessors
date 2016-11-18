#include <Servo.h> 

// Figure 8 program
// Navigates two cones in clockwise figure 8 pattern

int analogDistFrontRight = 0;    // variable for front distance sensor
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
  analogDistFrontRight = analogRead(A11);     // attaches the front distance sensor to analogread pin 26
  analogDistRight = analogRead(A9);     // attaches the left distance sensor to analogread pin 6
  gate.write(90);                       // lift gate up

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

void turnLeft()
{
  for (int i = 1200; i > 0; i--)
   {
     left.write(90);    // set right motor to full forward
     right.write(0);    // stop left motor
   }
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

  do                                      // go forward until reached next cone
  {
    forward();
    analogDistFrontRight = analogRead(A11);
    if (analogDistFrontRight > 400)            // <------update this value
      turnLeft();                         // turn left if cone reached
  } while(analogDistFrontRight < 400);         // <------update this value

  for (int i = 4; i > 0; i--)             // turn right 4 times around cone
  {
    do                                      // go forward until past cone, then turn right
    {
      forward();
      analogDistRight = analogRead(A9);
    } while(analogDistRight > 200);         // <------update this value

    for (int i = 400; i > 0; i--)           // go forward a LITTLE more
      forward();

    turnRight();                            // finally turn right
  }

  for (int i = 200; i > 0; i--)             // go forward VERY LITTLE more
      forward();

  turnLeft();                               // turn left to other cone and repeat
  
}
