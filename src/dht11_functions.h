float readDHT_Humidity(void);
float readDHT_Temperature(void);


DHT dht;

float readDHT_Humidity(void){
  delay(dht.getMinimumSamplingPeriod());
  return dht.getHumidity();
}

float readDHT_Temperature(void){
  delay(dht.getMinimumSamplingPeriod());
  return dht.getTemperature();
}
