int MotorLeftForward = 4; // Input3 подключен к выводу 5
int MotorLeftBackward = 5;
int MotorRightForward = 7;
int MotorRightBackward = 6;

int SpeedLeftPort = 1; //скорость левого
int SpeedRightPort = 2; //скорость правого

int echoPin = 11;
int trigPin = 10;
int echoPinL = 9;
int trigPinL = 8;
int echoPinR = 12;
int trigPinR = 3;

const float SOUND_SPEED = 29.1;
const int SPEED_RIGHT = 249;
const int SPEED_LEFT = 255;

void setup() {

  pinMode (MotorLeftForward, OUTPUT);
  pinMode (MotorLeftBackward, OUTPUT);
  pinMode (MotorRightForward, OUTPUT);
  pinMode (MotorRightBackward, OUTPUT);
  pinMode (SpeedRightPort, OUTPUT);
  pinMode (SpeedLeftPort, OUTPUT);
  Serial.begin (9600); // частота  обновления void loop
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

}

void setSpeedToMotors() {
  analogWrite(SpeedRightPort, SPEED_RIGHT);
  analogWrite(SpeedLeftPort, SPEED_LEFT);
}

void defineDirections(bool isLeft, bool isRight) {
  if (isLeft) {
    digitalWrite (MotorLeftForward, HIGH);
    digitalWrite (MotorLeftBackward, LOW);
  } else {
    digitalWrite (MotorLeftBackward, HIGH);
    digitalWrite (MotorLeftForward, LOW);
  }

  if (isRight) {
    digitalWrite (MotorRightForward, HIGH);
    digitalWrite (MotorRightBackward, LOW);
  } else {
    digitalWrite (MotorRightBackward, HIGH);
    digitalWrite (MotorRightForward, LOW);
  }
}

void turn_left() {
  defineDirections(false, true);
  setSpeedToMotors();
}

void turn_right() {
  defineDirections(true, false);
  setSpeedToMotors();
}

void move_forward() {
  defineDirections(true, true);
  setSpeedToMotors();
}

void move_backward() {
  defineDirections(false, false);
  setSpeedToMotors();
}


void loop() {
  const int DELAY_TIME = 500;
  turn_left();
  delay(DELAY_TIME);
  turn_right();
  delay(DELAY_TIME);
  move_forward();
  delay(DELAY_TIME);
  move_backward();
  delay(DELAY_TIME);

}
