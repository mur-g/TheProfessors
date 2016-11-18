#include <Servo.h> 

//main program 2

int analogLightRight = 0;   // variable for #5 light sensor
int analogLightLeft = 0;    // variable for #4 light sensor
int analogDistFront = 0;    // variable for front distance sensor
int analogDistLeft = 0;     // variable for right distance sensor
int analogDistRight = 0;    // variable for left distance sensor
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
  gate.attach(25);
  analogLightRight = analogRead(A2);    // attaches the #5 light sensor to analogread pin 28 
  analogLightLeft = analogRead(A4);     // attaches the #4 light sensor to analogread pin 27
  analogDistFront = analogRead(A11);     // attaches the front distance sensor to analogread pin 26
  analogDistRight = analogRead(A9);     // attaches the right distance sensor to analogread pin ??
  analogDistLeft = analogRead(A8);      // attaches the left distance sensor to analogread pin ??
  gate.write(90);                       //lift gate up

  mainProgram();
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

void lineFollow()
{
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);

  if(analogLightRight < analogLightLeft)           // turn right
  {
      left.write(150);                            
      right.write(0);
            
  }
  if (analogLightLeft < analogLightRight)          // turn left
  {
      left.write(180);
      right.write(30);
  }
}

boolean dropGate()
{
  boolean isDropped = false;
  analogDistFront = analogRead(A11);
  if (analogDistFront > 900)           // update value
  {
    gate.write(0);
    isDropped = true;
  }
  return isDropped;
}

void firstPokemon()
{
  stopCar();
  for (int i = 1000; i > 0; i--)      // wait 1 second for turn
  {
    left.write(180);
    right.write(90);
  }
  stopCar();

  for (int i = 4000; i > 0; i--)      // wait 4 seconds
    stopCar();
  // write code to lift game, push pokeball
  gate.write(90);
  
  for (int i = 1000; i > 0; i--)      // wait 1 second for turn back
  {
    left.write(0);
    right.write(90);
  }
  
}

void mainProgram()
{
  boolean dropped = false;
  do
  {
    forward();
    lineFollow();
    dropped = dropGate();
  } while(!dropped);

  do                                      // line follow until first pokemon is reached
  {
    forward();
    lineFollow();
    analogDistRight = analogRead(A9);     // check if reached first pokemon
    if (analogDistRight > 400)            // *******update this value********
      firstPokemon();                     // if reached, catch first pokemon
  } while(analogDistRight < 400);         // *******update this value********
  
  stopCar();
}

void loop() {}
