#include <lib/MLX90614/MLX90614.h>

MLX90614 mlx;

void getMlxTemp(float *objTemp, float *ambTemp){
  int address = 0x55;
  *objTemp = mlx.getObjTemp(address);
  *ambTemp = mlx.getAmbTemp(address);
}