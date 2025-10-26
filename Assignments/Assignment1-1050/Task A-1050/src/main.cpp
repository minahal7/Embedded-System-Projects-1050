/*
  -------------------------------------------------------------------------
  Title   : LED Mode Controller with OLED Display (Interrupt + Stable Debounce)
  Name    : Minahal Fatima
  Reg No  : 23-NTU-CS-1050
  Board   : ESP32 (compatible with Wokwi)
  -------------------------------------------------------------------------
  Description:
  • This program controls 3 LEDs, a buzzer, and an OLED display.
  • One button (MODE) cycles through four LED modes:
        0 - All LEDs OFF
        1 - Alternate blinking
        2 - Both LEDs ON
        3 - PWM fade effect
  • The second button (RESET) resets the system to Mode 0.
  • OLED shows the current mode and button events.
  • Interrupts are used for stable and responsive button handling.
  • Software debouncing ensures accurate button press detection.
  -------------------------------------------------------------------------
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==================== OLED Setup ====================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ==================== Pin Definitions ====================
#define LED1 2
#define LED2 4
#define LED3 5
#define BUZZER 27
#define BTN_MODE 12
#define BTN_RESET 14

// ==================== Variables ====================
// For debounce and interrupt control
volatile unsigned long lastModeInterrupt = 0;
volatile unsigned long lastResetInterrupt = 0;
const unsigned long debounceDelay = 250;  // debounce time in ms

// Flags set by interrupts (read inside loop)
volatile bool modePressed = false;
volatile bool resetPressed = false;

// Mode and LED control variables
int mode = 0;
unsigned long lastBlinkTime = 0;
int blinkState = 0;
int fadeValue = 0;
int fadeDir = 1;  // Direction of fade (1 = brighter, -1 = dimmer)

// ==================== Helper Function ====================
// Function to print messages on OLED screen
void showMessage(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

// ==================== Interrupt Service Routines ====================
// ISR for MODE button press
void IRAM_ATTR handleModePress() {
  unsigned long currentTime = millis();
  // Check debounce timing
  if (currentTime - lastModeInterrupt > debounceDelay) {
    modePressed = true;              // set flag for main loop
    lastModeInterrupt = currentTime; // update last press time
  }
}

// ISR for RESET button press
void IRAM_ATTR handleResetPress() {
  unsigned long currentTime = millis();
  // Check debounce timing
  if (currentTime - lastResetInterrupt > debounceDelay) {
    resetPressed = true;              // set flag for main loop
    lastResetInterrupt = currentTime; // update last press time
  }
}

// ==================== Setup Function ====================
void setup() {
  // Set pin modes
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  Serial.begin(115200);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED initialization failed!"));
    while (1);
  }

  // Attach interrupts for buttons (triggered on falling edge)
  attachInterrupt(digitalPinToInterrupt(BTN_MODE), handleModePress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET), handleResetPress, FALLING);

  // Show initial message
  showMessage("Mode 0: Both OFF");
}

// ==================== Main Loop ====================
void loop() {
  // ===== Handle MODE Button Press =====
  if (modePressed) {
    modePressed = false;             // clear flag
    mode = (mode + 1) % 4;           // cycle through 4 modes
    tone(BUZZER, 1200, 80);          // buzzer feedback

    // Display mode name on OLED
    String msg;
    switch (mode) {
      case 0: msg = "Mode 0: Both OFF"; break;
      case 1: msg = "Mode 1: Alternate Blink"; break;
      case 2: msg = "Mode 2: Both ON"; break;
      case 3: msg = "Mode 3: PWM Fade"; break;
    }
    showMessage(msg);
  }

  // ===== Handle RESET Button Press =====
  if (resetPressed) {
    resetPressed = false;            // clear flag
    mode = 0;                        // reset to mode 0
    tone(BUZZER, 800, 100);          // buzzer reset tone
    showMessage("Reset → Mode 0: OFF");
  }

  // ===== LED Behavior Based on Mode =====
  unsigned long currentTime = millis();

  switch (mode) {
    // Mode 0: All LEDs OFF
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;

    // Mode 1: Alternate blinking LEDs
    case 1:
      if (currentTime - lastBlinkTime > 400) {  // non-blocking timing
        lastBlinkTime = currentTime;
        blinkState = !blinkState;
        digitalWrite(LED1, blinkState);
        digitalWrite(LED2, !blinkState);
      }
      break;

    // Mode 2: Both LEDs ON
    case 2:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      break;

    // Mode 3: PWM Fade on LED3
    case 3:
      analogWrite(LED3, fadeValue);
      fadeValue += fadeDir * 5;  // smooth fade step
      if (fadeValue <= 0 || fadeValue >= 255) fadeDir = -fadeDir;  // reverse fade
      delay(10);  // small smooth delay (non-blocking for interrupts)
      break;
  }
}
