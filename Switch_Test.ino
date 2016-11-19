int TGLPIN = 10;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(TGLPIN, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly: 
 int tglOn = digitalRead(TGLPIN);
 Serial.println(tglOn);
 delay(100);
 
}
