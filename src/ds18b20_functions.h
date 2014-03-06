int getTemperatureAsInt(DeviceAddress deviceAddress);
#define ONE_WIRE_BUS 10

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/*
	returns the temp as an int and converted to a float later
*/
int getTemperatureAsInt(DeviceAddress deviceAddress){
  int tempAsInt = sensors.getTemp(deviceAddress);
  return tempAsInt;
}