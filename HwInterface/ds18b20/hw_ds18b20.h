#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <stdint.h>


int32_t DS18B20_fnInit(char *path);
void DS18B20_fnReadData();


#endif