#include <ArduinoJson.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#define dw(p, m) digitalWrite(p, m)
#define dr(p) digitalRead(p)
#define pm(p, m) pinMode(p, m)
#define aw(p, m) analogWrite(p, m)
#define ar(p) analogRead(p)
#define R 18
#define G 19
#define B 23
#define RELAY 33
// Update these with values suitable for your network.

const size_t capacity = JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);
DynamicJsonDocument led(capacity);
char buffer[512];

const char* ssid = "UMR_Lab1";
const char* password = "Ubon2566";
const char* mqtt_server = "192.168.1.115";

WiFiClient espClient;
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int red = 0;
int green = 0;
int blue = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
 char buf[length + 1];
  for (int i = 0; i < length; i++) {
    buf[i] = payload[i];
  }
  buf[length] = '\0';
  Serial.println("topic action");
  String tex = buf;
  int rgbp = tex.toInt();
  if (true) {
    if (rgbp > 255 || rgbp < 0) return;
    if (String(topic) == "/red") {
      aw(R, rgbp);
      red = rgbp;
      Serial.println("Red has change");
    } else if (String(topic) == "/green") {
      aw(G, rgbp);
      green = rgbp;
      Serial.println("Green has change");
    } else if (String(topic) == "/blue") {
      aw(B, rgbp);
      blue = rgbp;
      Serial.println("Red has change");
    } else if (String(topic) == "/relay") {
      dw(RELAY, rgbp > 0 ? 1 : 0);
      Serial.println("Relay has change");
    } else if (String(topic) == "/rgb") {
      aw(R, rgbp);
      red = rgbp;
      blue = rgbp;
      green = rgbp;
      aw(G, rgbp);
      aw(B, rgbp);
      aw(RELAY, rgbp > 0 ? 1 : 0);
      Serial.println("All RGB has change");
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("/temp", "hello world");
      // ... and resubscribe
      client.subscribe("/red");
      client.subscribe("/green");
      client.subscribe("/blue");
      client.subscribe("/relay");
      client.subscribe("/rgb");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pm(R, OUTPUT);
  pm(G, OUTPUT);
  pm(B, OUTPUT);
  pm(RELAY, OUTPUT);

  dw(R, LOW);
  dw(G, LOW);
  dw(B, LOW);
  dw(RELAY, LOW);

  dht.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
bool dht_toggle = true;
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    led["red"] =  red > 0 ? 1: 0;
    led["green"] = green > 0 ? 1 : 0;
    led["blue"] = blue > 0 ? 1 : 0;
    led["relay"] = dr(RELAY);
    serializeJson(led, buffer);
    client.publish("/rgb/status", buffer);

    if (dht_toggle) {
      dht_toggle = !dht_toggle;
      delay(1000);
      return;
    }
    dht_toggle = true;
    Serial.println("Publish message");
    doc["node_name"] = "node1";
    float h = dht.readHumidity();
    if (!isnan(h)) {
      doc["humidity"] = h;
      Serial.print("Humidity ");
      Serial.println(h);
      snprintf(msg, MSG_BUFFER_SIZE, "%.2f", h);
      client.publish("/humidity", msg);
    }
    float t = dht.readTemperature();
    if (!isnan(t)) {
      doc["temp"] = t;
      Serial.print("Temp ");
      Serial.println(t);
      snprintf(msg, MSG_BUFFER_SIZE, "%.2f", t);
      client.publish("/temp", msg);
    }
    serializeJson(doc, buffer);
    client.publish("/esp", buffer);
    delay(1000);
  }
}
