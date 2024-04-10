#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define oled_init(display)                            \
  ({                                                  \
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { \
      Serial.println(F("SSD1306 allocation failed")); \
      for (;;);                                       \
    }                                                 \
    display.clearDisplay();                           \
    display.setTextSize(1);                           \
    display.setTextColor(WHITE);                      \
    display.setCursor(0, 10);                         \
    display.println("Ready!");                        \
    display.display();                                \
  })

#define oled_print(display, value) \
  ({                               \
    display.clearDisplay();        \
    display.setCursor(0, 10);      \
    display.println(value);        \
    display.display();             \
  })