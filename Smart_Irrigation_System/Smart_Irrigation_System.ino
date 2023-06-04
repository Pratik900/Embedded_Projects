#define AOUT_PIN0 A0
#define AOUT_PIN1 A1
#define AOUT_PIN2 33
#define AOUT_PIN3 32

#define THRESHOLD 1500
#define THRESHOLD1 1900
#define THRESHOLD2 1000

int solenoid0 = 16;
int solenoid1 = 17;
int solenoid2 = 5;
int solenoid3 = 18;

void setup() {
  Serial.begin(115200);
  pinMode(solenoid0, OUTPUT);
  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(solenoid3, OUTPUT);
}

void loop() {
  int value0 = analogRead(AOUT_PIN0); // read the analog value from sensor
  int value1 = analogRead(AOUT_PIN1); // read the analog value from sensor
  int value2 = analogRead(AOUT_PIN2); // read the analog value from sensor
  int value3 = analogRead(AOUT_PIN3); // read the analog value from sensor

  if (value0 > THRESHOLD1){
    Serial.print("The soil 1 is DRY (");
    digitalWrite(solenoid0, LOW);
    }
    else{
      Serial.print("The soil 1 is WET (");
      digitalWrite(solenoid0, HIGH);
      }
      Serial.print(value0);
      Serial.println(")");
      delay(500);
      
     if(value1>THRESHOLD){
      Serial.print("The soil 2 is DRY (");
      digitalWrite(solenoid1, LOW);
     }
     else{
      Serial.print("The soil 2 is WET (");
      digitalWrite(solenoid1, HIGH);
     }
     Serial.print(value1);
     Serial.println(")");
     delay(500);

     if(value2>THRESHOLD){
      Serial.print("The soil 3 is DRY (");
      digitalWrite(solenoid2, LOW);
     }
     else{
      Serial.print("The soil 3 is WET (");
      digitalWrite(solenoid2, HIGH);
     }
     Serial.print(value2);
     Serial.println(")");
     delay(500);

     if(value3 > THRESHOLD2){
      Serial.print("The soil 4 is DRY (");
      digitalWrite(solenoid3, LOW);
     }
     else{
      Serial.print("The soil 4 is WET (");
      digitalWrite(solenoid3, HIGH);
     }
     Serial.print(value3);
     Serial.println(")");
     delay(500);
     
}
