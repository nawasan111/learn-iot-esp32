#define R 16
#define G 17
#define RELAY 33

void rgb_init() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(RELAY, LOW);
}

void rgb_red_on() {
  digitalWrite(R, HIGH);
}

void rgb_red_off() {
  digitalWrite(R, LOW);
}

void rgb_green_on() {
  digitalWrite(G, HIGH);
}

void rgb_green_off() {
  digitalWrite(G, LOW);
}

void rgb_relay_on() {
  digitalWrite(RELAY, HIGH);
}

void rgb_relay_off() {
  digitalWrite(RELAY, LOW);
}

void rgb_red() {
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(RELAY, LOW);
}

void rgb_green() {
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(RELAY, LOW);
}

void rgb_relay() {
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(RELAY, HIGH);
}

void rgb_all() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(RELAY, HIGH);
}

void rgb_off() {
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(RELAY, LOW);
}
