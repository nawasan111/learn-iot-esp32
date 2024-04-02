void light() {
  dw(R, HIGH);
  dw(G, HIGH);
  dw(B, HIGH);
}
void red() {
  dw(R, HIGH);
  dw(G, LOW);
  dw(B, LOW);
}

void yellow() {
  dw(R, HIGH);
  dw(G, HIGH);
  dw(B, LOW);
}

void blue() {
  dw(R, LOW);
  dw(G, LOW);
  dw(B, HIGH);
}

void green() {
  dw(R, LOW);
  dw(G, HIGH);
  dw(B, LOW);
}

void rgb_off() {
  dw(R, LOW);
  dw(G, LOW);
  dw(B, LOW);
}