#include <WiFi.h>

const char* ssid = "Infinix HOT 60 Pro";
const char* password = "ayesha128";

// Static IP configuration (Enter values from your computer/router)
IPAddress local_IP(10,28,162,172);   // ESP32 static IP (you choose)
IPAddress gateway(10, 1, 1, 1);      // Your router gateway
IPAddress subnet(255, 0, 0, 0);     // Your network subnet

void setup() {
  Serial.begin(115200);

  // Apply static IP
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Static IP Failed!");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
