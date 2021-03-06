#include <Servo.h> 

int analogLightRight = 0;   // variable for #5 light sensor
int analogLightLeft = 0;    // variable for #4 light sensor
int analogDistFront = 0;    // variable for front distance sensor
unsigned long time1 = 0;    // variables for several timers
unsigned long time2 = 0;
unsigned long time3 = 0;
unsigned long time4 = 0;
unsigned long time5 = 0;
unsigned long time6 = 0;

 
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control left servo

// 0 is forwards for right and backwards for left
// 180 is backwards for right and forwards for left


void setup() {
 
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  gate.attach(25);
}

/**/
void dropGate(){
  
}

/*
  Walks forward for half a second
  to begin line follow
*/
void start(){
  
}

void loop() {

  analogLightRight = analogRead(A2);    // attaches the #5 light sensor to analogread pin 28 
  analogLightLeft = analogRead(A4);     // attaches the #4 light sensor to analogread pin 27
  analogDistFront = analogRead(A0);     // attaches the front distance sensor to analogread pin 26

//    switch (1) {
      
//      case 1:
        delay(50);          // delay to allow power spike to pass
        left.write(180);    // set left motor to full forward
        right.write(0);     // set right motor to full forward
        delay(500);         //move for .5 sec

//      case 2:
        time1 = millis();                                   // take the time when case 2 starts
       
        do
        {
          time2 = millis();                                 // take the time at the start of each loop
          analogLightRight = analogRead(A2);
          analogLightLeft = analogRead(A4);
          analogDistFront = analogRead(A0);
//          if(time2 - time1 < 500 and time2 - time1 > 250){    // between .75 sec and 1 sec after case 2 begins lower the front gate
//            gate.write(0);
//            
//          }
          if(analogLightRight < analogLightLeft){           // fast line follow code
            left.write(150);
            right.write(0);
            
          }else{
              left.write(180);
              right.write(30);
          }
        } while(analogDistFront < 900);                    // loop until front distance reads wall is 10cm away

//      case 3:
        time3 = millis();                             // take the time when case 3 starts
        do
        {
          time4 = millis();                           // take the time at the start of each loop
          analogLightRight = analogRead(A2);
          analogLightLeft = analogRead(A4);
          gate.write(0);
          if(analogLightRight < analogLightLeft){     // slow line follow code
            
            left.write(100);
            right.write(50);
            
          }else{
              left.write(140);
              right.write(80);
          }
        } while(time4 - time3 < 2000);                // loop for 2.5 sec after case 3 starts
        
//      case 4:
        time5 = millis();                             // take the time when case 4 starts
        do
        {
          time6 = millis();                           // take the time at the start of each loop
          analogLightRight = analogRead(A2);
          analogLightLeft = analogRead(A4);
          if(analogLightRight < analogLightLeft){     // fast line follow code
            
            left.write(150);
            right.write(0);
            
          }else{
              left.write(180);
              right.write(30);
          }
        } while(time6 - time5 < 10000000000000);      // follow the line for a long time
//  }
}
