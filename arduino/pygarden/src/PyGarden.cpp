/*
  PyGarden.cpp - Library for monitoring a garden.
*/

#include "Arduino.h"
#include "PyGarden.h"

PyGarden::PyGarden() {
  _rain = new YL83_RainSensor(RainSensorPin);
  _soil1 = new FC28_SoilSensor(SoilSensor1Pin, SoilSensor1Dry, SoilSensor1Wet);
  _soil2 = new FC28_SoilSensor(SoilSensor2Pin, SoilSensor2Dry, SoilSensor2Wet);
  _temperature = new DS18B20_TemperatureSensors(TemperatureSensorsPin);
}

void PyGarden::begin() {
  // start serial connection
  // Serial.begin(9600);

  _rain->begin();
  _soil1->begin();
  _soil2->begin();
  _temperature->begin();
}

void PyGarden::loop() {
  _rain->loop();
  _soil1->loop();
  _soil2->loop();
  _temperature->loop();
}
