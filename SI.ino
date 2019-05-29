

#define BUZZER_PIN  3
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int PIN_DRIVER_IN1 = 2;
int PIN_DRIVER_IN2 = 4;
int PIN_DRIVER_IN3 = 7;
int PIN_DRIVER_IN4 = 8;

const int trigPin1 = A0;
const int echoPin1 = A1 ;
const int trigPin2 = A3;
const int echoPin2 = A2;
long duration1, duration2;
int distance1, distance2;
int go_forward=1;
char msg1[21];
char msg2[21];
void setup() {
  // put your setup code here, to run once:
    pinMode(PIN_DRIVER_IN1, OUTPUT);
    pinMode(PIN_DRIVER_IN2, OUTPUT);
    pinMode(PIN_DRIVER_IN3, OUTPUT);
    pinMode(PIN_DRIVER_IN4, OUTPUT);
    
    lcd.begin();
    lcd.backlight();
  
    pinMode(BUZZER_PIN, OUTPUT);
      pinMode(trigPin1, OUTPUT); 
    pinMode(trigPin2, OUTPUT); 
    pinMode(echoPin1, INPUT); 
    pinMode(echoPin2, INPUT); 

     Serial.begin(9600);

}
void senzor1(){
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*0.034/2;
}

void motorStop() {
  digitalWrite(PIN_DRIVER_IN1, LOW);
  digitalWrite(PIN_DRIVER_IN2, LOW);
  digitalWrite(PIN_DRIVER_IN3, LOW);
  digitalWrite(PIN_DRIVER_IN4, LOW);
}
void senzor2(){
  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.034/2; //masoara in cm
}

void buzzer(){
  if((distance1 < 20) || (distance2 < 20)&&!((distance1 < 10) || (distance2 < 10))){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    //delay(100);
  }else if((distance1 < 10) || (distance2 < 10)){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
  }
  else {
    digitalWrite(BUZZER_PIN, LOW);
  }
  
}

void ecran(){
  
  sprintf(msg1, "Distance1: %-7d", distance1);
  lcd.setCursor(0, 0); 
  lcd.print(msg1);
  
  sprintf(msg2, "Distance2: %-7d", distance2);
  lcd.setCursor(0, 1); 
  lcd.print(msg2);
  
  delay(50);
  
}

void forward() 
{
  digitalWrite(PIN_DRIVER_IN1, HIGH);
  digitalWrite(PIN_DRIVER_IN2, LOW);
  digitalWrite(PIN_DRIVER_IN3, HIGH);
  digitalWrite(PIN_DRIVER_IN4, LOW);
}

//transmiterea semnalelor corespunzătoare către motoare pentru mers înapoi
void backward() {
  digitalWrite(PIN_DRIVER_IN1, LOW);
  digitalWrite(PIN_DRIVER_IN2, HIGH);  
  digitalWrite(PIN_DRIVER_IN3, LOW);
  digitalWrite(PIN_DRIVER_IN4, HIGH); 
}
void loop() {
  // put your main code here, to run repeatedly:
  senzor1();
  senzor2();
  buzzer();
  ecran();
  if(distance1<10)
  {
    
    go_forward=0;
    motorStop();
    delay(500);
  }
  else if(distance2<10)
  {
    
    go_forward=1;
    motorStop();
    delay(500);
  }
  if(go_forward)
  {
    forward();
  }
  else
  {
    backward();
  }
  
  }
