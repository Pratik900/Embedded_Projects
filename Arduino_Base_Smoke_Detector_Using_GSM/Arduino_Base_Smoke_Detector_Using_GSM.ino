#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// SIM800L module RX and TX pins
#define SIM800_RX_PIN 2    //13
#define SIM800_TX_PIN 3    //15
#define MQ_PIN A0              // Analog pin connected to MQ-2 sensor
#define BUZZER_PIN 0           // GPIO 0 (corresponds to D3 on some ESP8266 boards)

#define GAS_THRESHOLD 50      // Set the gas concentration threshold (adjust as needed)

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Phone number to send the message
String phoneNumber = "8268054547";

// Message to send
String message = "Gas Detected";

SoftwareSerial sim800l(SIM800_RX_PIN, SIM800_TX_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(MQ_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin();
  lcd.backlight();  // Turn on the backlight
  lcd.print("Gas Detecter");
  lcd.setCursor(1,0);
  // Initialize the serial communication with the SIM800L module
    sim800l.begin(9600);
  delay(1000);  // Wait for SIM800L module to initialize
  
  // Set text mode for SMS
  sendCommand("AT+CMGF=1\r\n");
  delay(1000);

}

void loop() {
  int gasValue = analogRead(MQ_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > GAS_THRESHOLD) {       //(gasValue > GAS_THRESHOLD)
    lcd.setCursor(0, 1);
    lcd.print("Gas Detected");
    sendSMS(phoneNumber, message);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(2000);
    lcd.clear();
  } else {
    lcd.setCursor(1,0);
    lcd.print("Gas Value:");
    lcd.print(gasValue);
    lcd.setCursor(0, 1);
    lcd.print("No Gas Detected");
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.clear();
  }

  delay(500); // Delay between gas readings
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
