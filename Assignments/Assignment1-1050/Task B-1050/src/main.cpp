/*
  Title: Single Button Press-Type Detection with OLED Display (Final Stable Version)
  Name: Minahal Fatima
  Reg No: 23-NTU-CS-1050
  Task B — Use a single button to detect Short and Long press

  ▶ Short Press  → Toggle LED
  ▶ Long Press   → Play Buzzer Tone
  ▶ OLED Display → Shows which event occurred
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Pin Definitions ---
#define LED_PIN 2
#define BUZZER_PIN 27
#define BUTTON_PIN 12

// --- Timing & State Variables ---
unsigned long pressStartTime = 0;  // Time when button was first pressed
bool buttonPressed = false;        // Track button hold state
bool ledState = false;             // Store LED ON/OFF state

// --- Function to show text on OLED ---
void showMessage(const String &msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

void setup() {
  // --- Pin setup ---
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button active LOW

  Serial.begin(115200);

  // --- OLED Initialization ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED initialization failed"));
    while (1);
  }

  showMessage("Press Button...");
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // --- Detect button press (LOW = pressed) ---
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    pressStartTime = millis();  // Start timing when button pressed
  }

  // --- Detect button release ---
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
    unsigned long pressDuration = millis() - pressStartTime;

    // Short press → toggle LED
    if (pressDuration < 1500) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      showMessage("Short Press → LED " + String(ledState ? "ON" : "OFF"));
      tone(BUZZER_PIN, 1200, 60); // Small beep feedback
      Serial.println("Short Press Detected");
    }

    // Long press → play buzzer tone
    else {
      showMessage("Long Press → Buzzer");
      tone(BUZZER_PIN, 1000); // Start tone
      delay(600);             // Play for 0.6s
      noTone(BUZZER_PIN);     // Stop tone
      Serial.println("Long Press Detected");
    }
  }

  delay(20); // Small debounce delay
}
