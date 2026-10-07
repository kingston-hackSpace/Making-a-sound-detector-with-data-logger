/**
SD card data logger, saving signals from a SparkFun Sound Detector (envelope), and
tracking date and time via RTC module. 

Data saved as a .CSV file

HOW IT WORKS:
As soon as the Arduino is powered, the data logging starts, adding new lines to the same file if re-plugged. 
See next tutorial to log readings to separate files.
**/

#include <Wire.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>

#define envelopePin A0 //analog pin
#define CSPIN 10

const unsigned long LOG_INTERVAL = 500;    // time between log entries, in milliseconds
unsigned long lastLogTime = 0;             // when we last wrote to the card

// running totals for the current interval
unsigned long sum = 0;     // all readings added together (for the average)
unsigned int count = 0;    // how many readings we took

RTC_DS3231 rtc; // create rtc object of class RTC_DS3231

File myFile;

void setup(){
  Serial.begin(9600);
  Serial.println("Starting...");
  Wire.begin();

  pinMode(10, OUTPUT);
  pinMode(envelopePin,INPUT);

  // Initialise RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // set the clock if it lost power OR if it is behind the time this sketch was compiled
  DateTime compileTime = DateTime(F(__DATE__), F(__TIME__));
  if (rtc.lostPower() || rtc.now() < compileTime) {
    Serial.println("RTC lost power or is behind, setting the time!");
    rtc.adjust(compileTime);
  }

  // Initialise SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(CSPIN)) {
    Serial.println("Card failed or not present!");
    while (1);
  }
  Serial.println("SD card initialised.");

  // only write the header if the file doesn't exist yet
  if (!SD.exists("DATALOG.CSV")) {
    myFile = SD.open("DATALOG.CSV", FILE_WRITE);
    if (myFile) {
      myFile.println("Date,Time,average");   
      myFile.close();
    }
  }
}

void loop(){
  // read the sensor on EVERY pass of loop, and keep a running total
  int reading = analogRead(envelopePin);
  sum += reading;
  count++;

  // only log once every LOG_INTERVAL milliseconds
  if (millis() - lastLogTime < LOG_INTERVAL) {
    return;
  }
  lastLogTime = millis();

  // work out the average for this interval (whole number, int)
  int average = sum / count;

  DateTime now = rtc.now();

  // ISO date format yyyy-mm-dd
  char dateBuffer[12];
  sprintf(dateBuffer, "%04d-%02d-%02d", now.year(), now.month(), now.day());
  char timeBuffer[10];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  // Show on serial monitor
  Serial.print(dateBuffer);              
  Serial.print("  ");
  Serial.print(timeBuffer);
  Serial.print("  avg: ");
  Serial.println(average);               

  // Write to SD card
  myFile = SD.open("DATALOG.CSV", FILE_WRITE);
  if (myFile) {
    myFile.print(dateBuffer);
    myFile.print(",");
    myFile.print(timeBuffer);
    myFile.print(",");
    myFile.println(average);            
    myFile.close();
  } else {
    Serial.println("Error opening datalog file!");
  }

  // reset the totals ready for the next interval
  sum = 0;
  count = 0;
}
