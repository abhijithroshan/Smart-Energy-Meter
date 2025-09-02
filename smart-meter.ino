#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

// WiFi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak details
unsigned long channelID = YOUR_CHANNEL_ID;
const char* writeAPIKey = "YOUR_WRITE_API_KEY";

WiFiClient client;

int sensorPin = A0;  // ACS712 connected to A0

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop() {
  int rawValue = analogRead(sensorPin);  
  float voltage = (rawValue * 3.3) / 1024.0;  
  float current = (voltage - 2.5) / 0.185;  // for ACS712-5A module

  Serial.print("Current: ");
  Serial.println(current);

  ThingSpeak.writeField(channelID, 1, current, writeAPIKey);

  delay(20000);  // update every 20 seconds
}
