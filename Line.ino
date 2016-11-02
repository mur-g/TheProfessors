int lightSensor1 = A1;
int lightSensor2 = A2;
int lightSensor1Val = 0;
int lightSensor2Val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  lightSensor1Val = analogRead(lightSensor1);
  lightSensor2Val = analogRead(lightSensor2);
  Serial.print(lightSensor1Val);
  Serial.print(" ");
  Serial.println(lightSensor2Val);
  delay(100);
}
