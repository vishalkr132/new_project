#ifndef _RADAR_H_
#define _RADAR_H_

#include <stdio.h>
#include <stdint.h>

#define RADAR_DATA_SIZE 100

int32_t RADAR_fnInit(int32_t i32_baudrate , uint8_t *path);
float RADAR_fnReadData();
int32_t RADAR_fnClose();

#endif