#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define BUZ 27
#include "DHT.h"
#include "buzzer.h"

#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 32

int buz_state = 0;
int input_ser = 0;
float temp = 0;

DHT dht(32, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHT, &Wire);

void setup() {
  buz_setup();
  // setup dht
  Wire.begin();
  Serial.begin(115200);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  //  setup display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello!");
  display.display();
}

void loop() {
  delay(2000);
  if (buz_state) {
    buz_on();
  }
  if(Serial.available() > 0) {
    String input_tmp = Serial.readString();  
    input_tmp.trim();
    if(input_tmp == "off") {
      Serial.println("off change action");
      input_ser = 0;
    } else {
      Serial.println("change temp");
      input_ser = 1;
      temp = input_tmp.toFloat();
      Serial.print("temp has change to ");
      Serial.println(temp);
    }
  }
  if(input_ser == 0) {
  temp = dht.readTemperature();
  }
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(temp);
  display.clearDisplay();
  display.setCursor(0, 10);
  if (temp >= 30) {
    display.println("Hot");
    buz_state = 1;
  } else if (temp >= 25) {
    display.println("Normal");
    buz_state = 0;
  } else {
    display.println("Cold");
    buz_state = 0;
  }
  display.display();
}