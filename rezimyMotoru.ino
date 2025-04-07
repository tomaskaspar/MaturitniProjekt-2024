int in1 = 7;   // Pin pro směr otáčení motoru 1
int in2 = 6;   // Pin pro směr otáčení motoru 1
int in3 = 11;  // Pin pro směr otáčení motoru 2
int in4 = 12;  // Pin pro směr otáčení motoru 2
int enA = 10;  // PWM pin pro rychlost motoru 1
int enAA = 5;  // PWM pin pro rychlost motoru 2

int joystickPin = A1;  // Analogový pin pro joystick
int motorSpeed = 100;  // Výchozí rychlost motorů (v rozsahu 70-220)

// Tlačítka
int button1 = 2;
int button2 = 3;
int button3 = 4;

int stav1 = LOW;
int btnstatepred1;
int stav2 = LOW;
int btnstatepred2;
int stav3 = LOW;
int btnstatepred3;

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enAA, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
}

void loop() {
  int btnvalue1 = digitalRead(button1);  
  int btnvalue2 = digitalRead(button2); 
  int btnvalue3 = digitalRead(button3);

  if (btnvalue1 == LOW && btnstatepred1 == HIGH) {
    stav2 = LOW;
    stav3 = LOW;
    stav1 = !stav1;
    Serial.println(stav1);
  }

  if (btnvalue2 == LOW && btnstatepred2 == HIGH) {
    stav1 = LOW;
    stav3 = LOW;
    stav2 = !stav2;
    Serial.println(stav2);
  }

  if (btnvalue3 == LOW && btnstatepred3 == HIGH) {
    stav2 = LOW;
    stav1 = LOW;
    stav3 = !stav3;
    Serial.println(stav3);
  }

  int joystickValue = analogRead(joystickPin);

  if (joystickValue > 600) {
    motorSpeed += 5;
    if (motorSpeed > 220) motorSpeed = 225;
  } else if (joystickValue < 400) {
    motorSpeed -= 5;
    if (motorSpeed < 40) motorSpeed = 40;
  }

  if (stav1 == HIGH) {
    sameDirection();
  } else if (stav2 == HIGH) {
   
    reverseMotor1();
  } else if (stav3 == HIGH) {
    reverseMotor2();
  } else {
    stopMotors();
  }

  btnstatepred1 = btnvalue1;
  btnstatepred2 = btnvalue2;
  btnstatepred3 = btnvalue3;
  delay(100);
}

void sameDirection() {
  Serial.println("Motory se točí stejným směrem");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enAA, motorSpeed);
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void reverseMotor1() {
  Serial.println("Motor 1 opačný směr");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enAA, max(motorSpeed - 30, 40));
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void reverseMotor2() {
  Serial.println("Rotace dolů, levý motor z pohledu kratší strany");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, max(motorSpeed - 30, 40));
  analogWrite(enAA, motorSpeed);
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void stopMotors() {
  Serial.println("Motory zastaveny");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enAA, 0);
}
