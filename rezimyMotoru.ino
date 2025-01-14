int in1 = 7;   // Pin pro směr otáčení motoru 1
int in2 = 6;   // Pin pro směr otáčení motoru 1
int in3 = 11;  // Pin pro směr otáčení motoru 2
int in4 = 12;  // Pin pro směr otáčení motoru 2
int enA = 10;  // PWM pin pro rychlost motoru 1
int enAA = 5;  // PWM pin pro rychlost motoru 2

int joystickPin = A1;  // Analogový pin pro joystick
int motorSpeed = 100;  // Výchozí rychlost motorů (v rozsahu 70-220)

// Tlačítka
int button1 = 2; // První tlačítko
int button2 = 3; // Druhé tlačítko
int button3 = 4; // Třetí tlačítko

int stav1 = LOW; // První tlačítko
int btnstatepred1;// První tlačítko

int stav2 = LOW; // Druhe tlačítko
int btnstatepred2;// Druhe tlačítko

int stav3 = LOW; // Druhe tlačítko
int btnstatepred3;// Druhe tlačítko


void setup() {
  // Nastavení pinů jako výstupy
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enAA, OUTPUT);

  // Nastavení pinů pro tlačítka jako vstupy
  pinMode(button1, INPUT_PULLUP); // Aktivní při spojení s GND
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);


}

void loop() {
  Serial.begin(9600);
  //tlacitka stavy
  int btnvalue1 = digitalRead(button1);  
  int btnvalue2 = digitalRead(button2); 
  int btnvalue3 = digitalRead(button3);
  if (btnvalue1 == LOW && btnstatepred1 == HIGH) {
      stav2=LOW;
      stav3=LOW;
      stav1 = !stav1;
      Serial.println(stav1);
    }

   if (btnvalue2 == LOW && btnstatepred2 == HIGH) {
      stav1 =LOW;
      stav3 =LOW;
      stav2 = !stav2;
     
      Serial.println(stav2);
    }

     if (btnvalue3 == LOW && btnstatepred3 == HIGH) {
      stav2=LOW;
      stav1=LOW;
      stav3 = !stav3;
      Serial.println(stav3);
    }

    

  // Čtení hodnoty joysticku
  int joystickValue = analogRead(joystickPin);

  // Výpočet rychlosti motorů na základě joysticku
  if (joystickValue > 600) {
    motorSpeed += 5;
    if (motorSpeed > 220) motorSpeed = 220; // Max rychlost 220
  } else if (joystickValue < 400) {
    motorSpeed -= 5;
    if (motorSpeed < 40) motorSpeed = 40; // Min rychlost 70
  }

  // Kontrola stavu tlačítek
  if (stav1 == HIGH) {
    sameDirection();
  } else if (stav2 == HIGH) {
    delay(2000); // Pauza 2 sekundy
    reverseMotor1();
  } else if (stav3== HIGH) {
    reverseMotor2();
  } 
  
  //Motory zastaveny
  else {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, 0);
  analogWrite(enAA, 0);

  Serial.println("Motory zastaveny");
  }

  
  btnstatepred1 = digitalRead(button1);
    btnstatepred2 = digitalRead(button2);
      btnstatepred3 = digitalRead(button3);
  delay(100); // Krátké zpoždění
}

// Funkce pro stejný směr motorů
void sameDirection() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, motorSpeed);
  analogWrite(enAA, motorSpeed);

  Serial.println("Motory se točí stejným směrem");
}

// Funkce pro opačný směr motoru 1
void reverseMotor1() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

analogWrite(enA, motorSpeed);
analogWrite(enAA, max(motorSpeed - 30, 0)); 

  Serial.println("Motor 1 opačný směr");
}

// Funkce pro opačný směr motoru 2
void reverseMotor2() {
    Serial.println("Rotace dolu,levy motor z pohledu kratsi strany");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
    analogWrite(enA, max(motorSpeed - 30, 0)); // Zajištění minimální hodnoty 0
    analogWrite(enAA, motorSpeed);
  }
