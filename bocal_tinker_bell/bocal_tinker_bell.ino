#define TOUCH_PIN 12   // T5 touch
#define LED1 14
#define LED2 13
#define LED3 27

int threshold = 200;

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);
  //Serial.println(touchValue);

  if (touchValue < threshold) {
    fadeIn();
    //sparkle();
    fadeOut();
  }

  delay(40);
}

// ------------------------
void fadeIn() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(LED1, i);
    analogWrite(LED2, i);
    analogWrite(LED3, i);
    delay(4);
  }
}

void fadeOut() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED1, i);
    analogWrite(LED2, i);
    analogWrite(LED3, i);
    delay(4);
  }
}

void sparkle() {
  for (int s = 0; s < 30; s++) {
    int brightness = random(50, 255);
    int selected = random(1,4);

    if (selected == 1) analogWrite(LED1, brightness);
    if (selected == 2) analogWrite(LED2, brightness);
    if (selected == 3) analogWrite(LED3, brightness);

    Serial.println(selected);
    Serial.println(brightness);

    delay(100);
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);
  }
}
