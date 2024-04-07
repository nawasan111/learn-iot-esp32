#include "DHT.h"
#include "oled.h"
#include "serial_input.h"

#define BUZ 27
#include "buzzer.h"

DHT dht(32, DHT11);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHT, &Wire);

int buz_state = 0;
int input_ser = 0;
float temp = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  buz_setup();
  Wire.begin();

  init_screen(display);
}

void loop() {
  delay(2000);
  if (buz_state) {
    buz_on();
  }
  manual_input_temp(Serial, input_ser);

  if (input_ser == 0) {
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