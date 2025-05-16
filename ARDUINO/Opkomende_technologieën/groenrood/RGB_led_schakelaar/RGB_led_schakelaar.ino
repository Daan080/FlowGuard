const int switchPin = 2;  // pin schakelaar
const int redPin = 11;     // pin rood
const int greenPin = 10;  // pin groen

void setup() {
    pinMode(switchPin, INPUT_PULLUP);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

void loop() {
    int switchState = digitalRead(switchPin); // waarde schakelaar inlezen

    if (switchState == LOW) { // als schakelaar ingedrukt:
        digitalWrite(redPin, LOW);     // rood uit
        digitalWrite(greenPin, HIGH);  // groen aan
    } else {
        digitalWrite(redPin, HIGH);    // rood aan
        digitalWrite(greenPin, LOW);   // groen uit
    }
}
