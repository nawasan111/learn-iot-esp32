// #define GD 3
#define R 18
#define G 19
#define B 23
#define BUZ 32
#include "macro.h"
#include "rgb.h"
#include "buzzer.h"

int val = 0;

void setup() {
  Serial.begin(9600);
  pm(R, OUTPUT);
  pm(G, OUTPUT);
  pm(B, OUTPUT);
  // Buzzer io
  pm(BUZ, OUTPUT);
  dw(BUZ,HIGH);
  // read 
  pm(33, OUTPUT);
    pm(36, INPUT);
  pm(35, INPUT);
  // analog
  // ledcSetup(ledChanal, freq, resolution);
  ledcWrite(0, 50);
}

void loop() {
  val = analogRead(35);
  Serial.println(val);
  // dw(33, val);
  // dw(B, val);
  // dw(B, dr(36));
  if (val > 1000) {
    red();
  } else {
    green();
  }
  delay(2000);
}

void rgb_buzzer() {
  green();
  buz_on();
  delay(5 * minites);
  yellow();
  buz_on();
  delay(2 * minites);
  red();
  buz_on();
  delay(5 * minites);
}
