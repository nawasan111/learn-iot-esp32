#define R 16 
#define G 17

void rgb_init() {
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);

    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
}