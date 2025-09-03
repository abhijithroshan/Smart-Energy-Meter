#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

// WiFi details
const char* ssid = "MyHomeWiFi";         // your Wi-Fi name
const char* password = "12345678";       // your Wi-Fi password

// ThingSpeak details
unsigned long channelID = 1234567;       // your ThingSpeak channel ID
const char* writeAPIKey = "ABCDEF1234567890";  // your ThingSpeak Write API Key

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

