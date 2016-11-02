int analogValueFront = 0;    // variable to hold the analog value
int analogValueBack = 0;

void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog input on pin 0:
  analogValueFront = analogRead(A2);
  analogValueBack = analogRead(A1);
  // print it out in many formats:
  Serial.println(analogValueFront);
  Serial.println(analogValueBack);
  Serial.println("");
  // print as an ASCII-encoded decimal
  // delay 10 milliseconds before the next reading:
  delay(500);
}
