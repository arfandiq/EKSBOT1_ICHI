const int ENA = 3;
const int ENB = 6;
const int IN1R = 2;
const int IN2R = 4;
const int IN3L = 5;
const int IN4L = 7;
const int s1 = A3;  // paling kiri
const int s2 = A4;  // kiri
const int s3 = A5;  // tengah
const int s4 = A1;  // kanan
const int s5 = A2;  // paling kanan

float kp = 45;
float ki = 0;
float kd = 0;
float interval = 100;
float old = 0;
float now;
float integral;
float previousError = 0;

int Err;
int previousTime;
int correction;
int SpeedR, SpeedL;
int BSpeedR = 150;
int BSpeedL = 175;
int LSpeed;
int RSpeed;
// motor kiri dilebihkan 25

bool ichistop = false;

void setup() {
  Serial.begin(9600);
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
}

int readErr() {
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
  return Err;
}

void Maju(int RSpeed, int LSpeed) {
  analogWrite(ENA, RSpeed);
  analogWrite(ENB, LSpeed);
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}

void Kiri(int RSpeed, int LSpeed) {
  analogWrite(ENA, RSpeed);
  analogWrite(ENB, LSpeed);
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
}

void Kanan(int RSpeed, int LSpeed) {
  analogWrite(ENA, RSpeed);
  analogWrite(ENB, LSpeed);
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}

void PIDBos() {
  unsigned long now = micros();
  if (now - previousTime >= interval) {
    int error = readErr();
    float proportional = kp * error;
    integral += error * (now - previousTime) / interval;
    float derivative = (error - previousError) / ((now - previousTime) / interval);

    int correction = proportional + ki * integral + kd * derivative;
    correction = constrain(correction, -255, 255);

    int LSpeed = BSpeedL + correction;
    int RSpeed = BSpeedR - correction;

    int LSpeed2 = BSpeedL + correction;
    int RSpeed2 = BSpeedR - correction;


    LSpeed = constrain(LSpeed, 205, 225);
    RSpeed = constrain(RSpeed, 180, 200);

    // LSpeed2 = constrain(LSpeed, 0, 150);
    // RSpeed2 = constrain(RSpeed, 0, 150);

    // int LSpeed3 = baseSpeed + correction;
    // int RSpeed3 = baseSpeed - correction;

    // LSpeed3 = constrain(LSpeed, 0, 150);
    // RSpeed3 = constrain(RSpeed, 0, 150);

    if (error == 0) {
      Maju(BSpeedR, BSpeedL);
    } else if (error == -2) {
      Kanan(140, 175);
    } else if (error == 2) {
      Kiri(150, 165);
    } else if (error == -1 || error == 1) {
      Maju(BSpeedR, BSpeedL);
      // Maju(RSpeed, LSpeed);
    }
  }
}


void loop() {
  PIDBos();
  // while (ichistop == false) {
  //   pidControl();
  //   if ((val1 == a && val2 == b && val3 == c && val4 == d && val5 == e) || (val2 == b && val3 == c && val4 == d && val5 == e) || (val1 == a && val2 == b && val3 == c && val4 == d)) {
  //     stopmotor = true;
  //     break;
  //   }
  // }
  // analogWrite(ENA, 0);
  // analogWrite(ENB, 0);
  // digitalWrite(IN1R, LOW);
  // digitalWrite(IN2R, HIGH);
  // digitalWrite(IN3L, LOW);
  // digitalWrite(IN4L, HIGH);
}
