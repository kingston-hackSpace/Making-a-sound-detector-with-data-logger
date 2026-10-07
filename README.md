# Making a Sound Detector with Data Logger

----
## TUTORIAL DESCRIPTION

Using a Sound Detector with an Arduino UNO and logging data to SD card module

Once the device is powered, the Arduino will connect to the SD card and start logging sound intensity from the detector.

----
## SPARKFUN SOUND DETECTOR

The SparkFun Sound Detector is a microphone-based sensor designed to detect the presence and intensity of sound in its surroundings.

Note : It does NOT provide decibel readings, so it’s not suitable for precise noise level measurements.

Note : It’s NOT a sound recorder— It only measures sound intensity (volume) and provides a corresponding signal.

Read more about the Sparkfun Sound Detector [here](https://github.com/kingston-hackSpace/Sound-Detector/blob/main/README.md)

----
## HARDWARE

- Arduino UNO

- Sparkfun Sound detector

- SD-card module (with SD-card and reader) [more detail here](https://github.com/kingston-hackSpace/SDCard)
  
- RTC clock module [more detail here](https://github.com/kingston-hackSpace/RTC_Clock-Module)

- jumper wires

----
## WIRING

Assemble the equipment as shown in the fritzing file [here](https://github.com/kingston-hackSpace/Making-a-sound-detector-with-data-logger/blob/main/sound_detector_data_logger_bb.png). Connect the device via a serial connection, you can check for progress of the data logging.

----
### Upload the code and libraries
Open the .ino file in the arduino IDE. Make sure the following libraries are installed through the IDE...

- wire
- RTClib
- SD
- SPI

go to Sketch->Include library->manage libraries search for each one to see if they're installed

----
### Trouble shooting
If the SD card is not reading try the following...

Ensure the SD card is formatted correctly
Use only 8 characters for the name of the destination file
make sure the jump leads are well connected
try replacing the breadboard

----
### Useful links

[More on data logging](https://github.com/kingston-hackSpace/DataLogging_DHT11/tree/main)

