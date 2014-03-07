#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
arguments:
	1 mslp
	2 pas
	3 temperature
*/
int main (int argc, char** argv){
	if (sizeof(argc) != 4){
		printf("usage: CalcAltitude mslp pas temp");
	}else{
        	float altitude = 0.0;
        	float mslp = atof(argv[1]);
        	float pas = atof(argv[2]);
        	float temp = atof(argv[3]);
		float a = pow(mslp/pas,0.19022256) - 1;
		float t = temp + 273.15;
		altitude = (a * t) / 0.0065;
		printf("\n%dAltitude for %fhpa is %f meters\n",(int)sizeof(argc), pas, altitude);
	}
return 1;
}
