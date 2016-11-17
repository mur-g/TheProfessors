#include <Servo.h> 

// Square Dance program 2
// Same as 1 but replaces delay with for loop
// Clockwise square

int analogLightRight = 0;   // variable for #5 light sensor
int analogLightLeft = 0;    // variable for #4 light sensor
int analogDistFront = 0;    // variable for front distance sensor
//int analogDistRight = 0;
int analogDistLeft = 0;
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

void setup() {
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  gate.attach(25);
  analogLightRight = analogRead(A2);    // attaches the #5 light sensor to analogread pin 28 
  analogLightLeft = analogRead(A4);     // attaches the #4 light sensor to analogread pin 27
  analogDistFront = analogRead(A0);     // attaches the front distance sensor to analogread pin 26
  //analogDistRight = analogRead(A?);   // attaches the right distance 
  //analogDistLeft = analogRead(A?);    // attaches the left distance sensor to analogread pin ??
  gate.write(90);     //lift gate up

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
  for (int i = 800; i > 0; i--)
   {
     left.write(180);    // set left motor to full forward
     right.write(90);    // stop right motor
   }
}

void loop()
{
/*  
   do                                     // cones 1 and 3, right distance sensor
  {
    forward();
    analogDistFront = analogRead(A?);
    if (analogDistFront < 400)
    {
      turnRight();
      break;
    }
  } while(analogDistFront > 400);
  
  do                                      // cones 2 and 4, left distance sensor
  {
    forward();
    analogDistLeft = analogRead(A?);
    if (analogDistLeft < 200)
    {
      turnRight();
      break;
    }
  } while(analogDistLeft > 200);
*/  
}
