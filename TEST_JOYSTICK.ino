#include <Servo.h>

Servo servo;  // Vytvoření objektu pro servo
const int joystickPin = A0;  // Analogový pin pro osu X joysticku
const int servoPin = 9;      // Pin pro připojení serva

void setup() {
  servo.attach(servoPin);  // Připojení serva na definovaný pin
}

void loop() {
  int joystickValue = analogRead(joystickPin);  // Čtení hodnoty z joysticku (0-1023)
  
  // Mapování hodnoty joysticku (0-1023) na rozsah úhlů serva (0-180 stupňů)
  int servoAngle = map(joystickValue, 0, 1023, 0, 180);
  
  // Nastavení úhlu serva
  servo.write(servoAngle);
  
  delay(15);  // Malé zpoždění pro plynulé ovládání serva
}
