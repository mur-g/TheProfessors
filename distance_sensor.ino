int sensor_fr = 0;  // front right IR proximity sensor
int sensor_fl = 0;  // front left IR proximity sensor
int sensor_br = 0;  // back right IR proximity sensor
int sensor_bl = 0;  // back left IR proximity sensor

void setup() {
  Serial.begin(9600);     // setup serial

  pinMode(12, OUTPUT);    // sets pin 12 as output
  pinMode(13, OUTPUT);    // sets pin 13 as output

}

void loop() {
  int front_speed = analogRead(A7);               // the input from the front sensor connected to analog pin 7
  int front = map(front_speed, 0, 1023, 0, 255);  // scales down the analogRead from max of 1023 to max of 255 compatible with the sensor
  analogWrite(12, front);                         // pin 12 will have a PWM value of the variable front

  int back_speed = analogRead(A4);                // the input from the back sensor connected to analog pin 4
  int back = map(back_speed, 0, 1023, 0, 255);    // scales down the analogRead from max of 1023 to max of 255 compatible with the sensor
  analogWrite(13, back);                          // pin 13 will have a PWM value of the variable back
  
}
