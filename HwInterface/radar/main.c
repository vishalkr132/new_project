#include <stdio.h>
#include <unistd.h>
#include "hw_radar.h"

int main()
{

    int ret = RADAR_fnInit(115200 , "/dev/ttyCH9344USB5");
    if(ret != 0)
    {
        printf("failed to init radar\n");
    }

    while(1)
    {
        int ret = RADAR_fnReadData();
        sleep(1);
    }
    return 0;
}