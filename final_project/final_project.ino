#include "macro.h"

#define L1 26
#define L2 32
#define L3 33
#define L4 25
const char* node_name = "/node1";

char buffer[512];

const char* ssid = "UMR_Lab1";
const char* password = "Ubon2566";
const char* mqtt_server = "192.168.1.11";

WiFiClient espClient;

PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

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
  String topic_template = String(node_name) + "/led/";
  if (String(topic) == topic_template + "1") {
    digitalWrite(L1, payload[0] != '0' ? 1 : 0);
  } else if (String(topic) == topic_template + "2") {
    digitalWrite(L2, payload[0] != '0' ? 1 : 0);
  } else if (String(topic) == topic_template + "3") {
    digitalWrite(L3, payload[0] != '0' ? 1 : 0);
  } else if (String(topic) == topic_template + "4") {
    digitalWrite(L4, payload[0] != '0' ? 1 : 0);
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

      client.subscribe((String(node_name) + String("/led/1")).c_str());
      client.subscribe((String(node_name) + String("/led/2")).c_str());
      client.subscribe((String(node_name) + String("/led/3")).c_str());
      client.subscribe((String(node_name) + String("/led/4")).c_str());

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
  pm(L1, OUTPUT);
  pm(L2, OUTPUT);
  pm(L3, OUTPUT);
  pm(L4, OUTPUT);
  dw(L1, LOW);
  dw(L2, LOW);
  dw(L3, LOW);
  dw(L4, LOW);

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
  client.publish((String(node_name) + String("/led/1/status")).c_str(), String(dr(L1)).c_str());
  client.publish((String(node_name) + String("/led/2/status")).c_str(), String(dr(L2)).c_str());
  client.publish((String(node_name) + String("/led/3/status")).c_str(), String(dr(L3)).c_str());
  client.publish((String(node_name) + String("/led/4/status")).c_str(), String(dr(L4)).c_str());
}
