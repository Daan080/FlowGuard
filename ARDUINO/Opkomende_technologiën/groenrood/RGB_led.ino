const int switchPin = 2;  // De pin waarop de schakelaar is aangesloten
const int redPin = 11;     // De rode pin van de RGB-LED
const int greenPin = 10;  // De groene pin van de RGB-LED

void setup() {
    pinMode(switchPin, INPUT_PULLUP); // Schakelaar met interne pull-up weerstand
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

void loop() {
    int switchState = digitalRead(switchPin); // Lees de stand van de schakelaar

    if (switchState == LOW) { // Als de schakelaar wordt ingedrukt
        digitalWrite(redPin, LOW);     // Rood uit
        digitalWrite(greenPin, HIGH);  // Groen aan
    } else {
        digitalWrite(redPin, HIGH);    // Rood aan
        digitalWrite(greenPin, LOW);   // Groen uit
    }
}
