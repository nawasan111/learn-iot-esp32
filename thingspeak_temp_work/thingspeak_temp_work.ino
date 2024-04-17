#include <DHT.h>
#include <WiFi.h>
#include <fetch_api.h>

String apiKey = "45TEE0SG3QNQNYHE";
const char* ssid = "UMR_Lab1";
const char* password = "Ubon2566";

#define HOST "api.thingspeak.com"
#define DHTPIN 32

DHT dht(DHTPIN, DHT11);
Fetch fetch;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  fetch.setup(ssid, password);
  fetch.set_host(HOST);
  Serial.println("\nWiFi connected");
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String postStr = apiKey;
  postStr += "&field1=";
  postStr += String(t);
  postStr += "&field2=";
  postStr += String(h);
  postStr += "&field3=";
  postStr += String(f);
  String header[] = {"X-THINGSPEAKAPIKEY: " + apiKey};
  fetch.post("/update", postStr, header_parse(header, 1));

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" degrees Celcius Humidity: ");
  Serial.print(h);
  Serial.println("% send to Thingspeak");

  delay(2000);
  Serial.println("Waiting...");
  delay(15000);
}