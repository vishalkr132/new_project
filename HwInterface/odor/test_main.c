#include <stdio.h>
#include <unistd.h>

#include "hw_odor_sensor.h"
st_OdorSensor odor_t;

int main()
{
    int ret = ODOR_fnInit(2400 , "/dev/ttyCH9344USB6");
    printf("ret is %d\n" , ret);

    while(1)
    {
        int ret = ODOR_fnReadData(&odor_t);
        sleep(1);
    }

    return 0;
}