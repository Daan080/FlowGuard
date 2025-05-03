#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int buttonGreen = 6; // groene knop
const int buttonRed  = 7; // rode knop

const unsigned int LIGHT_SOFT = 25; // zachte lichtsterkte
const unsigned int LIGHT_BRIGHT = 140; // felle lichtsterkte

void setup() {
  lcd.begin(16, 2); // lcd scherm opstarten
  lcd.setRGB(0, LIGHT_SOFT, 0); // backlight standaard op groen

  // Knoppen als input met pull-up
  pinMode(buttonGreen, INPUT_PULLUP);
  pinMode(buttonRed, INPUT_PULLUP);
}

void loop() {
  // Als knop 1 ingedrukt is, zet backlight groen
  if (digitalRead(buttonGreen) == LOW) {
    lcd.setRGB(0, LIGHT_SOFT, 0); // Groen
  }

  // Als knop 2 ingedrukt is, zet backlight rood
  if (digitalRead(buttonRed) == LOW) {
    lcd.setRGB(LIGHT_SOFT, 0, 0); // Rood
  }
}