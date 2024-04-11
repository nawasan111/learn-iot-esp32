/*
RFID -> 23 19 18 5 25
@LED -> SDL SDA
DHT11 -> 32
RGB -> 16, 17
*/
#include <WiFi.h>
#define HOST "www.nawasan.dev/api/info"
#define WIFI_HOSTNAME "UMR_Lab1"
#define WIFI_PASSWORD "Ubon2566"
#include "rgb.h"

void setup() {
  rgb_init();
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_HOSTNAME, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println();
  Serial.print("Connected, Ip address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client;
    Serial.printf("\nConnecting to %s ...\n", HOST);
    if (client.connect(HOST, 80)) {
        Serial.println("Connected");

        Serial.println("Sending request");
        client.print(String("GET /") + "HTTP/1.1\r\n" +
            "HOST: " + HOST + "\r\n" +
            "Connecttion: close\r\n" + 
            "\r\n");

        Serial.print("response: ");
        while (client.connected() || client.available()) {
            if (client.available()) {
                String line = client.readStringUntil('\n');
                Serial.println(line);
            }
        }
    }
}