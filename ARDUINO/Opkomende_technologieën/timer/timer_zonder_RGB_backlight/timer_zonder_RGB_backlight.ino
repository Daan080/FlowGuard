// libraries
#include <Wire.h> // indirect gebruikt via rgb_ldc
#include "rgb_lcd.h" // aansturen van rbd lcd scherm
#include <Encoder.h> // aansturen van rotary encoder

// pinnen
const int CLK = 2; // clock pin rotary encoder
const int DT = 3; // data pin rotary encoder
const int SW = 4; // switch pin rotary encoder

// naamgeving hardware
rgb_lcd lcd; // rgb lcd scherm benoemen
Encoder RotEnc(CLK, DT); // rotary encoder benoemen

// statussen timer
volatile unsigned long totalSeconds = 0; // totaal aantal seconden
unsigned long lastInteractionTime = 0; // tijdstip van laatste interactie met encoder of switch
long lastEncPos = 0; // positie van laatste encoder-lezing
bool timerRunning = false; // timer staat stil
bool timerFinished = false; // timer is niet afgelopen
bool BacklightOn = false; // backlight staat uit

// constanten
const unsigned int LIGHT_SOFT = 25; // zachte lichtsterkte
const unsigned int LIGHT_BRIGHT = 140; // felle lichtsterkte
const unsigned int BLINK_SPEED = 530; // flikkersnelheid in ms
const unsigned long BACKLIGHT_DELAY = 7000; // tijd dat RGB aanblijft in ms, moet long zijn want moet compatibel zijn met millis()

void setup() {
  pinMode(SW, INPUT_PULLUP); // drukknop activeren
  lcd.begin(16, 2); // lcd tekst activeren
  displayTime(totalSeconds); // lcd tijd weergeven
  lcd.setRGB(0, LIGHT_SOFT, 0); // rgb backlight op zacht groen
  lastEncPos = RotEnc.read(); // stand encoder lezen
}

void loop() {
  Encoder(); // encoder inlezen en tijd verhogen of verlagen
  Switch(); // switch inlezen en tijd starten of stoppen
  Timer(); // tijd laten aflopen per seconde en stoppen bij 0
  Blink(); // flikkeren van de tijd en backlight wanneer nodig
  BacklightOff(); // vanzelf uitzetten backlight na bepaalde delay
  delay(5);
}

void Encoder() {
  long newEncPos = RotEnc.read() / 4;
  long diff = lastEncPos - newEncPos;

  if (diff != 0) { // werkt enkel als er gedraaid wordt
    if (!timerRunning) { // als timer stilstaat
      unsigned long step = getStepSize(); // stapgrootte wordt bepaald

      if (diff > 0) { // als naar rechts gedraaid wordt
        if (totalSeconds % step != 0) { // als de tijd geen veelvoud is van de stapgrootte
          totalSeconds = ((totalSeconds / step) + 1) * step; // eerst tijd naar boven afronden
        } else {
          totalSeconds += step; // anders gewoon stap bijtellen
        }

        if (totalSeconds > 359999) totalSeconds = 359999; // maximum van 99:59:59

      } else { // als naar links gedraaid wordt
        if (totalSeconds % step != 0) { // als de tijd geen veelvoud is van de stapgrootte
          totalSeconds = (totalSeconds / step) * step; // eerst tijd naar onder afronden
        } else {
          if (totalSeconds >= step) {
            totalSeconds -= step; // anders gewoon stap aftrekken
          } else {
            totalSeconds = 0; // minimum van 00:00:00
          }
        }
      }

      displayTime(totalSeconds); // nieuwe tijd weergeven op lcd scherm
      lastInteractionTime = millis(); // laatste interactietijd updaten om backlight aan te houden
      lcd.setRGB(0, LIGHT_SOFT, 0); // rgb backlight op zacht groen (stilstaande tijd zichtbaar maken om in te stellen)
      BacklightOn = true; // backlight staat aan
      timerFinished = false; // indien tijd ingesteld nadat timer afgelopen was, bool updaten naar niet meer finished

    } else { // als timer loopt
      lastInteractionTime = millis(); // laatste interactietijd updaten om backlight vanzelf uit te schakelen
      if (!BacklightOn) { // als de backlight nog niet aanstond
        lcd.setRGB(0, LIGHT_SOFT, 0); // rgb backlight op zacht groen (lopende tijd kort zichtbaar maken bij draaien aan encoder)
        BacklightOn = true; // backlight staat aan
      }
    }
  }

  lastEncPos = newEncPos; // positie van laatste encoder-lezing updaten
}

void Switch() {
  static bool lastPress = HIGH; // laatste indrukking staat standaard op niet ingedrukt
  bool newPress = digitalRead(SW); // switch inlezen

  if (lastPress == HIGH && newPress == LOW) { // als knop ingedrukt wordt
    if (timerRunning) { // als timer loopt
      timerRunning = false; // timer staat stil
      lcd.setRGB(0, LIGHT_SOFT, 0); // rgb backlight op zacht groen
      BacklightOn = true; // backlight staat aan
    } else { // als timer stilstaat
      if (totalSeconds > 0) { // als tijd groter is dan 00:00:00
        timerRunning = true; // timer loopt
        lastInteractionTime = millis(); // laatste interactietijd updaten om backlight vanzelf uit te schakelen
      }
    }
  }
  lastPress = newPress; // indrukstatus updaten
}

void Timer() {
  static unsigned long lastTick = 0; // laatste tick is in het begin 0
  if (timerRunning && millis() - lastTick >= 1000) { // als er 1 seconde gepasseerd is
    lastTick = millis(); // laatste tick updaten
    if (totalSeconds > 0) { // als timer nog niet afgelopen is
      totalSeconds--; // 1 seconde aftrekken
      displayTime(totalSeconds); // nieuwe tijd weergeven op lcd scherm
    }
    if (totalSeconds == 0) { // als timer afgelopen is
      timerRunning = false; // timer staat stil
      timerFinished = true; // timer is afgelopen
      BacklightOn = true; // backlight staat aan
    }
  }
}

void Blink() {
  if (timerRunning && !timerFinished) { // als timer loopt en nog niet afgelopen is
    return; // niet flikkeren
  }

  static unsigned long lastBlink = 0; // laatste flikkerstatus is in het begin 0
  static bool visible = true; // tijd is zichtbaar op scherm

  if (millis() - lastBlink >= BLINK_SPEED) { // als flikkerinterval is overschreden
    lastBlink = millis(); // laatste flikkerstatus updaten
    visible = !visible; // tijd is niet zichtbaar op scherm

    if (visible) { // als tijd zichtbaar is op scherm
      displayTime(totalSeconds); // tijd weergeven op lcd scherm
      if (timerFinished) { // als tijd afgelopen is
        lcd.setRGB(0, LIGHT_BRIGHT, 0); // rgb backlight op fel groen
      }
    } else { // als tijd niet zichtbaar is op scherm
      lcd.setCursor(4, 1);
      lcd.print("        "); // lege tekst weergeven op lcd scherm
      if (timerFinished) { // als tijd afgelopen is
        lcd.setRGB(0, 0, 0); // rgb backlight uit
      }
    }
  }
}

void BacklightOff() {
  if (timerRunning && BacklightOn && millis() - lastInteractionTime >= BACKLIGHT_DELAY) { // als de tijd loopt en de backlight al voor een bepaalde tijd aanstaat
    lcd.setRGB(0, 0, 0); // rgb backlight uit
    BacklightOn = false; // rgb backlight uit
  }
}

unsigned long getStepSize() { // stapgrootte bepalen afhankelijk van totalSeconds
  if (totalSeconds < 10 * 60) return 30;
  else if (totalSeconds < 30 * 60) return 60;
  else if (totalSeconds < 60 * 60) return 300;
  else return 900;
}

void displayTime(unsigned long seconds) { // totalSeconds omzetten naar HH:MM:SS
  int h = seconds / 3600; // HH
  int m = (seconds % 3600) / 60; // MM
  int s = seconds % 60; // SS

  char timeArray[9]; // ketting van 8 tekens
  sprintf(timeArray, "%02d:%02d:%02d", h, m, s); // ketting vullen met tijd
  lcd.setCursor(4, 1);
  lcd.print(timeArray); // lcd scherm print ketting
}
