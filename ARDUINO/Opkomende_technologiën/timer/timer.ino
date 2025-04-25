#include <Wire.h>
#include "rgb_lcd.h"

// Rotary Encoder pinnen
#define CLK 2
#define DT 3

// LCD setup
rgb_lcd lcd;

// Tijd in seconden (max bijv. 99u 59m 59s = 359999 seconden)
volatile unsigned long totalSeconds = 0;
int lastEncoded = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLK), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), readEncoder, CHANGE);

  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 0); // Licht UIT tijdens instellen
  updateDisplay();
}

void loop() {
  // Regelmatig display updaten (je kunt hier evt. vertraging of check op verandering toevoegen)
  updateDisplay();
  delay(200); // Display update-interval
}

// Functie: rotary encoder uitlezen (alleen tijd bijstellen)
void readEncoder() {
  int MSB = digitalRead(CLK);
  int LSB = digitalRead(DT);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  // Rechtsom
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    if (totalSeconds < 3600) totalSeconds += 10;   // <1u: stappen van 10s
    else totalSeconds += 60;                       // ≥1u: stappen van 1m
  }

  // Linksom
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    if (totalSeconds <= 3600 && totalSeconds >= 10) totalSeconds -= 10;
    else if (totalSeconds > 3600 && totalSeconds >= 60) totalSeconds -= 60;
  }

  if (totalSeconds < 0) totalSeconds = 0;
  lastEncoded = encoded;
}

// Functie: tijd tonen in HH:MM:SS
void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Set Timer:");

  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;

  lcd.setCursor(0, 1);
  if (hours < 10) lcd.print("0");
  lcd.print(hours); lcd.print("h ");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes); lcd.print("m ");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds); lcd.print("s  ");
}