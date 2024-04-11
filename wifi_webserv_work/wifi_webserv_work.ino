#include <DHT.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "oled.h"
#include "rgb.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

const char* ssid = "ASDF";
const char* password = "Ubon2566";

#define DHT_PIN 32

#define DHT_TYPE DHT11

WebServer server(80);
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  dht.begin();
  rgb_init();
  oled_init(display);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  bool result = WiFi.softAP(ssid, password);
  if(result) {
    Serial.println("wifi ready");
  } else {
    Serial.println("WiFi Failed");
  }
  // WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.print("Connected to ");
  // Serial.println(ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());

  // if (MDNS.begin("esp32")) {
    // Serial.println("MDNS responder started");
  // }

  server.on("/", handleRoot);

  server.on("/control", []() {
    String led = server.arg("led");
    String status = server.arg("status");
    int pin_c = 0;
    if (led.equals("red")) {
      pin_c = R;
    } else if (led.equals("green")) {
      pin_c = G;
    } else if (led.equals("relay")) {
      pin_c = RELAY;
    }
    if (pin_c != 0) {
      digitalWrite(pin_c, status.equals("on") ? 1 : 0);
      server.send(200, "text/plain", "action completed");
    } else {
      server.send(200, "text/plain", "failed");
    }
  });

  server.on("/oled", []() {
    String oled_text = server.arg("text");
    oled_print(display, oled_text);
    server.send(200, "text/plain", "oled print success");
  });

  server.on("/hum", []() {
    float h = dht.readHumidity();
    if (isnan(h)) {
      server.send(200, "text/plain", "reading failed");
    } else {
      server.send(200, "text/plain", "Humidity: " + String(h));
    }
  });

  server.on("/temp", []() {
    float h = dht.readTemperature();
    if (isnan(h)) {
      server.send(200, "text/plain", "reading failed");
    } else {
      server.send(200, "text/plain", "Temperature: " + String(h));
    }
  });

  server.on("/inline",
            []() { server.send(200, "text/plain", "this works as well"); });

  server.on("/rgb/g", []() {
    rgb_green();
    server.send(200, "text/plain", "change led to green");
  });

  server.on("/rgb/r", []() {
    rgb_red();
    server.send(200, "text/plain", "change led to red");
  });

  server.on("/rgb/all", []() {
    rgb_all();
    server.send(200, "text/plain", "trun on all led");
  });

  server.on("/rgb/off", []() {
    rgb_off();
    server.send(200, "text/plain", "all led is off.");
  });

  server.on("/rgb/relay", []() {
    rgb_relay();
    server.send(200, "text/plain", "relay on");
  });

  server.on("/red/on", []() {
    rgb_red_on();
    server.send(200, "text/plain", "red on");
  });
  server.on("/red/off", []() {
    rgb_red_off();
    server.send(200, "text/plain", "red off");
  });
  server.on("/green/on", []() {
    rgb_green_on();
    server.send(200, "text/plain", "green on");
  });
  server.on("/green/off", []() {
    rgb_green_off();
    server.send(200, "text/plain", "green off");
  });
  server.on("/relay/on", []() {
    rgb_relay_on();
    server.send(200, "text/plain", "relay on");
  });
  server.on("/relay/off", []() {
    rgb_relay_off();
    server.send(200, "text/plain", "relay off");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);  // allow the cpu to switch to other tasks
}
