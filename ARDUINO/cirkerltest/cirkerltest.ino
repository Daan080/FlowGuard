#include <Adafruit_NeoPixel.h>

#define LED_PIN 6         // Pin voor de LED Ring
#define NUM_LEDS 16       // Aantal LEDs in de ring (pas aan indien nodig)

#define potHelderheid A0  // Potentiometer voor helderheid
#define potKnipper A2     // Potentiometer voor knippersnelheid
#define schakelPin 2      // Schakelknop om flikkeren te starten

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool knipperModus = false;

void setup() {
    pinMode(schakelPin, INPUT_PULLUP); // Schakelknop met interne pull-up
    ring.begin();
    ring.show(); // Alle LEDs uit
}

void loop() {
    knipperModus = digitalRead(schakelPin) == LOW; // LOW = knipperen, HIGH = vasc:\Users\daand\OneDrive - UGent\2024-2025\project gebruiksgericht ontwerp\ARDUINO\helderheid_flikkerente kleur

    // Lees helderheid en knippersnelheid
    int helderheid = analogRead(potHelderheid);
    int ledBrightness = map(helderheid, 0, 1023, 0, 255);

    int knipperSnelheid = analogRead(potKnipper);
    int knipperDelay = map(knipperSnelheid, 0, 1023, 100, 1000); // 100ms - 1000ms

    if (knipperModus) {
        setRingColor(ledBrightness, 0, 0); // Rood licht aan
        delay(knipperDelay);
        setRingColor(0, 0, 0); // Licht uit (zwart)
        delay(knipperDelay);
    } else {
        setRingColor(ledBrightness, 0, 0); // Blijft constant rood
    }
}

// Functie om de kleur van alle LEDs in de ring in te stellen
void setRingColor(int r, int g, int b) {
    for (int i = 0; i < NUM_LEDS; i++) {
        ring.setPixelColor(i, ring.Color(r, g, b));
    }
    ring.show();
}