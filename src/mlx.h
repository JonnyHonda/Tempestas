#include <lib/MLX90614/MLX90614.h>
float getMlxTemp(void);
MLX90614 mlx;

float getMlxTemp(void){
  int address = 0x55;
     return mlx.getObjTemp(address);
}
