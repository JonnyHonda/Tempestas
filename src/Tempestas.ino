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

#include "MLX90614.h"
#include "mlx.h"
//#include "lib/MLX90614/MLX90614.h"

#define DHT_PIN 2

#define TEMPERATURE_PRECISION 12
#define MAX_DEVICES 5

// An array of potentially 5 devices
DeviceAddress device[MAX_DEVICES];

//MLX90614 mlx;

void setup() {
  // put your setup code here, to run once:
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);

  // Start up the libraries
  Wire.begin();
  bmp085Calibration();

  dht.setup(DHT_PIN); // data pin 2
  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  for(int x = 0; x < deviceCount; x++){
    sensors.getAddress(device[x],x);
    sensors.setResolution(device[x], TEMPERATURE_PRECISION);
  }  
}

void loop() {
  // fetch the temperature, pressure and altitude from the BMP085
  temperature = bmp085GetTemperature(bmp085ReadUT());
  pressure = bmp085GetPressure(bmp085ReadUP());
  altitude = bmp085GetAltitude(temperature, pressure);
  
  // fetch the mls Temps
  float objTemp = 0.0;
  float ambTemp = 0.0;
  getMlxTemp(&objTemp, &ambTemp);
  // create an array to hold the ds18b20 temperatures
  int dsData[deviceCount];
  int t;
  sensors.requestTemperatures();
  
  for(int x = 0; x < deviceCount; x++){
   t = getTemperatureAsInt(device[x]);
   dsData[x] = t;
  }

  // fetch the DHT11 humidity and temperature
  float humidity = readDHT_Humidity();
  float dht_temperature = readDHT_Temperature();
  
  // Now push everything to output
  pipe2Pi(dsData, dht_temperature, humidity, pressure,altitude,temperature,ambTemp,objTemp);
}
