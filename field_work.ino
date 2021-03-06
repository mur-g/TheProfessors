#include <Servo.h> 

int SWITCH1 = 10;            // variable for switch determining left vs. right field
int SWITCH2 = 10;            // variable for switch determining first round vs. reset

int analogLightCenter = 0;  // variable for #4 light sensor
int analogLightRight = 0;   // variable for #3 light sensor
int analogLightLeft = 0;    // variable for #5 light sensor
// black is a high value and white is a low value

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

Servo right;    // create servo object to control right servo 
Servo left;     // create servo object to control left servo
Servo gate;     // create servo object to control gate servo

// 0 is full forwards for right and backwards for left
// 180 is full backwards for right and forwards for left


void setup() {
  pinMode(PA_3, INPUT);      // sets switch pins to input mode
  pinMode(PA_2, INPUT);
  Serial.begin(9600);
  
  right.attach(24);             // attaches the right servo on pin 23 to the servo object 
  left.attach(23);              // attaches the left servo on pin 24 to the servo object
  gate.attach(25);              // attaches the gate servo on pin 25 to the servo object
 
  loop();
}

void first() {
  delay(100);           // delay to allow power spike to pass
  gate.write(90);
  left.write(130);      // set left motor to forward
  right.write(30);      // set right motor to forward
  delay(250);           // move for .5 sec
}

void lineFollowLeft() {                         // LEFT side line follow code
  analogLightRight = analogRead(A1);              
  analogLightLeft = analogRead(A2);
  analogLightCenter = analogRead(A0);
  if(analogLightCenter > 3000 and analogLightRight < 3000 and analogLightLeft < 3000) {         // if the middle is black and the outside is white
    right.write(30);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter < 3000 and analogLightRight > 3000 and analogLightLeft > 3000) {         // if the middle is white and the outside is black
    right.write(30);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 3000 and analogLightRight > 3000 and analogLightLeft < 3000) {         // if left is white and others are black
    right.write(30);      //40                                                                      // turn left
    left.write(100);      //120
  }
  if(analogLightCenter > 3000 and analogLightRight < 3000 and analogLightLeft > 3000) {         // if right is white and others are black
    right.write(30);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter < 3000 and analogLightRight > 3000 and analogLightLeft < 3000) {         // if right is black and others are white
    right.write(80);                                                                            // turn right
    left.write(130);
  }
  if(analogLightCenter < 3000 and analogLightRight < 3000 and analogLightLeft > 3000) {         // if left is black and others are white
    right.write(30);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 3000 and analogLightRight > 3000 and analogLightLeft > 3000) {         // if all are black
    right.write(30);                                                                            // turn left
    left.write(100);
  }
}

void lineFollowRight() {                        // RIGHT side line follow code                       
  analogLightCenter = analogRead(A0);               
  analogLightRight = analogRead(A1);               
  analogLightLeft = analogRead(A2);                 
  if(analogLightCenter > 3000 and analogLightRight < 3000 and analogLightLeft < 3000) {         // if the middle is black and the outside is white
    right.write(80);                                                                            // turn right
    left.write(130);
  }
  if(analogLightCenter < 3000 and analogLightRight > 3000 and analogLightLeft > 3000) {         // if the middle is white and the outside is black
    right.write(80);                                                                            // turn right
    left.write(130);
  }
  if(analogLightCenter > 3000 and analogLightRight > 3000 and analogLightLeft < 3000) {         // if left is white and others are black
    right.write(80);                                                                            // turn right
    left.write(150);
  }
  if(analogLightCenter > 3000 and analogLightRight < 3000 and analogLightLeft > 3000) {         // if right is white and others are black
    right.write(80);       //40                                                                     // turn right
    left.write(150);       //120
  }
  if(analogLightCenter < 3000 and analogLightRight > 3000 and analogLightLeft < 3000) {         // if right is black and others are white
    right.write(80);                                                                            // turn right
    left.write(130);
  }
  if(analogLightCenter < 3000 and analogLightRight < 3000 and analogLightLeft > 3000) {         // if left is black and others are white
    right.write(30);                                                                            // turn left
    left.write(100);
  }
  if(analogLightCenter > 3000 and analogLightRight > 3000 and analogLightLeft > 3000) {         // if all are black
    right.write(80);                                                                            // turn right
    left.write(120);
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
  right.write(110);                             // slowly pivot toward the great ball
  left.write(110);
  delay(1500);
  right.write(90);                              // pause
  left.write(90);
  delay(1000);
  right.write(40);                              // move forward
  left.write(120);
  delay(200);
  gate.write(0);                                // lower front gate  
  delay(500);
  right.write(120);                             // move backward
  left.write(40);
  delay(500);
  resetSwitch();
  if (SWITCH2 == HIGH) {                          // if before reset
    right.write(110);
    left.write(110);                              // pivot right until back on the line
    delay(1500);   
  }
  if (SWITCH2 == LOW) {                           // if after reset
    right.write(70);
    left.write(70);                               // pivot left until back on the line
    delay(1500);
  }
}

void greatBallRight() {                           // capturing the great ball for the RIGHT side of the field               
  right.write(70);                              // slowly pivot toward the great ball
  left.write(70);
  delay(1500);
  right.write(90);                              // pause
  left.write(90);
  delay(1000);
  right.write(40);                              // move forward
  left.write(120);
  delay(200);
  gate.write(0);                                // drop the front gate
  delay(500);
  right.write(120);                             // move backward
  left.write(40);
  delay(500);
  if (SWITCH2 == HIGH) {                          // if before reset
    right.write(70);
    left.write(70);                               // pivot left until on the line again
    delay(1500); 
  }
  if (SWITCH2 == LOW) {                           // if after reset
    right.write(110);
    left.write(110);                              // pivot right until on the line again
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
  
  resetSwitch();
  if (SWITCH2 == HIGH) {                          // run this code if reset switch is off
    first();

    time1 = millis();
    fieldSwitch();
    if (SWITCH1 == HIGH) {                        // if we're on the left side of the field    
      do {
        time2 = millis();
        lineFollowLeft();
      } while(time2 - time1 < 2500);              // line follow for two and a half seconds                        
    }
    if (SWITCH1 == LOW) {                         // if we're on the right side of the field
      do {
        time2 = millis();                         // line follow for three seconds
        lineFollowRight();
      } while(time2 - time1 < 3000);             
    }

    gate.write(0);                                // lower front gate to capture first pokeball  

    time3 = millis();                             // take the time
    fieldSwitch();
    if (SWITCH1 == HIGH) {                        // if we're on the left side of the field    
      do {
        time4 = millis();                           // take the time at the start of each loop                             
        lineFollowLeft();
      } while(time4 - time3 < 12750);              // follow the line until the robot has passed the junction // 13000              
    }
    if (SWITCH1 == LOW) {                         // if we're on the right side of the field
      do {
        time4 = millis();                           // take the time at the start of each loop                             
        lineFollowRight();
      } while(time4 - time3 < 15750);              // follow the line until the robot has passed the junction // 15000   
    }

    gate.write(90);                               // raise front gate
  
    greatBall();                                  // capture the great ball
  
    time5 = millis();                             // take the time
    fieldSwitch();
    if (SWITCH1 == HIGH) {                        // if we're on the left side of the field    
      do {
        time6 = millis();                           // take the time at the start of each loop
        lineFollowLeft();
      } while(time6 - time5 < 20000);              // line follow for 2.5 sec until the robot finishes the curve             
    }
    if (SWITCH1 == LOW) {                         // if we're on the right side of the field
      do {
        time6 = millis();                           // take the time at the start of each loop
        lineFollowRight();
      } while(time6 - time5 < 20000);              // line follow for 2.5 sec until the robot finishes the curve 
    }
  }

  resetSwitch();
  if (SWITCH2 == LOW) {                           // run this code if reset switch is on
    first();
    
    time8 = millis();                             // take the time
    fieldSwitch();
    if(SWITCH1 == HIGH);
      do {
        time9 = millis();                           // take the time at the start of each loop
        lineFollowLeft();
        } while(time9 - time8 < 12750);              // follow the line until the robot passes the junction  
    if(SWITCH2 == LOW);
      do {
        time9 = millis();
        lineFollowRight();
      } while(time9 - time8 < 15750);
  
    greatBall();                                  // capture another great ball

    time10 = millis();                             // take the time
    do {
      time11 = millis();                           // take the time at the start of each loop
      lineFollow();                               // will capture the corner pokemon at this time
      } while(time11 - time10 < 15000);              // loop for 2.5 sec until the robot passes the curve
    
    right.write(90);
    left.write(90);
    delay(10000);                                 // and we're done unless we decide to do something else  
  }
}
