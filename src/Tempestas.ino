#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdio.h>
#include <stdlib.h>

#include <DHT.h>
#inliude "bmp085_functions.cpp"
#define ONE_WIRE_BUS 10
#define DHT_PIN 2

#define TEMPERATURE_PRECISION 12
#define MAX_DEVICES 5


int getTemperatureAsInt(DeviceAddress deviceAddress);
void pipe2Pi(int [], float, float);
float readDHT_Humidity(void);
float readDHT_Temperature(void);


OneWire oneWire(ONE_WIRE_BUS);
DHT dht;
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// An array of potentially 5 devices
DeviceAddress device[MAX_DEVICES];
int deviceCount; 

void setup() {
  // put your setup code here, to run once:
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  
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
  pipe2Pi(dsData, dht_temperature, humidity);
}


void pipe2Pi(int ptrData[], float dht_temp, float humidity){
  String output;
  // Squirt all the data to the Pi
  Serial.print( (float) (ptrData[0] * 0.0078125) );
  for (int x = 1; x < deviceCount; x++){
    Serial.print (",");
    Serial.print ( (float) (ptrData[x] * 0.0078125) );
  }
  Serial.print (",");
  Serial.print ((float) dht_temp);
  Serial.print (",");
  Serial.print ((float) humidity);
  Serial.println("\n");
  Serial.flush();
  delay(1000);
}

int getTemperatureAsInt(DeviceAddress deviceAddress){
  int tempAsInt = sensors.getTemp(deviceAddress);
  return tempAsInt;
}

float readDHT_Humidity(void){
  delay(dht.getMinimumSamplingPeriod());
  return dht.getHumidity();
}

float readDHT_Temperature(void){
  delay(dht.getMinimumSamplingPeriod());
  return dht.getTemperature();
}