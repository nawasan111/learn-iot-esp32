#include <ArduinoJson.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#define dw(p, m) digitalWrite(p, m)
#define dr(p) digitalRead(p)
#define pm(p, m) pinMode(p, m)
#define aw(p, m) analogWrite(p, m)
#define ar(p) analogRead(p)
