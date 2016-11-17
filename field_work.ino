#include <Servo.h> 

int analogLightRight = 0;   // variable for #5 light sensor
int analogLightLeft = 0;    // variable for #4 light sensor
int analogDistFRight = 0;   // variable for front right distance sensor
int analogDistFCenter = 0;  // variable for front center distance sensor
unsigned long time1 = 0;    // variables for several timers
unsigned long time2 = 0;
unsigned long time3 = 0;
unsigned long time4 = 0;
unsigned long time5 = 0;
unsigned long time6 = 0;
unsigned long time7 = 0;
unsigned long time8 = 0;
unsigned long time9 = 0;
unsigned long time10 = 0;
unsigned long time11 = 0;
unsigned long time12 = 0;
unsigned long time13 = 0;
unsigned long time14 = 0;
unsigned long time15 = 0;

 
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control gate servo

// 0 is forwards for right and backwards for left
// 180 is backwards for right and forwards for left


void setup() {
 
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  gate.attach(25);
}

void loop() {

  analogLightRight = analogRead(A2);    // attaches the #5 right light sensor to analog pin 2 
  analogLightLeft = analogRead(A4);     // attaches the #4 left light sensor to analog pin 4
  analogDistFRight = analogRead(A0);    // attaches the front right distance sensor to analog pin 0
  analogDistRCenter = analogRead(A11);  // attaches the front center distance sensor to analog pin 11 

  delay(50);          // delay to allow power spike to pass
  left.write(180);    // set left motor to full forward
  right.write(0);     // set right motor to full forward
  delay(500);         //move for .5 sec

  time1 = millis();                                   // take the time     
  do {
    time2 = millis();                                 // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    analogDistFRight = analogRead(A0);
    if(analogLightRight < analogLightLeft){           // fast line follow code
      left.write(150);
      right.write(0);
      }
    else{
      left.write(180);
      right.write(30);
      }
    } while(analogDistFRight < 900);             // loop until front distance reads wall is 10cm away

  time3 = millis();                             // take the time
  do {
    time4 = millis();                           // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    gate.write(0);                              // lower front gate to capture first pokeball
    if(analogLightRight < analogLightLeft){     // slow line follow code        
      left.write(100);
      right.write(50);
      }
    else{
      left.write(140);
      right.write(80);
      }
    } while(time4 - time3 < 2000);              // loop for 2.5 sec

  time5 = millis();                             // take the time
  do {
    time6 = millis();                           // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    if(analogLightRight < analogLightLeft){     // fast line follow code        
      left.write(150);                          // will capture two middle-field pokemon at this time
      right.write(0);
      }
    else{
      left.write(180);
      right.write(30);
      }
    } while(time6 - time5 < 5000);    // follow the line until the robot has passed the junction
  
  gate.write(90);                               // raise front gate
  time7 = millis();                             // take the time                              
  
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  analogDistFRight = analogRead(A0);
  analogDistFCenter = analogRead(A11);
  if(analogDistFRight >= 500) {               // once the robot is 21 cm away from the wall               
    right.write(100);                         // slowly pivot toward the great ball
    left.write(100);                          // can work for both sides of the field but is more time efficient for left side
    if(analogDistFCenter > 1500) {            // when it senses the great ball closer than 15 cm
      right.write(40);                        // move forward slowly for one second
      left.write(120);
      gate.write(0);                          // lower front gate
      delay(500);
      right.write(120);                       // slowly back up for one second
      left.write(40);
      delay(500);
    }
  }
  right.write(100);
  left.write(100);                            // pivot right until on the line again
  delay(1500);                                // ONLY WORKS FOR LEFT SIDE OF FIELD

  time8 = millis();                             // take the time
  do {
    time9 = millis();                           // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    if(analogLightRight < analogLightLeft){     // slow line follow code        
      left.write(100);
      right.write(50);
      }
    else{
      left.write(140);
      right.write(80);
      }
    } while(time9 - time8 < 2000);              // loop for 2.5 sec until the robot finishes the curve
  
  time10 = millis();                                   // take the time     
  do {
    time11 = millis();                                 // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    analogDistFRight = analogRead(A0);
    if(analogLightRight < analogLightLeft){            // fast line follow code
      left.write(150);
      right.write(0);
      }
    else{
      left.write(180);
      right.write(30);
      }
    } while(analogDistFRight < 750);              // loop until front distance reads wall is 40cm away after it captures zaptos

  right.write(90);                              // stop and raise the gate
  left.write(90);
  gate.write(90);
  right.write(120);                             // pivot to the right for 1.5 seconds
  left.write(120);
  delay(1500);
  
  time12 = millis();                                   // take the time     
  do {
    time13 = millis();                                 // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    analogDistFRight = analogRead(A0);
    if(analogLightRight < analogLightLeft){           // fast line follow code
      left.write(150);
      right.write(0);
      }
    else{
      left.write(180);
      right.write(30);
      }
    } while(analogDistFRight < 900);              // loop until front distance reads wall is 10cm away
  
  time14 = millis();                              // take the time
  do {
    time15 = millis();                            // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    if(analogLightRight < analogLightLeft){       // slow line follow code        
      left.write(100);
      right.write(50);
      }
    else{
      left.write(140);
      right.write(80);
      }
    } while(time15 - time14 < 2000);              // loop for 2.5 sec until the robot passes the junction  
  
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  analogDistFRight = analogRead(A0);
  analogDistFCenter = analogRead(A11);
  if(analogDistFRight >= 500) {               // once the robot is 21 cm away from the wall               
    right.write(100);                         // slowly pivot toward the great ball
    left.write(100);                          // can work for both sides of the field but is more time efficient for left side
    if(analogDistFCenter > 1500) {            // when it senses the great ball closer than 15 cm
      right.write(40);                        // move forward slowly for one second
      left.write(120);
      gate.write(0);                          // lower front gate
      delay(500);
      right.write(120);                       // slowly back up for one second
      left.write(40);
      delay(500);
    }
  }
  right.write(80);
  left.write(80);                             // pivot left until on the line again
  delay(1500);                                // ONLY WORKS FOR LEFT SIDE OF FIELD

  time14 = millis();                              // take the time
  do {
    time15 = millis();                            // take the time at the start of each loop
    analogLightRight = analogRead(A2);
    analogLightLeft = analogRead(A4);
    if(analogLightRight < analogLightLeft){       // slow line follow code        
      left.write(100);                            // will capture the corner pokemon at this time
      right.write(50);
      }
    else{
      left.write(140);
      right.write(80);
      }
    } while(time15 - time14 < 2000);              // loop for 2.5 sec until the robot passes the curve
  right.write(90);
  left.write(90);
  delay(1000000000000000000);                     // and we're done unless we decide to do something else  
}
