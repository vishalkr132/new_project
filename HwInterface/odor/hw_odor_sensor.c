#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "hw_odor_sensor.h"
#include "../mslogs/err.h"

int32_t i32_Fd;

int32_t baudrate[7] = {B2400, B4800, B9600, B19200, B38400, B57600, B115200};
int32_t baud_rate[7] = {2400 , 4800 , 9600, 19200 , 38400 , 57600 , 115200};

int32_t ODOR_fnInit(int32_t i32_baudrate , char *path)
{
    struct termios tty;
    int32_t ODOR_BAUDRATE = 0;

    i32_Fd = open(path , O_RDWR);
    if(-1 == i32_Fd)
    {
        printf("failed to open uart port %d\n" , i32_Fd);
        return ERR;
    }

    for(int32_t loop = 0; loop < 7; loop++)
    {
        if(i32_baudrate == baud_rate[loop])
        {
            ODOR_BAUDRATE = baudrate[loop];
            break;
        }
    }

    if(tcgetattr(i32_Fd , &tty) != 0)
    {
        return ERR;
    }

    cfsetspeed(&tty , ODOR_BAUDRATE);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_cc[VMIN] = 26;
    tty.c_cc[VTIME] = 0;

    if(tcsetattr(i32_Fd , TCSANOW , &tty) != 0 )
    {
        return ERR;
    }
    return OK;
}

uint8_t checksum(uint8_t *data , int32_t len)
{
    int result = 0;
    for(int i=0; i<len; i++)
    {
        result += data[i];
    }
    return result & 0xFF;
}


int32_t reverse(uint8_t *data)
{
    uint32_t result = 0;
    result = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    return result/1000;
}

int32_t ODOR_fnReadData(st_OdorSensor *odor_t)
{

    char buffer[DATA_SIZE];

    memset(&buffer , 0 , DATA_SIZE);

    int readByte = read(i32_Fd , buffer , DATA_SIZE);

    if(readByte > 0)
    {
        for (int i=0;i<readByte;i++)
        {
            printf("%02X " , buffer[i]);
        }

        printf("\n\n");
    }

    uint8_t recevied_checksum = buffer[DATA_SIZE - 1];
    uint8_t claculate_checksum = checksum(buffer , DATA_SIZE - 1);

    if(recevied_checksum == claculate_checksum)
    {
        odor_t->i32_temperature = reverse(buffer + 1);
        printf("temp is %d\n" ,odor_t->i32_temperature);
    }

    return 0;
    
}

int32_t ODOR_fnClose()
{
    if(i32_Fd != -1)
    {
        close(i32_Fd);
        i32_Fd = -1;
        return 0;
    }
    else
    {
        return -1;
    }
}