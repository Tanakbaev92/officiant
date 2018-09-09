
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

long START_TIME;

struct Task {
  Task (int duration, int action) {
    this->duration = duration;
    this->action = action;
  }
  int duration;
  int action;
};

void mapActions(int action) {
  switch (action) {
    case 1: 
      turn_left();
      break;
    case 2:
      turn_right();
      break;
    case 3:
      move_forward();
      break;
    case 4:
      move_backward();
      break;
    case 0:
      stop_moving();
      break;
  }
}

const int TIME_INTERVALS_COUNT = 4;
Task * tasksQueue[TIME_INTERVALS_COUNT] = {
  // new Task(duration, actionNumber);
  new Task(000, 2),
  new Task(000, 1),
  new Task(5000, 3),
  new Task(5000, 4),
};

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

void defineDirections(bool isLeft, bool isRight, bool isStop) {
  if (isStop) {
    digitalWrite (MotorLeftForward, LOW);
    digitalWrite (MotorLeftBackward, LOW);
    digitalWrite (MotorRightForward, LOW);
    digitalWrite (MotorRightBackward, LOW);

    return;
  }
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
  defineDirections(false, true, false);
  setSpeedToMotors();
}

void turn_right() {
  defineDirections(true, false, false);
  setSpeedToMotors();
}

void move_forward() {
  defineDirections(true, true, false);
  setSpeedToMotors();
}

void move_backward() {
  defineDirections(false, false, false);
  setSpeedToMotors();
}

void stop_moving() {
  defineDirections(false, false, true);
  setSpeedToMotors();
}

// узнать, в каком отрезке мы сейчас находимся, в любой момент времени

// какой номер действия вернуть, если время прошло
int getActionFromIndex(long time) { // 728, 10000 => 9 => 8 => 5 => 3
  int i = 0;
  while (time > 0 && i < TIME_INTERVALS_COUNT) {
    
    time = time - tasksQueue[i]->duration;
    i ++;
  }

  if (time > 0) {
    return 0;
  }

  int index = i - 1;

  if (index < 0) {
    return 0;
  }

  if (index > TIME_INTERVALS_COUNT) {
    return 0;
  }

  return tasksQueue[index]->action;
}

int getDistance() {
  long duration;
  
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  Serial.println((duration/2) / SOUND_SPEED);
  
  return (duration/2) / SOUND_SPEED;
}

int BlockTime = 0;
const int DELAY_TIME = 300;
const int BLOCK_DISTANCE = 50;

void loop() {
  delay(DELAY_TIME);

  if (getDistance() < BLOCK_DISTANCE) {
    
    BlockTime += DELAY_TIME;
    mapActions(0);

    return;
  }

  
  long time = millis() - BlockTime;
  int action = getActionFromIndex(time);

  mapActions(action);
}

