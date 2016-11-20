#include <Servo.h> 

int SWITCH1 = 0;            // variable for switch determining left vs. right field
int SWITCH2 = 0;            // variable for switch determining first round vs. reset

int analogLightCenter = 0;  // variable for #4 light sensor
int analogLightRight = 0;   // variable for #3 light sensor
int analogLightLeft = 0;    // variable for #5 light sensor
// black is a high value and white is a low value

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

Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control gate servo

// 0 is full forwards for right and backwards for left
// 180 is full backwards for right and forwards for left


void setup() {
  Serial.begin(9600);
  pinMode(SWITCH1, INPUT);      // sets switch pins to input mode
  pinMode(SWITCH2, INPUT);
  
  right.attach(24);             // attaches the right servo on pin 23 to the servo object 
  left.attach(23);              // attaches the left servo on pin 24 to the servo object
  gate.attach(25);              // attaches the gate servo on pin 25 to the servo object
 
  loop();
}

void first() {
  delay(100);           // delay to allow power spike to pass
  left.write(130);      // set left motor to forward
  right.write(30);      // set right motor to forward
  delay(500);           // move for .5 sec
}

void lineFollowLeft() {                         // LEFT side line follow code
  analogLightCenter = analogRead(A0);               
  analogLightRight = analogRead(A1);                
  analogLightLeft = analogRead(A2);                 
  if(analogLightCenter > 4000 and analogLightRight < 4000 and analogLightLeft < 4000) {         // if the middle is black and the outside is white
    right.write(30);                                                                            // go straight
    left.write(130);
  }
  if(analogLightCenter < 4000 and analogLightRight > 4000 and analogLightLeft > 4000) {         // if the middle is white and the outside is black
    right.write(20);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 4000 and analogLightRight > 4000 and analogLightLeft < 4000) {         // if left is white and others are black
    right.write(30);                                                                            // go straight
    left.write(130);
  }
  if(analogLightCenter > 4000 and analogLightRight < 4000 and analogLightLeft > 4000) {         // if right is white and others are black
    right.write(20);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter < 4000 and analogLightRight > 4000 and analogLightLeft < 4000) {         // if right is black and others are white
    right.write(80);                                                                            // turn right
    left.write(150);
  }
  if(analogLightCenter < 4000 and analogLightRight < 4000 and analogLightLeft > 4000) {         // if left is black and others are white
    right.write(20);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 4000 and analogLightRight > 4000 and analogLightLeft > 4000) {         // if all are black
    right.write(20);                                                                            // turn left
    left.write(100);
  }
}

void lineFollowRight() {                        // RIGHT side line follow code                       
  analogLightCenter = analogRead(A0);               
  analogLightRight = analogRead(A1);               
  analogLightLeft = analogRead(A2);                 
  if(analogLightCenter > 4000 and analogLightRight < 4000 and analogLightLeft < 4000) {         // if the middle is black and the outside is white
    right.write(30);                                                                            // go straight
    left.write(130);
  }
  if(analogLightCenter < 4000 and analogLightRight > 4000 and analogLightLeft > 4000) {         // if the middle is white and the outside is black
    right.write(80);                                                                            // turn right
    left.write(150);
  }
  if(analogLightCenter > 4000 and analogLightRight > 4000 and analogLightLeft < 4000) {         // if left is white and others are black
    right.write(80);                                                                            // turn right
    left.write(150);
  }
  if(analogLightCenter > 4000 and analogLightRight < 4000 and analogLightLeft > 4000) {         // if right is white and others are black
    right.write(30);                                                                            // go straight
    left.write(130);
  }
  if(analogLightCenter < 4000 and analogLightRight > 4000 and analogLightLeft < 4000) {         // if right is black and others are white
    right.write(80);                                                                            // turn right
    left.write(150);
  }
  if(analogLightCenter < 4000 and analogLightRight < 4000 and analogLightLeft > 4000) {         // if left is black and others are white
    right.write(20);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 4000 and analogLightRight > 4000 and analogLightLeft > 4000) {         // if all are black
    right.write(80);                                                                            // turn right
    left.write(150);
  }
}


void fieldSwitch() {
  SWITCH1 = digitalRead(PA_3);                  // attaches the left-right switch to digital pin PA_3
}

void lineFollow() {
  fieldSwitch();
  if (SWITCH1 == HIGH) {                        // if we're on the left side of the field                   
      lineFollowLeft();                         // follow the left side of the line
    }
  if (SWITCH1 == LOW) {                         // if we're on the right side of the field
      lineFollowRight();                        // follow the right side of the line
    }       
}

void resetSwitch() {
  SWITCH2 = digitalRead(PA_2);                  // attaches the left-right switch to digital pin PA_3
}

void greatBallLeft() {                            // capturing the great ball for the LEFT side of the field
  analogDistFRight = analogRead(A4);
  if(analogDistFRight >= 500) {                   // once the robot is 21 cm away from the wall               
    right.write(100);                             // slowly pivot toward the great ball
    left.write(100);
    delay(1500);
    gate.write(0);                                // lower front gate                             
  }
  resetSwitch();
  if (SWITCH2 == HIGH) {
    right.write(100);
    left.write(100);                              // pivot right until back on the line
    delay(1500);   
  }
  if (SWITCH2 == LOW) {
    right.write(80);
    left.write(80);
    delay(1500);
  }
}

void greatBallRight() {                           // capturing the great ball for the RIGHT side of the field
  analogDistFRight = analogRead(A4);
  if(analogDistFRight >= 500) {                   // once the robot is 21 cm away from the wall               
    right.write(80);                              // slowly pivot toward the great ball
    left.write(80);
    delay(1500);
    gate.write(0);                                // drop the front gate
  }
  if (SWITCH2 == HIGH) {                          // if reset switch is off
    right.write(80);
    left.write(80);                               // pivot left until on the line again
    delay(1500);   
  }
  if (SWITCH2 == LOW) {                           // if reset switch is on
    right.write(100);
    left.write(100);                              // pivot right until on the line again
    delay(1500);
  }
}

void greatBall() {
  fieldSwitch();
  if (SWITCH1 == HIGH) {                          // if we're on the left side of the field             
      greatBallLeft();                            // use left side great ball commands
    }
  if (SWITCH1 == LOW) {                           // if we're on the right side of the field
      greatBallRight();                           // use right side great ball commands
    }       
}

void loop() {

  analogLightCenter = analogRead(A0);             // attaches the #4 center light sensor to analog pin 0
  analogLightRight = analogRead(A1);              // attaches the #3 right light sensor to analog pin 1 
  analogLightLeft = analogRead(A2);               // attaches the #5 left light sensor to analog pin 2
  analogDistFRight = analogRead(A4);              // attaches the front right distance sensor to analog pin 4
  analogDistFCenter = analogRead(A11);            // attaches the front center distance sensor to analog pin 11 

  resetSwitch();
  if (SWITCH2 == HIGH) {                          // run this code if reset switch is off
    first();

    do {
      analogDistFCenter = analogRead(A11);
      lineFollow();
      } while(analogDistFCenter < 900);           // follow the line until front distance reads wall is 10cm away

      gate.write(0);                              // lower front gate to capture first pokeball  

    time1 = millis();                             // take the time
    do {
      time2 = millis();                           // take the time at the start of each loop                             
      lineFollow();
      } while(time2 - time1 < 5000);              // follow the line until the robot has passed the junction

    gate.write(90);                               // raise front gate
  
    greatBall();                                  // capture the great ball
  
    time3 = millis();                             // take the time
    do {
      time4 = millis();                           // take the time at the start of each loop
      lineFollow();
      } while(time3 - time4 < 2000);              // loop for 2.5 sec until the robot finishes the curve
  
    do {
      analogDistFRight = analogRead(A0);
      lineFollow();                               // will capture zaptos at this time
      } while(analogDistFRight < 750);            // loop until front distance reads wall is 40cm away after it captures zaptos
    }

  resetSwitch();
  if (SWITCH2 == LOW) {                          // run this code if reset switch is on
    first();
    
    time5 = millis();                             // take the time
    do {
      time6 = millis();                           // take the time at the start of each loop
      lineFollow();
      } while(time6 - time5 < 5000);              // follow the line until the robot passes the junction  
  
    greatBall();                                  // capture another great ball

    time7 = millis();                             // take the time
    do {
      time8 = millis();                          // take the time at the start of each loop
      lineFollow();                           // will capture the corner pokemon at this time
      } while(time8 - time7 < 2000);             // loop for 2.5 sec until the robot passes the curve
    
    right.write(90);
    left.write(90);
    delay(1000000000000000000);                   // and we're done unless we decide to do something else  
  }
}
