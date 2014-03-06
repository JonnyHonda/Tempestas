#include <stdio.h>
#include <math.h>

int main (void){
	float altitude = 0.0;
	const float p0 = 1013.25;
	float P = 1011.00;
	float temp = 11.00;
        // altitude = pow(p0/pressure,(1/5.257) - 1) * (11+273.15) / 0.0065;
	float a = pow(p0/P,0.19022256) - 1;
	float t = temp + 273.15;
	altitude = (a * t) / 0.0065;
	
	
	// altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));
	printf("\nAltitude for %fhps is %f meters\n", P, altitude);
return 1;
}
