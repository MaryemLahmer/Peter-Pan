// ============================================================
// TINKER BELL INTERACTIVE LIGHT EXPERIENCE
// WS2812B addressable LED strip (4 LEDs)
// Capacitive touch via conductive-coated glass
// ============================================================
// REQUIRES: Adafruit NeoPixel library
//   Arduino IDE: Sketch -> Include Library -> Manage Libraries
//   Search "NeoPixel" -> Install "Adafruit NeoPixel"
// ============================================================
// TOUCHREAD WINDOWS FIX:
//   If touchRead() returns garbage on Windows:
//   - Add this line at the very top of the file:
//       #define touchRead(pin) touchReadRaw(pin)
//   - Or add: #include <esp32-hal-touch.h>
//   - Make sure your board manager URL is:
//       https://dl.espressif.com/dl/package_esp32_esp32_index.json
// ============================================================
#include <Adafruit_NeoPixel.h>
#include <esp32-hal-touch.h>

// --- PIN CONFIGURATION ---
#define TOUCH_PIN   32   // GPIO 32 = T9 capacitive touch
#define LED_PIN     2    // GPIO 2 -> Din on strip (through 330 ohm)
#define NUM_LEDS    4

// --- NEOPIXEL SETUP ---
// WS2812B = NEO_GRB, 800kHz
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- TOUCH CALIBRATION ---
// Read Serial with 0, 1, 2... fingers and adjust these.
// Lower value = more fingers (more capacitance).
#define THRESH_0    70
#define THRESH_1    58
#define THRESH_2    48
#define THRESH_3    40
#define THRESH_4    33

// --- GLOBALS ---
int activeTouches   = 0;
int previousTouches = 0;

// ============================================================
//  SETUP
// ============================================================
void setup() {
  Serial.begin(9600);

  strip.begin();
  //strip.setMaxRefreshRate(400);  // cap refresh rate, easier on the ESP32
  strip.show();                  // init to off
  strip.setBrightness(255);

  Serial.println("=== Tinker Bell Ready (WS2812B x4) ===");
  Serial.println("Touch the glass...");
}

// ============================================================
//  MAIN LOOP
// ============================================================
void loop() {
  activeTouches = countTouches();

  // transition flash when touch count changes
  if (activeTouches != previousTouches && activeTouches > 0) {
    transitionFlash(activeTouches);
  }
  previousTouches = activeTouches;

  // run animation
  switch (activeTouches) {
    //case 0: fadeToOff();          break;
    case 1: gentleGlow();         break;
    case 2: pulseWave();          break;
    case 3: magicSparkle();       break;
    case 4: fairyDance();         break;
    default: pixieDustExplosion(); break;
  }

  // debug every 500ms
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 500) {
    Serial.print("Raw: ");
    Serial.print(touchRead(TOUCH_PIN));
    Serial.print("  |  Touches: ");
    Serial.println(activeTouches);
    lastDebug = millis();
  }
}

// ============================================================
//  TOUCH COUNTING
// ============================================================
int countTouches() {
  int value = touchRead(TOUCH_PIN);
  if (value > THRESH_0) return 0;
  if (value > THRESH_1) return 1;
  if (value > THRESH_2) return 2;
  if (value > THRESH_3) return 3;
  if (value > THRESH_4) return 4;
  return 5;
}

// ============================================================
//  UTILITY
// ============================================================

void allOff() {
  strip.fill(0, 0, NUM_LEDS);
  strip.show();
}

// smooth fade out when nobody is touching
void fadeToOff() {
  static int fadeBrightness = 255;
  if (fadeBrightness > 0) {
    fadeBrightness -= 4;
    if (fadeBrightness < 0) fadeBrightness = 0;
    strip.setBrightness(fadeBrightness);
    strip.show();
  } else {
    strip.fill(0);
    strip.show();
    fadeBrightness = 255;       // reset for next time
    strip.setBrightness(255);
  }
}

// white double-flash when a new person joins
void transitionFlash(int count) {
  int burstLevel = 80 + count * 35;
  if (burstLevel > 255) burstLevel = 255;

  strip.fill(strip.Color(burstLevel, burstLevel, burstLevel));
  strip.show();
  delay(60);
  strip.fill(0);
  strip.show();
  delay(40);
  strip.fill(strip.Color(burstLevel, burstLevel, burstLevel));
  strip.show();
  delay(40);
  strip.fill(0);
  strip.show();
}

// ============================================================
//  ANIMATION 1 — GENTLE GLOW (1 person)
//  Warm white breathing. Each LED slightly offset in phase
//  so it feels organic, like a single candle flame.
// ============================================================
void gentleGlow() {
  static int phase = 0;
  phase = (phase + 2) % 360;

  for (int i = 0; i < NUM_LEDS; i++) {
    float offset = i * 15.0;  // 15 degrees between each LED
    float val = (sin((phase + offset) * PI / 180.0) + 1.0) * 0.5;
    // warm white: R > G > B
    int r = (int)(val * 200) + 30;
    int g = (int)(val * 160) + 20;
    int b = (int)(val * 80)  + 10;
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

// ============================================================
//  ANIMATION 2 — PULSE WAVE (2 people)
//  A cool blue-white wave chases around the strip.
//  Speed ramps up every 3 seconds then resets — the glass
//  feels like it's reacting and building energy.
// ============================================================
void pulseWave() {
  static int phase = 0;
  static int speed = 4;
  static unsigned long speedTimer = 0;

  if (millis() - speedTimer > 3000) {
    speed += 2;
    speedTimer = millis();
    if (speed > 14) speed = 4;
  }

  phase = (phase + speed) % 360;

  for (int i = 0; i < NUM_LEDS; i++) {
    float offset = i * 90.0;  // 90 degrees apart for 4 LEDs
    float val = (sin((phase + offset) * PI / 180.0) + 1.0) * 0.5;
    // cool blue-white
    int r = (int)(val * 80);
    int g = (int)(val * 180);
    int b = (int)(val * 255);
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

// ============================================================
//  ANIMATION 3 — MAGIC SPARKLE (3 people)
//  Random pixels flash in random colors at random brightness.
//  30% chance of a double-sparkle. LEDs decay (fade) at
//  different rates so it looks like dust drifting.
//  Color palette: gold, pink, cyan, white, violet.
// ============================================================
void magicSparkle() {
  static unsigned long lastSparkle = 0;
  static int bright[4]  = {0, 0, 0, 0};
  static int decay[4]   = {1, 1, 1, 1};
  static uint32_t colors[4] = {0, 0, 0, 0};

  // fairy color palette
  uint32_t palette[] = {
    strip.Color(255, 215, 0),   // gold
    strip.Color(255, 105, 180), // pink
    strip.Color(0,   255, 255), // cyan
    strip.Color(255, 255, 240), // warm white
    strip.Color(180, 100, 255)  // violet
  };
  int paletteSize = 5;

  int interval = random(60, 160);
  if (millis() - lastSparkle > interval) {
    int count = (random(0, 100) < 30) ? 2 : 1;
    for (int i = 0; i < count; i++) {
      int led    = random(0, NUM_LEDS);
      bright[led] = random(160, 255);
      decay[led]  = random(3, 7);
      colors[led] = palette[random(0, paletteSize)];
    }
    lastSparkle = millis();
  }

  // decay and render each pixel
  for (int i = 0; i < NUM_LEDS; i++) {
    bright[i] -= decay[i];
    if (bright[i] < 0) bright[i] = 0;

    // extract RGB from stored color, scale by brightness
    uint8_t r = (colors[i] >> 16) & 0xFF;
    uint8_t g = (colors[i] >>  8) & 0xFF;
    uint8_t b =  colors[i]        & 0xFF;
    float scale = bright[i] / 255.0;
    strip.setPixelColor(i, strip.Color(
      (int)(r * scale),
      (int)(g * scale),
      (int)(b * scale)
    ));
  }
  strip.show();
}

// ============================================================
//  ANIMATION 4 — FAIRY DANCE (4 people)
//  One bright magenta pixel bounces: 0->1->2->3->2->1->0...
//  Speed alternates fast/slow for a playful feel.
//  A dim ghost trails on the previous pixel so the motion
//  feels smoother and more fluid.
// ============================================================
void fairyDance() {
  static int step      = 0;
  static int prevLed   = -1;
  static unsigned long lastMove = 0;
  static bool fastStep = true;

  int interval = fastStep ? 70 : 160;

  if (millis() - lastMove > interval) {
    // bounce index: 0 1 2 3 2 1  (cycle of 6)
    int ledIndex = step;
    if (step >= 4) ledIndex = 6 - step;

    strip.fill(0);

    // ghost trail on previous LED
    if (prevLed >= 0 && prevLed != ledIndex) {
      strip.setPixelColor(prevLed, strip.Color(60, 10, 80));
    }

    // main bright pixel — magenta
    strip.setPixelColor(ledIndex, strip.Color(220, 40, 200));

    strip.show();

    prevLed  = ledIndex;
    step     = (step + 1) % 6;
    fastStep = !fastStep;
    lastMove = millis();
  }
}

// ============================================================
//  ANIMATION 5 — PIXIE DUST EXPLOSION (5+ people)
//  Full chaos. Random colors every 40ms.
//  Brightness envelope ramps up/down over 4 seconds.
//  Every 12th frame: white heartbeat flash.
// ============================================================
void pixieDustExplosion() {
  static unsigned long lastChange = 0;
  static unsigned long cycleStart = millis();
  static int frameCount = 0;

  if (millis() - lastChange > 40) {
    float cyclePos = ((millis() - cycleStart) % 4000) / 4000.0;
    float envelope = (cyclePos < 0.5)
        ? (cyclePos * 2.0)
        : (2.0 - cyclePos * 2.0);
    int maxB = 80 + (int)(envelope * 175);

    frameCount++;

    if (frameCount % 12 == 0) {
      strip.fill(strip.Color(maxB, maxB, maxB));
    } else {
      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, strip.Color(
          random(0, maxB),
          random(0, maxB),
          random(0, maxB)
        ));
      }
    }
    strip.show();
    lastChange = millis();
  }
}
