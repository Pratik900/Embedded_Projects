#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <WiFi.h>
#include <Wire.h>
#include <Max44009.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
float temperature, humidity, pressure, altitude;
int val;

WiFiClient client;

unsigned long myChannelNumber = 1622061; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "FV25GVX753NCI3ME"; //Your Write API Key
Max44009 myLux(0x4A);
void setup()
{
  Serial.begin(115200);
  delay(10);
    Wire.begin();
    bme.begin(0x76); 
  // Connect to WiFi network
 WiFi.begin("MAYURESH", "mayuresh"); 
  ThingSpeak.begin(client);

}

void loop()
{
    int value = analogRead(36);
    Serial.println (value);
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
Serial.print("Temperature: ");
Serial.print(temperature);  
  
Serial.print("  humidity : ");
Serial.print(  humidity ); 
Serial.print("  pressure: ");
Serial.print(  pressure); 
Serial.print(" altitude: ");
Serial.print( altitude); // Print on Serial Monitor
  
 Serial.print("lux:\t");
 Serial.println(myLux.getLux());


  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1,temperature,myWriteAPIKey); //Update in ThingSpeak 
  ThingSpeak.writeField(myChannelNumber, 2,humidity ,myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3,pressure ,myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4,altitude ,myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5,myLux.getLux() ,myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 6,value ,myWriteAPIKey);
  delay(100);
}
