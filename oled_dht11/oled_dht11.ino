#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "DHT.h"
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 32

DHT dht(32, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHT, &Wire);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello!");
  display.display();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.print("Humidity: ");
  display.print(h);
  display.println(" %");
  display.print("Temperature: ");
  display.print(t);
  display.print("°C ");
  display.print(f);
  display.println("°F");
  display.display();
}