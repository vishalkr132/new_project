#include "hw_ds18b20.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int32_t ds18b20_fd;

int32_t DS18B20_fnInit(char *path)
{
    ds18b20_fd = open(path , O_RDWR);

    if(-1 == ds18b20_fd)
    {
        printf("failed to opne path %d\n" , ds18b20_fd);
        return -1;
    }


}

void DS18B20_fnReadData()
{
    char buffer[2];

    memset(&buffer , 0 , sizeof(buffer));

    int readSize = read(ds18b20_fd , buffer , 2);

    if(-1 == readSize)
    {
        printf("failed to read temp data\n");
       // return -1;
    }

    printf("temp data is 0x%02X\n" , buffer[0]);
    //return 0;

}   

