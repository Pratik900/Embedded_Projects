#include <LiquidCrystal_I2C.h>
#include "EmonLib.h"
#include <FirebaseESP32.h>
#include  <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"  

#define vCalibration 83.3
#define currCalibration 0.50
#define dc_relay 16 
#define ac_relay 17 
#define FIREBASE_HOST "solar-base-ev-charger-default-rtdb.firebaseio.com"
#define WIFI_SSID "MIT-WPU" // Change the name of your WIFI
#define WIFI_PASSWORD "CROPMONITORING" // Change the password of your WIFI
#define FIREBASE_Authorization_key "AIzaSyAK5eWuAFdkmslDYkX1Qjqrjztgmfi5c6s"

int lcdColumns = 16;
int lcdRows = 2;
EnergyMonitor emon;
int voltage_offset = 20;
DHT dht2(4,DHT11);  
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
float kWh = 0;
FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseJson json;
unsigned long lastmillis = millis();

void myTimerEvent()
{
  emon.calcVI(20, 500);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  int volt = analogRead(35);// read the input
  double voltage = map(volt,0,4095, 0, 1650) + voltage_offset;
  double irms;
  int vrms;
  voltage /=100; 
  yield();
  Serial.print("Vrms:");
  Serial.print(emon.Vrms,2);
  Serial.print("V\t");
  
  Serial.print("Irms:");
  Serial.print(emon.Irms);
  Serial.print("I\t");

  Serial.print("DC Voltage: ");
  Serial.print(voltage);
  Serial.print("V\t");

  Serial.print("Temperature in C:");  
  Serial.println((dht2.readTemperature( )));  

  lcd.setCursor(1, 0);
  lcd.print("SOLAR BASED EV");
  lcd.setCursor(0,1);
  lcd.print("CHARGING STATION");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.print(emon.Vrms,2);
  vrms = (emon.Vrms);
  lcd.print("V");
  lcd.setCursor(0,1);
  lcd.print("Irms:");
  lcd.print(emon.Irms,4);
  irms = (emon.Irms);
  lcd.print("Amp");
  Firebase.setFloat(firebaseData, "/Vrms", (vrms));
  Firebase.setFloat(firebaseData, "/Irms", (irms));
  delay(3000);
  lcd.clear(); 

  lcd.setCursor(0, 0);
  lcd.print("Dc Volt:");
  lcd.print(voltage);
  lcd.print("V");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print((dht2.readTemperature( )));
  lcd.print((char)223);
  lcd.print("C");
  Firebase.setFloat(firebaseData, "/DC_Voltage", (voltage));
  Firebase.setFloat(firebaseData, "/TEMPERATURE", (dht2.readTemperature( )));
  delay(3000);
  lcd.clear(); 
  Firebase.get(firebaseData, "/DC_Relay");
  if ((firebaseData.stringData() == "0") && (voltage>=10))
  {
    digitalWrite(dc_relay,HIGH);
  }
  else if ((firebaseData.stringData() == "0")&&(voltage<=10))
  {
    digitalWrite(dc_relay,LOW);
  }
  else if((firebaseData.stringData() == "1")&&(voltage>=10))
  {
    digitalWrite(dc_relay,HIGH);
  }
  else if((firebaseData.stringData() == "0")&&(voltage<=10))
  {
    digitalWrite(dc_relay,HIGH);
  }
  else{
    digitalWrite(dc_relay,HIGH);
  }
  Firebase.get(firebaseData1, "/AC_Relay");
  if (firebaseData1.stringData() == "0")
  {
    digitalWrite(ac_relay,LOW);
  }
  else
  {
    digitalWrite(ac_relay,HIGH);
  }
  lcd.setCursor(0, 0);
  lcd.print("Battery:");
  if(firebaseData.stringData()=="0")
  {
    lcd.print("ON");
  }
  else
  {
    lcd.print("OFF");
  }
  lcd.setCursor(0,1);
  lcd.print("Inverter:");
  if(firebaseData1.stringData()=="0")
  {
    lcd.print("ON");
  }
  else
  {
    lcd.print("OFF");
  }
  delay(3000);
  lcd.clear(); 

  lastmillis = millis();
}
void setup()
{
  Serial.begin(115200);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  emon.voltage(34, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
  emon.current(32, currCalibration);   // Current: input pin, calibration.
  timer.setInterval(1000L, myTimerEvent);
  lcd.begin();                     
  lcd.backlight();
  pinMode(dc_relay, OUTPUT);
  pinMode(ac_relay, OUTPUT);
  
}
void loop()
{
  myTimerEvent();

}
