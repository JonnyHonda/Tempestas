#include <OneWire.h>
char *data;

void setup() {
  // put your setup code here, to run once:
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  data = "Arduino";
  pipe2Pi(data);
}




/* 
  
*/
void pipe2Pi(char *data){
  /* Squirt all the data to the Pi */
  Serial.print(data);
}

