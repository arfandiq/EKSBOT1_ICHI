#define ENA 3 //kanna
#define ENB 6 //kiri
#define IN1R 2
#define IN2R 4
#define IN3L 5
#define IN4L 7
#define s1 A3  // paling kiri
#define s2 A4  // kiri
#define s3 A5  // tengah
#define s4 A1  // kanan
#define s5 A2  // paling kanan

int Err;
void maju() {
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}
void kanan() {
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
}
void kiri() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}
void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, LOW);
}
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);
  pinMode(IN3L, OUTPUT);
  pinMode(IN4L, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  Serial.begin(9600);
}


void readErr() {
  // 0 ngebaca hitam && 1 ngebaca putih
  int sr1 = digitalRead(s1);
  int sr2 = digitalRead(s2);
  int sr3 = digitalRead(s3);
  int sr4 = digitalRead(s4);
  int sr5 = digitalRead(s5);

  // ngatur error sensor
  // (-) sensor kanan, (+) sensor kiri
  if (sr3 == 0) {
    Err = 0;
  } else if (sr4 == 0 || sr2 == 0) {
    if (sr4 == 0) {
      Err = -1;
    } else if (sr2 == 0) {
      Err = 1;
    }
  } else if (sr5 == 0 || sr1 == 0) {
    if (sr5 == 0) {
      Err = -2;
    } else if (sr1 == 0) {
      Err = 2;
    }
  }

  Serial.print("Error = ");
  Serial.println(Err);
}

void motor(int speedR, int speedL) {
  if (speedR > 0) {
    analogWrite(ENA, speedR);
    digitalWrite(IN1R, HIGH);
    digitalWrite(IN2R, LOW);
  } else if (speedR < 0) {
    analogWrite(ENA, -speedR);
    digitalWrite(IN1R, LOW);
    digitalWrite(IN2R, HIGH);
  } else {
    analogWrite(ENA, 0);
    digitalWrite(IN1R, LOW);
    digitalWrite(IN2R, LOW);
  }

  if (speedL > 0) {
    analogWrite(ENB, speedL);
    digitalWrite(IN3L, HIGH);
    digitalWrite(IN4L, LOW);
  } else if (speedL < 0) {
    analogWrite(ENB, -speedL);
    digitalWrite(IN3L, LOW);
    digitalWrite(IN4L, HIGH);
  } else {
    analogWrite(ENB, 0);
    digitalWrite(IN3L, LOW);
    digitalWrite(IN4L, LOW);
  }
}


void loop() {
  readErr();
  if (Err == 0) {
    motor(170, 195);
  } else if (Err == 1) {
    motor(170, 215);
  } else if (Err == 2) {
    motor(170, -215);
  } else if (Err == -1) {
    motor(190, 195);
  } else if (Err == -2) {
    motor(-190, 195);
  }

  // readErr();
  // if (Err == 0) {
  //   motor(190, 205);
  // } else if (Err == 1) {
  //   motor(150, 195);
  // } else if (Err == 2) {
  //   motor(150, -195);
  // } else if (Err == -1) {
  //   motor(170, 175);
  // } else if (Err == -2) {
  //   motor(-170, 175);
  // }

  // readErr();
  // if (Err == 0) {
  //   motor(190, 215);
  // } else if (Err == 1) {
  //   motor(190, 235);
  // } else if (Err == 2) {
  //   motor(190, -235);
  // } else if (Err == -1) {
  //   motor(210, 215);
  // } else if (Err == -2) {
  //   motor(-210, 215);
  // }
}
