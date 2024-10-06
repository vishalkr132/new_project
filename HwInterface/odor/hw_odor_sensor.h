#ifndef _ODOR_H_
#define _ODOR_H_

#include <stdint.h>

#define DATA_SIZE 26

typedef struct
{
    int8_t i8_header;
    int32_t i32_temperature;
    int32_t i32_voltage1;
    int32_t i32_voltage2;
    int32_t i32_threshold1;
    int32_t i32_threshold2;
    int8_t i8_gasType;
    int8_t i8_preheatSignal;
    int8_t i8_faultSignal;
    int8_t i8_statusSignal;
    int8_t i8_endFram;

}st_OdorSensor;

int32_t ODOR_fnInit(int32_t i32_baudrate , char *path);
int32_t ODOR_fnReadData(st_OdorSensor *odor_t);
uint8_t checksum(uint8_t *data , int32_t len);
int32_t reverse(uint8_t *data);
int32_t ODOR_fnClose();


#endif