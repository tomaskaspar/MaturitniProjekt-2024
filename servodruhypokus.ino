#include <Servo.h>  // Zahrnutí knihovny pro ovládání servo motoru 

Servo myservo;         // Servo objekt
int pos = 0;          // Aktuální úhel serva
bool movingUp = true; // Směr pohybu serva
unsigned long lastUpdate = 0; // Čas poslední aktualizace serva

int button1 = 51;  // První tlačítko
int button2 = 47; // Druhé tlačítko
int joystickPin = A2;
int joystickButton = 9;

bool stav1 = false; // Stav prvního tlačítka (automatický režim)
bool stav2 = false; // Stav druhého tlačítka (joystick režim)

void setup() {
  myservo.attach(8);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(joystickButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Čtení stavu tlačítek
  if (digitalRead(button1) == LOW) {
    delay(50); // Debounce
    stav2 = false; // Vypne druhý režim
    stav1 = !stav1; // Přepne první režim
    Serial.print("Automatický režim: "); Serial.println(stav1);
    while (digitalRead(button1) == LOW); // Počká na uvolnění tlačítka
  }

  if (digitalRead(button2) == LOW) {
    delay(50);
    stav1 = false; // Vypne první režim
    stav2 = !stav2; // Přepne druhý režim
    Serial.print("Joystick režim: "); Serial.println(stav2);
    while (digitalRead(button2) == LOW);
  }

  // Automatický režim serva (bez blokování)
  if (stav1) {
    if (millis() - lastUpdate >= 15) { // Aktualizace každých 15 ms
      lastUpdate = millis();
      
      if (movingUp) {
        pos++;
        if (pos >= 180) movingUp = false;
      } else {
        pos--;
        if (pos <= 0) movingUp = true;
      }

      myservo.write(pos);
    }
  }

  // Joystick režim serva
  if (stav2) {
    if (digitalRead(joystickButton) == LOW) { // Přepne pouze při stisku tlačítka
      int joystickValue = analogRead(joystickPin);
      int servoAngle = map(joystickValue, 0, 1023, 0, 180);
      myservo.write(servoAngle);
    }
  }

  // Pokud žádný režim není aktivní, vrátí servo do výchozí polohy
  if (!stav1 && !stav2) {
    myservo.write(90);
  }
}
