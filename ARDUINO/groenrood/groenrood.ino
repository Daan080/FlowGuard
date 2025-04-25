int sensorPin = A0;   // select the input pin for the potentiometer
int ledRood = 5;
int ledGroen = 3;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  pinMode(ledRood, OUTPUT);
  pinMode(ledGroen, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  Serial.println(sensorValue);
  
  if (0 < sensorValue < 20) {
    Serial.println("rood");
    digitalWrite(ledRood, HIGH);
    digitalWrite(ledGroen, LOW);
  }
  if (20 <= sensorValue <= 1000) {
    Serial.println("uit");
    digitalWrite(ledRood, LOW);
    digitalWrite(ledGroen, LOW);
  }
  if (1000 < sensorValue < 1050) {
    Serial.println("groen");
    digitalWrite(ledRood, LOW);
    digitalWrite(ledGroen, HIGH);
  }
  delay(100);
}
