#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WebServer.h>

#define SIM800_RX_PIN 2    //13
#define SIM800_TX_PIN 3    //15
#define MQ_PIN A0              // Analog pin connected to MQ-2 sensor
#define BUZZER_PIN 0   
#define GAS_THRESHOLD 12

const char* ssid = "MQ2"; //--> Your wifi name or SSID.
const char* password = "02007!tikg"; //--> Your wifi password.

const char* host = "script.google.com";
const int httpsPort = 443;

ESP8266WebServer server(80);

WiFiClientSecure client;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

String GAS_ID = "AKfycbwUWw5LXPVtYy8nuDVT0BL-ma9qrIEj5cmbrFLug6GUTWxeqB5lJdg-3ZV11iQIdTQCHg"; //--> spreadsheet script ID

String phoneNumber = "9970232504";

String message = "Gas Detected";

SoftwareSerial sim800l(SIM800_RX_PIN, SIM800_TX_PIN);

void handleRoot() {
  int t = analogRead(MQ_PIN);
  String gasStatus;
  String h;

  if (t >= GAS_THRESHOLD) {
    gasStatus = "Gas Detected";
    lcd.setCursor(0, 1);
    lcd.print("Gas Detected");
    h = "Gas_Detected";
    sendSMS(phoneNumber, message);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(2000);
    lcd.clear();
  } else {
    lcd.setCursor(1,0);
    lcd.print("Gas Value:");
    lcd.print(t);
    lcd.setCursor(0, 1);
    lcd.print("No Gas Detected");
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.clear();
    gasStatus = "No Gas Detected";
    h = "No_Gas_Detected";
  }

    String html = "<html><head>";
    html += "<style>";
    html += "h1 { text-align: center;border-style: solid;}";
    html += "p { font-size: 18px; text-align: center; color:black;border:double gray;}";
    html += "</style>";
    html += "</head><body>";
    html += "<meta http-equiv=\"refresh\" content=\"1\">";
    html += "<h1>Gas Sensor Data</h1>";
    html += "<p>Gas Value: " + String(t) + "</p>";
    html += "<p>Gas Status: " + gasStatus + "</p>";
    html += "</body></html>";


  server.send(200, "text/html", html);
  delay(500); // Delay between gas readings
  String Temp = "Threshold : " + String(t);
  String Humi = "Result : " + String(h);
  Serial.println(Temp);
  Serial.println(Humi);
  
  sendData(t, h); //--> Calls the sendData Subroutine
}

void setup() {
  
  Serial.begin(115200);
  pinMode(MQ_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin();
  lcd.backlight();  // Turn on the backlight
  lcd.print("Gas Detecter");
  lcd.setCursor(1,0);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  client.setInsecure();
  sim800l.begin(9600);
  delay(1000);  // Wait for SIM800L module to initialize
  
  // Set text mode for SMS
  sendCommand("AT+CMGF=1\r\n");
  delay(1000);
  
  server.on("/", handleRoot);
  server.begin();
}
void loop() {
  server.handleClient();
}

void sendData(float tem, String hum) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  String string_temperature =  String(tem);
  // String string_temperature =  String(tem, DEC); 
  String string_humidity =  String(hum); 
  String url = "/macros/s/" + GAS_ID + "/exec?Threshold=" + string_temperature + "&Result=" + string_humidity;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
} 
void sendSMS(String phoneNumber, String message) {
  // Set the phone number
  sendCommand("AT+CMGS=\"" + phoneNumber + "\"\r\n");
  delay(1000);
  
  // Set the message
  sendCommand(message);
  delay(1000);
  
  // Send the message
  sim800l.write(26);
  
  // Wait for the message to be sent
  delay(5000);
}

void sendCommand(String command) {
  sim800l.print(command);
  while (!sim800l.available());
  String response = sim800l.readString();
  Serial.println(response);
}
