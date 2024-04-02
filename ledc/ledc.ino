void setup() {
  // ledcSetup(ledChanal, freq, resolution);
  // reso = 8bit
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);

  ledcAttachPin(23, 0); // B
  ledcAttachPin(19, 1); // G 
  ledcAttachPin(18, 2); // R
}

void loop() {
    // ledcWrite(0, 50);
    // delay(1000);
    ledcWrite(0, 255);
    ledcWrite(1, 91);
    ledcWrite(2, 203);

    delay(1000);
}