#include <Servo.h>
#include <LiquidCrystal_I2C.h>

int IRSensor = 10; 
int IRSensor1 = 11; 

int IR4 = 4;
int IR5 = 5;
int IR6 = 6;
int IR7 = 7;

int total_ir=0;

int pos = 0;
int pos1 = 0;
Servo myservo;
Servo myservo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup(){
  Serial.begin(115200); 
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("CAR PARKING");
  lcd.setCursor(4,1);
  lcd.print("SYSTEM");
  delay(3000);
  lcd.clear();
  pinMode(IRSensor, INPUT);
  pinMode(IRSensor1, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR7, INPUT);
  myservo.attach(9);
  myservo1.attach(8);

}
void loop(){

  int sensorStatus = digitalRead(IRSensor);
  int sensorStatus1 = digitalRead(IRSensor1);
  int sensorStatus5 = digitalRead(IR5);
  int sensorStatus4 = digitalRead(IR4);
  int sensorStatus6 = digitalRead(IR6);
  int sensorStatus7 = digitalRead(IR7);
  total_ir = sensorStatus4 + sensorStatus5 + sensorStatus6 + sensorStatus7 ;

  if (total_ir == 0)
  {
    lcd.setCursor(1, 0);
    lcd.print("Parking is full");
  }
  else
  {
      lcd.setCursor(0, 0);
      lcd.print(total_ir);
      lcd.print(" Slot are Empty");
  }
  delay(3000);
  lcd.clear();
  
  if (total_ir != 0)
  {
          if (sensorStatus == 0) 
      {
        for (pos = 0; pos <= 90; pos += 1) { 
        // in steps of 1 degree
        myservo.write(pos);             
        delay(15);          
        }
        delay(3000);
        for (pos = 90; pos >= 0; pos -= 1) { 
        myservo.write(pos);          
        delay(15);                   
        }
        }
        else if (sensorStatus1 == 0)
        {
        for (pos1 = 0; pos1 <= 90; pos1 += 1) { 
        // in steps of 1 degree
        myservo1.write(pos1);           
        delay(15);                      
        }
        delay(3000);
        for (pos1 = 90; pos1 >= 0; pos1 -= 1) { 
        myservo1.write(pos1);      
        delay(15);                     
        }
        }
  }
}
