#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello! UMR");
  display.display();
  Serial.println("Ready");
}
void loop() {
  Serial.println("input ready");
  while (Serial.available() == 0) {
  }
  String textstr = Serial.readString();
  Serial.println("command action");
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(textstr);
  display.display();
}