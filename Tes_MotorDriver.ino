#define ENA 3
#define ENB 6
#define IN1R 2
#define IN2R 4
#define IN3L 5
#define IN4L 7
#define s1 A3  // paling kiri
#define s2 A4  // kiri
#define s3 A5  // tengah
#define s4 A1  // kanan
#define s5 A2  // paling kanan

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);
  pinMode(IN3L, OUTPUT);
  pinMode(IN4L, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ENA, 110); //Atur PWM Motor Kanan
  analogWrite(ENB, 110); //Atur PWM Motor Kiri

  //Motor Kanan Maju
  digitalWrite(IN1R, HIGH); 
  digitalWrite(IN2R, LOW);

  //Motor Kiri Maju
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);

  
}
