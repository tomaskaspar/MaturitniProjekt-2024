#include <Servo.h>

// --- Piny pro motory ---
int in1 = 7;
int in2 = 6;
int in3 = 11;
int in4 = 12;
int enA = 10;
int enAA = 5;

// --- Piny pro servo ---
Servo myservo;
int servoPin = 8;
int servoPos = 0;
bool servoUp = true;
unsigned long lastServoUpdate = 0;

// --- Joysticky a tlačítka ---
int joystickMotorPin = A1;
int joystickServoPin = A2;
int joystickServoBtn = 9;

int button1 = 2;  // Motor režim 1
int button2 = 3;  // Motor režim 2
int button3 = 4;  // Motor režim 3

int button4 = 51;  // Servo automat
int button5 = 47;  // Servo joystick

// --- Stavy ---
int motorSpeed = 100;
int stav1 = LOW, btnStatePrev1;
int stav2 = LOW, btnStatePrev2;
int stav3 = LOW, btnStatePrev3;
bool servoAuto = false;
bool servoJoy = false;

void setup() {
  Serial.begin(9600);

  // Motory
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enAA, OUTPUT);

  // Tlačítka
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(joystickServoBtn, INPUT_PULLUP);

  // Servo
  myservo.attach(servoPin);
  myservo.write(90);  // výchozí pozice
}

void loop() {
  // --- Režimy motorů ---
  int btn1 = digitalRead(button1);
  int btn2 = digitalRead(button2);
  int btn3 = digitalRead(button3);

  if (btn1 == LOW && btnStatePrev1 == HIGH) {
    stav1 = !stav1;
    stav2 = stav3 = LOW;
    Serial.println("Režim: Motory stejné směr");
  }
  if (btn2 == LOW && btnStatePrev2 == HIGH) {
    stav2 = !stav2;
    stav1 = stav3 = LOW;
    Serial.println("Režim: Motor 1 opačný směr");
  }
  if (btn3 == LOW && btnStatePrev3 == HIGH) {
    stav3 = !stav3;
    stav1 = stav2 = LOW;
    Serial.println("Režim: Motor 2 opačný směr");
  }

  // Rychlost motorů joystickem
  int joyMotor = analogRead(joystickMotorPin);
  if (joyMotor > 600) {
    motorSpeed = min(motorSpeed + 5, 225);
  } else if (joyMotor < 400) {
    motorSpeed = max(motorSpeed - 5, 40);
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

  // --- Servo režimy ---
  if (digitalRead(button4) == LOW) {
    delay(50);
    servoAuto = !servoAuto;
    servoJoy = false;
    Serial.print("Servo režim: Automatický = "); Serial.println(servoAuto);
    while (digitalRead(button4) == LOW);
  }

  if (digitalRead(button5) == LOW) {
    delay(50);
    servoJoy = !servoJoy;
    servoAuto = false;
    Serial.print("Servo režim: Joystick = "); Serial.println(servoJoy);
    while (digitalRead(button5) == LOW);
  }

  if (servoAuto) {
    if (millis() - lastServoUpdate >= 30) {
      lastServoUpdate = millis();
      if (servoUp) {
        servoPos++;
        if (servoPos >= 180) servoUp = false;
      } else {
        servoPos--;
        if (servoPos <= 0) servoUp = true;
      }
      myservo.write(servoPos);
      Serial.print("Servo AUTO pozice: "); Serial.println(servoPos);
    }
  }

  if (servoJoy) {
    if (digitalRead(joystickServoBtn) == LOW) {
      int joyVal = analogRead(joystickServoPin);
      int angle = map(joyVal, 0, 1023, 0, 180);
      myservo.write(angle);
      Serial.print("Servo JOY pozice: "); Serial.println(angle);
    }
  }

  // Výchozí pozice serva
  if (!servoAuto && !servoJoy) {
    myservo.write(90);
  }

  btnStatePrev1 = btn1;
  btnStatePrev2 = btn2;
  btnStatePrev3 = btn3;

  delay(100);
}

// --- Funkce motorů ---
void sameDirection() {
  Serial.println("Bez rotace");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, motorSpeed);
  analogWrite(enAA, motorSpeed);
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void reverseMotor1() {
   Serial.println("Zpětná rotace");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, max(motorSpeed - 50, 40));
  analogWrite(enAA, motorSpeed);
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void reverseMotor2() {
   Serial.println("Zpětná rotace");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, max(motorSpeed - 50, 40));
  analogWrite(enAA, motorSpeed);
  Serial.print("motorSpeed: ");
  Serial.println(motorSpeed);
}

void stopMotors() {
  Serial.println("Motory zastaveny");
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enAA, 0);
}
