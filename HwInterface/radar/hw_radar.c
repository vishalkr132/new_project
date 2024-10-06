#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <termios.h>

#include "hw_radar.h"

int32_t radar_fd;

int32_t RADAR_fnInit(int32_t i32_baudrate , uint8_t *path)
{
    radar_fd = 0;
    struct termios tty;
    radar_fd = open(path , O_RDWR);

    if(-1 == radar_fd)
    {
        printf("failed to open radar path %d\n" , radar_fd);
        return -1;
    }
    
    if(tcgetattr(radar_fd , &tty) != 0)
    {
        printf("fauiled get tcgetattr\n");
        return -1;
    }

    tty.c_cflag = cfsetspeed(&tty , i32_baudrate);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS; 
    tty.c_cflag |= CREAD | CLOCAL; // to read data
    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 1;

    if(tcsetattr(radar_fd , TCSANOW , &tty) != 0)
    {
        printf("failed to set attr for radar\n");
        return -1;
    }

    return 0;
}


float RADAR_fnReadData()
{
    uint8_t buffer[RADAR_DATA_SIZE];

    memset(&buffer , 0 , RADAR_DATA_SIZE);
    int32_t readSize = read(radar_fd , buffer , RADAR_DATA_SIZE);

    if(readSize == -1)
    {
        printf("failed to read radar value\n");
        return -1;
    }

    float distance = 0;
    float mag = 0;

    sscanf(buffer ,"{\"dis\": %f , \"mag\": %f}" , &distance , &mag);

    printf("dis is %f and mag is %f\n" , distance , mag);
    return distance;
}



int32_t RADAR_fnClose()
{
    if(radar_fd != -1)
    {
        close(radar_fd);
        radar_fd = 1;
        return 0;
    }
    return -1;
}