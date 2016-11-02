int sensor_fr = 0;  // front right IR proximity sensor
int sensor_fl = 0;  // front left IR proximity sensor
int sensor_br = 0;  // back right IR proximity sensor
int sensor_bl = 0;  // back left IR proximity sensor

void setup() {
  Serial.begin(9600);     // setup serial
}

void loop() {
  int front_speed = analogRead(A3);               // the input from the front sensor connected to analog pin 3
  Serial.println(front_speed);
  delay(500);

}
