/*
  PyGarden.cpp - Library for monitoring a garden.
*/

#include "Arduino.h"
#include "PyGarden.h"

PyGarden::PyGarden() {
  /*_rain = new YL83_RainSensor(RainSensorPin);
  _soil1 = new FC28_SoilSensor(SoilSensor1Pin, SoilSensor1Dry, SoilSensor1Wet);
  _soil2 = new FC28_SoilSensor(SoilSensor2Pin, SoilSensor2Dry, SoilSensor2Wet);*/
  _temperature = new DS18B20_TemperatureSensors(TemperatureSensorsPin);
  _light = new BH1750_LightSensor(LightSensorSCLPin, LightSensorSDAPin);
  _water = new SingleChannel_Relay(WaterValvePin);
}

void PyGarden::begin() {
  // start serial connection
  Serial.begin(115200);

  /*_rain->begin();
  _soil1->begin();
  _soil2->begin();*/
  _temperature->begin();
  _light->begin();
  _water->begin();
}

void PyGarden::loop() {
  /*
  _rain->loop();
  _soil1->loop();
  _soil2->loop();
  */
  // temperature
  float temperature1 = _temperature->getTemperatureByIndex(0);
  Serial.print("Temperature 1: ");
  Serial.print(temperature1);
  Serial.println("ºC");
  float temperature2 = _temperature->getTemperatureByIndex(1);
  Serial.print("Temperature 2: ");
  Serial.print(temperature2);
  Serial.println("ºC");
  delay(2000);

  // light
  float lux = _light->read();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  // water
  _water->start();
  Serial.println("Current: flowing");
  delay(4000);

  _water->stop();
  Serial.println("Current: idle");
  delay(4000);

  delay(3000);
  Serial.println("-----------------------");
}
