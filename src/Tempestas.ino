#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdio.h>
#include <stdlib.h>
#include <Wire.h>
#include <DHT.h>

#include "bmp085_functions.h"
#include "dht11_functions.h"
#include "custom_functions.h"
#include "ds18b20_functions.h"


#define DHT_PIN 2

#define TEMPERATURE_PRECISION 12
#define MAX_DEVICES 5


//OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.

// An array of potentially 5 devices
DeviceAddress device[MAX_DEVICES];

void setup() {
  // put your setup code here, to run once:
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  Wire.begin();
  bmp085Calibration();


  // Start up the libraries
  dht.setup(DHT_PIN); // data pin 2
  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  for(int x = 0; x < deviceCount; x++){
    sensors.getAddress(device[x],x);
    sensors.setResolution(device[x], TEMPERATURE_PRECISION);
  }  
}

void loop() {
  temperature = bmp085GetTemperature(bmp085ReadUT());
  pressure = bmp085GetPressure(bmp085ReadUP());
  altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));

  int dsData[deviceCount];
  int t;
  //Serial.println("Incomming...");
  sensors.requestTemperatures();
  
  for(int x = 0; x < deviceCount; x++){
   t = getTemperatureAsInt(device[x]);
   dsData[x] = t;
  }
  float humidity = readDHT_Humidity();
  float dht_temperature = readDHT_Temperature();
  // Now push everything to output
  pipe2Pi(dsData, dht_temperature, humidity, pressure,altitude,temperature);
}