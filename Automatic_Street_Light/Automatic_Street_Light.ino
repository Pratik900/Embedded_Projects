int IRSensor1 = 8; 
int IRSensor2 = 9; 
int IRSensor3 = 10; 
int IRSensor4 = 11; 
int LED1 = 4;
int LED2 = 5;
int LED3 = 6;
int LED4 = 7;
void setup(){
  Serial.begin(115200);
  pinMode(IRSensor1, INPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(IRSensor2, INPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(IRSensor3, INPUT); 
  pinMode(LED3, OUTPUT); 
  pinMode(IRSensor4, INPUT); 
  pinMode(LED4, OUTPUT); 
}
void loop(){
  int sensorStatus1 = digitalRead(IRSensor1); 
  int sensorStatus2 = digitalRead(IRSensor2);
  int sensorStatus3 = digitalRead(IRSensor3);
  int sensorStatus4 = digitalRead(IRSensor4);
  if (sensorStatus1 == 1)
  {
    digitalWrite(LED1, LOW);
  }
  else  {
    digitalWrite(LED1, HIGH); 
//    delay(1000);
  }
    if (sensorStatus2 == 1)
  {
    digitalWrite(LED2, LOW);
  }
  else  {
    digitalWrite(LED2, HIGH);
//    delay(1000);
  }
    if (sensorStatus3 == 1)
  {
    digitalWrite(LED3, LOW);
  }
  else  {
    digitalWrite(LED3, HIGH);
//    delay(1000);
  }
    if (sensorStatus4 == 1)
  {
    digitalWrite(LED4, LOW);
  }
  else  {
    digitalWrite(LED4, HIGH);
//    delay(1000);
  }
}
