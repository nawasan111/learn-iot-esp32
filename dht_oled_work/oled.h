#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 32

#define init_screen(display) \
  ({                             \
    display.clearDisplay();      \
    display.setTextSize(1);      \
    display.setTextColor(WHITE); \
    display.setCursor(0, 10);    \
    display.println("Hello!");   \
    display.display();           \
  })

#define oled_is_error(display)                        \
  ({                                                  \
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { \
      Serial.println(F("SSD1306 allocation failed")); \
      for (;;);                                       \
    }                                                 \
  })
