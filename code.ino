/*
 * Arduino Security Camera with Motion Detection
 * 
 * This sketch interfaces an OV7670 camera module and a PIR motion sensor with
 * an Arduino UNO. The camera captures images when motion is detected by the
 * PIR sensor. The images are stored on an SD card. The system also logs the
 * time and lighting conditions when motion is detected to analyze PIR sensor
 * sensitivity under different lighting conditions.
 */

#include <Wire.h>
#include <SD.h>
#include <SPI.h>

// Pin definitions
const int pirPin = 2; // PIR sensor output pin
const int sdCsPin = 10; // SD card module CS pin
const int cameraPlkPin = 5; // Camera PLK pin
const int cameraVsPin = 3; // Camera VS pin
const int cameraHsPin = 4; // Camera HS pin

// Variables
bool motionDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(sdCsPin, OUTPUT);
  pinMode(cameraPlkPin, OUTPUT);
  pinMode(cameraVsPin, INPUT);
  pinMode(cameraHsPin, INPUT);

  // Initialize SD card
  if (!SD.begin(sdCsPin)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Initialize camera
  Wire.begin();
  // Additional camera initialization code goes here

  // Attach interrupt to PIR sensor
  attachInterrupt(digitalPinToInterrupt(pirPin), detectMotion, RISING);
}

void loop() {
  if (motionDetected) {
    captureImage();
    logEvent();
    motionDetected = false;
  }
}

void detectMotion() {
  motionDetected = true;
}

void captureImage() {
  // Code to capture image from OV7670 camera
  Serial.println("Capturing image...");
  // Image capture logic goes here
}

void logEvent() {
  // Log the event with timestamp and lighting conditions
  File logFile = SD.open("log.txt", FILE_WRITE);
  if (logFile) {
    logFile.print("Motion detected at: ");
    logFile.println(millis());
    logFile.println("Lighting conditions: TBD");
    logFile.close();
    Serial.println("Event logged.");
  } else {
    Serial.println("Error opening log file.");
  }
}