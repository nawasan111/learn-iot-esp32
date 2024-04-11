#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("abc", "12345678");
  if (result == true) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
  }
}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}