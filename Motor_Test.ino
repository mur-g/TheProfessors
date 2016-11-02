#include <Servo.h>

Servo right;

void setup() {
  // put your setup code here, to run once:
  right.attach(23);
}

void loop() {
  // put your main code here, to run repeatedly: 
  right.write(180);
  delay(1000);
  right.write(90);
  delay(1000);
  right.write(0);
  delay(1000);
}
