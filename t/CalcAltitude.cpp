/*
Name	: CalAltitude
Purpose	: Calculate altitude of a weather station given MSLP, Pressure at station and local temp in degC
Author	: John Burrin
compile : g++ CalAltitude.cpp -o CalAltitude
*/
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
	if (argc != 4){
		printf("\nusage: CalcAltitude mslp pas temp\nWhere mslp is calculated Mean SeaLevel Pressure\n pas is current Pressure At Station\n and temp is current local temperture\nexample CalcAltitude 1013.25 980.87 11.4\n\n");
	}else{
        	float altitude = 0.0;
        	float mslp = atof(argv[1]);
        	float pas = atof(argv[2]);
        	float temp = atof(argv[3]);
		float a = pow(mslp/pas,0.19022256) - 1;
		float t = temp + 273.15;
		altitude = (a * t) / 0.0065;
		printf("\nAltitude is %5.2f meters\n", altitude);
	}
return 1;
}
