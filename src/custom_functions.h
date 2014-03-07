void pipe2Pi(int ptrData[], float dht_temp, float humidity, long pressure, float altitude, short bmp085temperature);
float quickMSLP(float, float, float);

int deviceCount; 

float quickMSLP(float t, float h, float p){
  float dTop = 0.0065 * h;
  float dBottom = t + dTop + 273.15;
  float mslp = 0.0;
  float temp = pow (1 - (dTop / dBottom), -5.257);
  mslp =p * temp;
  return mslp;
}

void pipe2Pi(int ptrData[], float dht_temp, float humidity, long pressure, float altitude, short bmp085temperature){
  String output;
  double total;
  // Squirt all the data to the Pi
  Serial.print( (float) (ptrData[0] * 0.0078125) ); // this can probably bee sent as int and handled by the oi to convert to float
  for (int x = 1; x < deviceCount; x++){
    Serial.print (",");
    Serial.print ( (float) (ptrData[x] * 0.0078125) );
  }

  float mslp = quickMSLP(dht_temp, 62.00, pressure);
  Serial.print (",");
  Serial.print ((float) dht_temp);
  Serial.print (",");
  Serial.print ((float) humidity);
  Serial.print (",");
  Serial.print ((float) pressure / 100);
  Serial.print (",");
  Serial.print ((float) altitude);
  Serial.print (",");
  Serial.print ((short) bmp085temperature);
  Serial.print (",");
  Serial.print ((float) mslp);
  Serial.println("\n");
  Serial.flush();
  delay(2000);
}