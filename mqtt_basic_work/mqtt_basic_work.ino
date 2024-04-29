#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#define dw(p, m) digitalWrite(p, m)
#define dr(p) digitalRead(p)
#define pm(p, m) pinMode(p, m)
#define R 18
#define G 19
#define B 23
#define RELAY 33
// Update these with values suitable for your network.

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
int value = 0;

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
  Serial.println("topic action");
  if (String(topic) == "/red") {
    dw(R, payload[0] == '1' ? 1 : 0);
    Serial.println("Red has change");
  } else if (String(topic) == "/green") {
    dw(G, payload[0] == '1' ? 1 : 0);
    Serial.println("Green has change");
  } else if (String(topic) == "/blue") {
    dw(B, payload[0] == '1' ? 1 : 0);
    Serial.println("Red has change");
  } else if (String(topic) == "/relay") {
    dw(RELAY, payload[0] == '1' ? 1 : 0);
    Serial.println("Relay has change");
  } else if (String(topic) == "/rgb") {
    dw(R, payload[0] == '1' ? 1 : 0);
    dw(G, payload[0] == '1' ? 1 : 0);
    dw(B, payload[0] == '1' ? 1 : 0);
    dw(RELAY, payload[0] == '1' ? 1 : 0);
    Serial.println("All RG has change");
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

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    Serial.println("Publish message");
    float h = dht.readHumidity();
    if (!isnan(h)) {
      Serial.print("Humidity ");
      Serial.println(h);
      snprintf(msg, MSG_BUFFER_SIZE, "%.2f", h);
      client.publish("/humidity", msg);
    }
    float t = dht.readTemperature();
    if (!isnan(t)) {
      Serial.print("Temp ");
      Serial.println(t);
      snprintf(msg, MSG_BUFFER_SIZE, "%.2f", t);
      client.publish("/temp", msg);
    }
    delay(2000);
  }
}
