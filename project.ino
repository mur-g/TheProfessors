#include <Servo.h>

// Globals
unsigned long sysTime;  // system time
// Note: writing 0 to right motor moves it forward and
//       writing 0 to left motor moves it backwards
//       writing 180 to right motor moves it backwards
//       writing 180 to left motor moves it forward
//       writing 90 to either motor does not move it at all
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control front gate
int ls4;        // light sensor 4; connected to pin A2
int ls5;        // light sensor 5; connected to pin A4
int dsf;        // distance sensor (front); connected to pin A0
bool b = true;

void setup() {
  // put your setup code here, to run once:
  right.attach(24);   // attaches the right servo to pin 24 
  left.attach(23);    // attaches the left servo to pin 23
  //gate.attach(25);    // attaches the front gate to pin 25
  //lineFollow();
}

/*
  Drops the back gate at the
  beginning
*/
void dropBackGate(){
  
}

/*
  Walks forward for half a second
  to begin line follow. Robot goes
  outside the start position (the
  square).
*/
void first(){
  left.write(180);    // moves left motor forward
  right.write(0);     // moves right motor forward
  delay(500);         // moves for .5 sec
  left.write(90);
  right.write(90);
}

/*
  Line follows
*/
void lineFollow(){
  do{
  
  sysTime = millis();     // sets the system time
  ls4 = analogRead(A2);   // read value from light sensor 4
  ls5 = analogRead(A4);   // read value from light sensor 5
  dsf = analogRead(A0);   // read value from distance sensor (right)
  if(ls4 < ls5){
            left.write(150);
            right.write(0);
            
  }else{
    left.write(180);
    right.write(30);
  }

  }while(dsf < 900);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  if(b){
    delay(50);          // allows power spike to pass
    first();            // robot leaves the square
    b = false;
  }else{
    left.write(90);
    right.write(90);
  }
}
