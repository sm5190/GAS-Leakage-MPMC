#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9, 10);
 
int gasValue = A0; // gas sensor connected with analog pin A0
int data = 0;
int SPEAKER = 8;    // The speaker is on pin 8

int freq = 0;  
void setup()
{

randomSeed(analogRead(0));
 pinMode(SPEAKER, OUTPUT);
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor
lcd.init();
 lcd.backlight();
pinMode(gasValue, INPUT);
lcd.setCursor(0,0);
lcd.print (" Gas Leakage ");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();

}
 
void loop()
{
 
data = analogRead(gasValue);
lcd.setCursor(0,0);
Serial.print("Gas Level: ");
Serial.println(data);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,0);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);
 
if ( data > 500) //
{
freq=1000;
tone(SPEAKER, freq);
delay(100);

SendMessage();

lcd.setCursor(0,1);
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,1);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
 
}
else
{
noTone(SPEAKER);
lcd.setCursor(0,0);
Serial.print("Gas Level Low");
//lcd.clear();
lcd.setCursor(0,1);
lcd.print("Gas Level Normal");
delay(1000);
}
 
lcd.clear();
}
 
void SendMessage()
{
//Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 msec or 1 sec
mySerial.println("AT+CMGS=\"+8801682644989\"\r"); // Mobile number
delay(1000);
mySerial.println("ALERT! Excess Gas Detected. Open Windows Immediately");// The SMS 
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
