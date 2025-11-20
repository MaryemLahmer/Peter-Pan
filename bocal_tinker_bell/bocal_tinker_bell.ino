#define TOUCH_PIN 12 // (maillage autour du bocal)
#define LED1 14 
#define LED2 13 
#define LED3 27 


int threshold = 200; // a calibrer selon le maillage

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);
  Serial.println(touchValue); //pour calibrer

  if (touchValue < threshold){
    fadeIn();
    sparkle();
    fadeOut();
  }

  delay(50);

}

void fadeIn(){
  for (int i =0; i<3; i++){
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED3, HIGH);
    delay(100);
  }
}


void sparkle(){
  for (int i = 0; i < 20; i++) {
    int r = random(1,4);
    if (r == 1) digitalWrite(LED1, HIGH);
    if (r == 2) digitalWrite(LED2, HIGH);
    if (r == 3) digitalWrite(LED3, HIGH);

    delay(random(50,120));

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

    delay(random(50,120));
  }
}

// Extinction douce
void fadeOut() {
  digitalWrite(LED1, LOW);
  delay(150);
  digitalWrite(LED2, LOW);
  delay(150);
  digitalWrite(LED3, LOW);
}



















