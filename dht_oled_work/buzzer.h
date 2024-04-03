void buz_setup() {
    pinMode(BUZ, OUTPUT);
    digitalWrite(BUZ, HIGH);
}

void buz_on() {
    digitalWrite(BUZ, LOW);
    delay(200);
    digitalWrite(BUZ, HIGH);
}
