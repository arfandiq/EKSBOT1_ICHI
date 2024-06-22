#define s1 A3  // paling kiri
#define s2 A4  // kiri
#define s3 A5  // tengah
#define s4 A1  // kanan
#define s5 A2  // paling kanan
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int sv1 = digitalRead(s1);
  int sv2 = digitalRead(s2);
  int sv3 = digitalRead(s3);
  int sv4 = digitalRead(s4);
  int sv5 = digitalRead(s5);

  Serial.print("Sensor 1 : ");
  Serial.println(sv1);
  Serial.print("Sensor 2 : ");
  Serial.println(sv2);
  Serial.print("Sensor 3 : ");
  Serial.println(sv3);
  Serial.print("Sensor 4 : ");
  Serial.println(sv4);
  Serial.print("Sensor 5 : ");
  Serial.println(sv5);

  delay(1000);

  //870 maks putih
  //125 maks hitam

  //hitam = 50 - 150
  //putih = 800 - 920


}