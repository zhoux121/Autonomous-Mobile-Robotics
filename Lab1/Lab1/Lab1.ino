#define PIN_Motor_AIN 8
#define PIN_Motor_BIN 7
#define PIN_Motor_PWMA 9
#define PIN_Motor_PWMB 6
#define PIN_Motor_STBY 4

void setup()
{
  pinMode(PIN_Motor_AIN, OUTPUT);
  pinMode(PIN_Motor_BIN, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  Serial.println("Froward");
}



void turn_right()
{
  digitalWrite(PIN_Motor_BIN, LOW);
  analogWrite(PIN_Motor_PWMB, 100);
  digitalWrite(PIN_Motor_AIN, LOW);
  analogWrite(PIN_Motor_PWMA, 100);
}

void turn_left()
{
  digitalWrite(PIN_Motor_BIN, HIGH);
  analogWrite(PIN_Motor_PWMB, 100);
  digitalWrite(PIN_Motor_AIN, HIGH);
  analogWrite(PIN_Motor_PWMA, 100);
}

void forward()
{
  digitalWrite(PIN_Motor_AIN, HIGH);
  analogWrite(PIN_Motor_PWMA, 100);
  digitalWrite(PIN_Motor_BIN, LOW);
  analogWrite(PIN_Motor_PWMB, 100);
}

void stop()
{
  analogWrite(PIN_Motor_PWMA, 0);
  analogWrite(PIN_Motor_PWMB, 0);
}

void rount_one()
{ 
  forward();
  delay(6100);
  
  stop();
  delay(100);
  turn_right();
  delay(600);

  forward();
  delay(6100);

  stop();
  delay(100);
  turn_right();
  delay(600);

  forward();
  delay(6100);

  stop();
  delay(100);
  turn_right();
  delay(600);

  forward();
  delay(6100);

  stop();
  delay(100);
  turn_right();
  delay(600);
}


void loop()
{
  stop();
  rount_one();
  rount_one();
  rount_one();

  stop();
  delay(1000000);
}
