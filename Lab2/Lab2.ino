#include <Wire.h>
volatile uint16_t TrackingData_R; 
volatile uint16_t TrackingData_L;
volatile uint16_t TrackingData_M;
#define STM8S003F3_IR_devAddr 0XA0
#define PIN_Motor_AIN 8
#define PIN_Motor_BIN 7
#define PIN_Motor_PWMA 9
#define PIN_Motor_PWMB 6
#define PIN_Motor_STBY 4

void STM8S003F3_IR_Init(void)
{
  Wire.begin();
  pinMode(PIN_Motor_AIN, OUTPUT);
  pinMode(PIN_Motor_BIN, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  Wire.beginTransmission(STM8S003F3_IR_devAddr);
  Wire.write(110);
  Wire.endTransmission();
}

void devices(uint16_t *STM8S003F3_IRL /*out*/, uint16_t *STM8S003F3_IRM /*out*/, uint16_t *STM8S003F3_IRR /*out*/){
  uint8_t STM8S003F3_IR_IIC_buff[8];
  uint8_t a = 0;
  static uint8_t cout = 0;
  Wire.requestFrom(STM8S003F3_IR_devAddr, 8); // request 6 bytes from slave device #2
  while (Wire.available())                    // slave may send less than requested
  {
    STM8S003F3_IR_IIC_buff[a++] = Wire.read(); // receive a byte as character
  }
  if ((STM8S003F3_IR_IIC_buff[0] == 0XA0) && (STM8S003F3_IR_IIC_buff[7] == 0XB0))
  {
    *STM8S003F3_IRR = (STM8S003F3_IR_IIC_buff[1] << 8) | (STM8S003F3_IR_IIC_buff[2]);
    *STM8S003F3_IRL = (STM8S003F3_IR_IIC_buff[3] << 8) | (STM8S003F3_IR_IIC_buff[4]);
    *STM8S003F3_IRM = (STM8S003F3_IR_IIC_buff[5] << 8) | (STM8S003F3_IR_IIC_buff[6]);
    cout = 0;
  }
  else
  {
    /* code */
    //Serial.println("Contact Changhua :STM8S003F3_IR data error"); // print the character
    cout += 1;
    if (cout > 250)
    {
      Wire.beginTransmission(STM8S003F3_IR_devAddr);
      Wire.write(110);
      Wire.endTransmission();
    }
    return;
  }
}

void turn_right()
{
  digitalWrite(PIN_Motor_BIN, LOW);
  analogWrite(PIN_Motor_PWMB, 250);
  digitalWrite(PIN_Motor_AIN, LOW);
  analogWrite(PIN_Motor_PWMA, 250);
}

void turn_left()
{
  digitalWrite(PIN_Motor_BIN, HIGH);
  analogWrite(PIN_Motor_PWMB, 250);
  digitalWrite(PIN_Motor_AIN, HIGH);
  analogWrite(PIN_Motor_PWMA, 250);
}

void forward()
{
  digitalWrite(PIN_Motor_AIN, HIGH);
  analogWrite(PIN_Motor_PWMA, 80);
  digitalWrite(PIN_Motor_BIN, LOW);
  analogWrite(PIN_Motor_PWMB, 80);
}

void backward()
{
  digitalWrite(PIN_Motor_AIN, LOW);
  analogWrite(PIN_Motor_PWMA, 80);
  digitalWrite(PIN_Motor_BIN, HIGH);
  analogWrite(PIN_Motor_PWMB, 80);
}

/*
void DeviceDriverSet_STM8S003F3_IR_Test(void)
{
  uint8_t STM8S003F3_IR_IIC_buff[8];
  uint8_t a = 0;
  Wire.requestFrom(STM8S003F3_IR_devAddr, 8); // request 6 bytes from slave device #2
  while (Wire.available())                    // slave may send less than requested
  {
    STM8S003F3_IR_IIC_buff[a++] = Wire.read(); // receive a byte as character
  }

  if ((STM8S003F3_IR_IIC_buff[0] == 0XA0) && (STM8S003F3_IR_IIC_buff[7] == 0XB0))
  {

    Serial.print("R:");
    Serial.print((STM8S003F3_IR_IIC_buff[1] << 8) | (STM8S003F3_IR_IIC_buff[2]));
    Serial.print("\t");

    Serial.print("L:");
    Serial.print((STM8S003F3_IR_IIC_buff[3] << 8) | (STM8S003F3_IR_IIC_buff[4]));
    Serial.print("\t");

    Serial.print("M:");
    Serial.print((STM8S003F3_IR_IIC_buff[5] << 8) | (STM8S003F3_IR_IIC_buff[6]));

    Serial.println(""); // print the character
  }
  else
  {

    Serial.println("STM8S003F3_IR data error"); // print the character
  }
}
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  STM8S003F3_IR_Init();

}

void loop(){
  int count = 0;
  devices(&TrackingData_L, &TrackingData_M, &TrackingData_R);
  if(TrackingData_M > 100 && TrackingData_R > 100 && TrackingData_L > 100){backward();delay(300);turn_left();delay(200);}
  else if(TrackingData_R > 100 && TrackingData_L > 100){backward();delay(300);turn_left();delay(200);}
  else if(TrackingData_M > 100 && TrackingData_R > 100){backward();delay(300);turn_right();delay(200);}
  else if(TrackingData_L > 100){backward();delay(500);turn_right();delay(150);}
  else if(TrackingData_R > 100){backward();delay(500);turn_left();delay(150);}

  else if(TrackingData_R < 100){forward();delay(100);}
}
