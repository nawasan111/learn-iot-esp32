#define R 18
#define G 19
#define B 23
#include "macro.h"
#include "rgb.h"

int incoming_byte = 0;
void setup() {
  Serial.begin(9600);

  Serial2.begin(9600);
  Serial2.setPins(16, 17);
  pm(R, OUTPUT);
  pm(G, OUTPUT);
  pm(B, OUTPUT);

  pinMode(33, OUTPUT);
}

void loop() {
  Serial.println("Enter Data");
  while (Serial.available() == 0) {
  }
  String teststr = Serial.readString();
  teststr.trim();
  // sending data to another board
  // Serial2.write(teststr);
  if (teststr == "light") {
    light();
    dw(33, HIGH);
    Serial2.write("light");
  } else if (teststr == "red") {
    Serial2.write("red");
    red();
    dw(33, HIGH);
  } else if (teststr == "blue") {
    blue();
    dw(33, HIGH);
    Serial2.write("blue");
  } else if (teststr == "green") {
    green();
    dw(33, HIGH);
    Serial2.write("green");
  } else if (teststr == "off") {
    rgb_off();
    dw(33, LOW);
    Serial2.write("off");
  } else {
    dw(33, LOW);
    rgb_off();
    Serial.println("not found command: [light, red, blue, green, off]");
    Serial2.write("off");
  }
}
