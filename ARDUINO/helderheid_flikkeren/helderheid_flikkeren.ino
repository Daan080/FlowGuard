#include <Wire.h>
#include "rgb_lcd.h"


#define potHelderheid A0  // Potentiometer voor helderheid LCD
#define potKnipper A2     // Potentiometer voor knippersnelheid
#define schakelPin 2      // Schakelknop om flikkeren te starten

rgb_lcd lcd;
bool knipperModus = false;

void setup() {
    pinMode(schakelPin, INPUT_PULLUP); // Schakelknop met interne pull-up

    lcd.begin(16, 2);
    lcd.setRGB(255, 0, 0); // Start met rood licht
}

void loop() {
    knipperModus = digitalRead(schakelPin) == LOW; // LOW = knipperen, HIGH = vaste kleur

    // Lees helderheid en knippersnelheid
    int helderheid = analogRead(potHelderheid);
    int lcdBrightness = map(helderheid, 0, 1023, 0, 255);

    int knipperSnelheid = analogRead(potKnipper);
    int knipperDelay = map(knipperSnelheid, 0, 1023, 100, 1000); // 100ms - 1000ms

    // Weergave op LCD
    lcd.setCursor(0, 0);
    lcd.print("Snelheid: ");
    lcd.print(knipperDelay);
    lcd.print(" ms  "); // Wis oude waarden

    lcd.setCursor(0, 1);
    lcd.print("Lv: ");
    lcd.print(lcdBrightness);
    lcd.print("    "); // Wis oude waarden

    if (knipperModus) {
        lcd.setRGB(lcdBrightness, 0, 0); // Rood licht aan
        delay(knipperDelay);
        lcd.setRGB(0, 0, 0); // Licht uit (zwart)
        delay(knipperDelay);
    } else {
        lcd.setRGB(lcdBrightness, 0, 0); // Blijft constant rood
    }
}