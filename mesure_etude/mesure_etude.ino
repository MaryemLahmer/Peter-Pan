void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i=0; i<= 65500; i+=500) {
    touchSetCycles(i, 256);
    for (int j=0; j<100; j++) {
      Serial.print(touchRead(27));
      Serial.print(',');
    }
    Serial.print('\n');
    delay(10);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
