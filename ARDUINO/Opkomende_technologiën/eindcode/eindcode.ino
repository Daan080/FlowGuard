#include <Wire.h>
#include "rgb_lcd.h"

#define CLK 2   // Rotary Encoder CLK (A)
#define DT 3    // Rotary Encoder DT (B)
#define SW 4    // Rotary Encoder drukknop

rgb_lcd lcd;

volatile int totalSeconds = 0;  // Totale tijd in seconden
int lastEncoded = 0;         
bool timerRunning = false;
unsigned long countdownStart = 0;

void setup() {
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(CLK), readEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DT), readEncoder, CHANGE);

    lcd.begin(16, 2);
    lcd.setRGB(0, 255, 0);  // Groen bij instellen
    updateDisplay();
}

void loop() {
    if (!timerRunning) {
        updateDisplay();
        
        if (digitalRead(SW) == LOW) {  
            delay(200);  // Debounce
            if (totalSeconds > 0) {
                timerRunning = true;
                countdownStart = millis();
                lcd.setRGB(255, 0, 0); // Rood tijdens aftellen
            }
        }
    } 
    else {
        unsigned long elapsed = (millis() - countdownStart) / 1000;
        int remainingTime = totalSeconds - elapsed;

        if (remainingTime <= 0) {
            timerRunning = false;
            totalSeconds = 0;
            lcd.setRGB(0, 255, 0);  // Terug naar groen
            lcd.clear();
            lcd.print("Tijd voor pauze!");
            delay(2000);
            lcd.clear();
            updateDisplay();
        } 
        else {
            displayTime(remainingTime, "Time Left: ");
        }
    }
}

// Functie om de timer correct weer te geven in HH:MM:SS formaat
void updateDisplay() {
    displayTime(totalSeconds, "Set Timer: ");
}

// Functie om seconden om te zetten naar HH:MM:SS en weer te geven
void displayTime(int timeInSeconds, const char* label) {
    int hours = timeInSeconds / 3600;
    int minutes = (timeInSeconds % 3600) / 60;
    int seconds = timeInSeconds % 60;

    lcd.setCursor(0, 0);
    lcd.print(label);
    lcd.setCursor(0, 1);
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s  "); // Extra spatie om vorige cijfers te wissen
}

// Rotary Encoder uitlezen
void readEncoder() {
    int MSB = digitalRead(CLK);
    int LSB = digitalRead(DT);
    int encoded = (MSB << 1) | LSB;
    int sum = (lastEncoded << 2) | encoded;

    // Draaien met grotere stappen voor snellere instelling
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        totalSeconds += (totalSeconds < 3600) ? 10 : 60;  // <1u: +10s, anders +1m
    }
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        totalSeconds -= (totalSeconds <= 3600) ? 10 : 60;
    }

    totalSeconds = max(0, totalSeconds);  // Zorgt dat de tijd niet negatief wordt
    lastEncoded = encoded;
}