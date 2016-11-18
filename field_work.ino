#include <Servo.h> 

int analogLightRight = 0;   // variable for #5 light sensor
int analogLightLeft = 0;    // variable for #4 light sensor
// black is a low value and white is a high value

int analogDistFRight = 0;   // variable for front right distance sensor
int analogDistFCenter = 0;  // variable for front center distance sensor
// higher values are closer, lower values are farther away

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

 
Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control gate servo

// 0 is full forwards for right and backwards for left
// 180 is full backwards for right and forwards for left


void setup() {
  right.attach(24);   // attaches the right servo on pin 23 to the servo object 
  left.attach(23);    // attaches the left servo on pin 24 to the servo object
  gate.attach(25);
 
  loop();
}

void first() {
  delay(50);          // delay to allow power spike to pass
  left.write(180);    // set left motor to full forward
  right.write(0);     // set right motor to full forward
  delay(500);         // move for .5 sec
}

void fastLineFollowLeft() {
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  if(analogLightRight < analogLightLeft){           // fast LEFT side line follow code
    left.write(150);                                // useful for following straight lines
    right.write(0);                                 
    }                                               
  else{                                             
    left.write(180);                                
    right.write(30);
    }
}

void fastLineFollowRight() {                        // fast RIGHT side line follow code
  analogLightRight = analogRead(A2);                // useful for following straight lines
  analogLightLeft = analogRead(A4);
  if (analogLightLeft < analogLightRight) {
    left.write(180);
    right.write(30);
  }
  else {
    left.write(150);
    right.write(0);
  }
}

void fastLineFollow() {
  if (/*left side of field*/) {               // will capture two middle pokemon at this time
    fastLineFollowLeft(); 
    }
  if (/*right side of field*/) {
    fastLineFollowRight();
    }       
}

void slowLineFollowRight() {
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  if(analogLightRight < analogLightLeft){     // slow LEFT line follow code        
    left.write(100);                          // needed for taking turns to avoid getting off course
    right.write(50);                          // USE LEFT SIDE LINE FOLLOW FOR LEFT FIELD
    }                                         // USE RIGHT SIDE LINE FOLLOW FOR RIGHT FIELD
  else{                                       // WE NEED TO THINK OF HARDWARE SOLUTIONS FOR QUICK CHANGES  
    left.write(140);                          // ASLO NOT SURE IF THIS CODE IN PARTICULAR FOLLOWS LEFT OR RIGHT
    right.write(80);
    }
}

void slowLineFollowLeft() {
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  if(analogLightLeft < analogLightRight){     // slow RIGHT line follow code        
    left.write(140);                          // needed for taking turns to avoid getting off course
    right.write(80);                         
    }                                         
  else{                                         
    left.write(100);                          
    right.write(50);
    }
}

void slowLineFollow() {
  if (/*left side of field*/) {               // will capture two middle pokemon at this time
    slowLineFollowLeft(); 
  }
  if (/*right side of field*/) {
    slowLineFollowRight();
  }       
}

void greatBallLeft() {                        // capturing the great ball for the LEFT side of the field
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  analogDistFRight = analogRead(A0);
  analogDistFCenter = analogRead(A11);
  if(analogDistFRight >= 500) {               // once the robot is 21 cm away from the wall               
    right.write(100);                         // slowly pivot toward the great ball
    left.write(100);                          
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
  delay(1500);   
}

void greatBallRight() {                       // capturing the great ball for the RIGHT side of the field
  analogLightRight = analogRead(A2);
  analogLightLeft = analogRead(A4);
  analogDistFRight = analogRead(A0);
  analogDistFCenter = analogRead(A11);
  if(analogDistFRight >= 500) {               // once the robot is 21 cm away from the wall               
    right.write(80);                         // slowly pivot toward the great ball
    left.write(80);                          
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
  left.write(100);                             // pivot left until on the line again
  delay(1500);   
}

void greatBall() {
  if (/*left side of field*/) {               // will capture two middle pokemon at this time
      greatBallLeft(); 
    }
  if (/*right side of field*/) {
      greatBallRight();
    }       
}

void loop() {

  analogLightRight = analogRead(A2);    // attaches the #5 right light sensor to analog pin 2 
  analogLightLeft = analogRead(A4);     // attaches the #4 left light sensor to analog pin 4
  analogDistFRight = analogRead(A0);    // attaches the front right distance sensor to analog pin 0
  analogDistFCenter = analogRead(A11);  // attaches the front center distance sensor to analog pin 11 

  if (/*first go*/) {
    first();

    do {
      analogDistFCenter = analogRead(A11);
      fastLineFollow();
      } while(analogDistFCenter < 900);             // loop until front distance reads wall is 10cm away

    time1 = millis();                             // take the time
    do {
      time2 = millis();                           // take the time at the start of each loop
      gate.write(0);                              // lower front gate to capture first pokeball
      slowLineFollow();
      } while(time2 - time1 < 2000);              // loop for 2.5 sec

    time3 = millis();                             // take the time
    do {
      time4 = millis();                           // take the time at the start of each loop
      fastLineFollow();                            
      } while(time4 - time3 < 5000);              // follow the line until the robot has passed the junction
  
    gate.write(90);                               // raise front gate
  
    greatBall();                                  // capture the great ball

    right.write(100);
    left.write(100);                            // pivot right until on the line again
    delay(1500);                                // ONLY WORKS FOR LEFT SIDE OF FIELD
  
    time5 = millis();                             // take the time
    do {
      time6 = millis();                           // take the time at the start of each loop
      slowLineFollow();
      } while(time6 - time5 < 2000);              // loop for 2.5 sec until the robot finishes the curve
  
    do {
      analogDistFRight = analogRead(A0);
      fastLineFollow();                             // will capture zaptos at this time
      } while(analogDistFRight < 750);              // loop until front distance reads wall is 40cm away after it captures zaptos
    }

  if (/*reset*/) {
    first();
    
    time7 = millis();                             // take the time
    do {
      time8 = millis();                           // take the time at the start of each loop
      fastLineFollow();
      } while(time8 - time7 < 2000);              // loop for 2.5 sec until the robot passes the junction  
  
    greatBall();                                  // capture another great ball

    time9 = millis();                              // take the time
    do {
      time10 = millis();                            // take the time at the start of each loop
      slowLineFollow();                             // will capture the corner pokemon at this time
      } while(time10 - time9 < 2000);               // loop for 2.5 sec until the robot passes the curve
    
    right.write(90);
    left.write(90);
    delay(1000000000000000000);                     // and we're done unless we decide to do something else  
  }
}
