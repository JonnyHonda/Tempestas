#include <lib/MLX90614/MLX90614.h>

MLX90614 mlx;

float getMlxTemp(int t){
  int address = 0x55;
  if(t == 0) {
     return mlx.getObjTemp(address);
   }else{
  return mlx.getAmbTemp(address);
   }
}
