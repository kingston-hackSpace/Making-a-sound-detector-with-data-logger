/** 
SDCARD Module - testing communication

WIRING :
SDCARD MODULE 5V pin to the 5V pin on the Arduino UNO
SDCARD MODULE GND pin to the GND pin on the Arduino UNO
SDCARD MODULE CLK to pin 13  (pin 52 for Arduino MEGA)
SDCARD MODULE DO to pin 12 (pin 50 for Arduino MEGA)
SDCARD MODULE DI to pin 11  (pin 51 for Arduino MEGA)
SDCARD MODULE CS to pin 10  (pin 53 for Arduino MEGA)

**/
#include <Wire.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>

#define envelopePin A0 //analog pin
#define CSPIN 10

RTC_DS3231 rtc; // create rtc object of class RTC_DS3231
 
File myFile;
 
void setup(){
  Serial.begin(9600); 
  Wire.begin();

  pinMode(10, OUTPUT);
  pinMode(envelopePin,INPUT);

    // Initialise RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
 
   // Initialise SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(CSPIN)) {
    Serial.println("Card failed or not present!");
    while (1);
  }
  Serial.println("SD card initialised.");

  // Create / open log file
  myFile = SD.open("DATALOG.CSV", FILE_WRITE);
  if (myFile) {
    myFile.println("Date,Time,data_reading");
    myFile.close();
  }
}
 
void loop()
{
  DateTime now = rtc.now();

  float h = analogRead(envelopePin);//raw data from the analog pin

  // Format date and time
  char dateBuffer[12];
  sprintf(dateBuffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  char timeBuffer[10];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  // Write to SD card
  myFile = SD.open("DATALOG.CSV", FILE_WRITE);
  if (myFile) {
    myFile.print(dateBuffer);
    myFile.print(",");
    myFile.print(timeBuffer);
    myFile.print(",");
    myFile.println(h, 1);
    myFile.close();
} else {
    Serial.println("Error opening datalog file!");    
  }
}
