


int in1 = 7;  // Pin pro směr otáčení
int in2 = 6;  // Pin pro směr otáčení
int in3 = 11;  // Pin pro směr otáčení
int in4 = 12;  // Pin pro směr otáčení
int enA = 10; // PWM pin pro rychlost (enable pin)
int enAA= 5; // PWM pin pro rychlost 
void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enAA, OUTPUT);


}

void loop() {


  
 
  // put your main code here, to run repeatedly:

  // Motor se točí jedním směrem
    digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  
  // Nastav rychlost motoru na 50 % (PWM hodnota 0 - 255)
    analogWrite(enA, 50);
   analogWrite(enAA, 60);
  delay(2000); // Běží 2 sekundy

  // Zastavení motoru
    digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  delay(2000);
  

}
