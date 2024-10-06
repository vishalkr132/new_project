#include <stdio.h>
#include "hw_ds18b20.h"
#include <unistd.h>

int main()
{
    // printf("console %d, path %s\n", );


    DS18B20_fnInit("/dev/ds18b20"); 
    int i;
    for(i=0;i<10;i++)
    {
    
        float result=0;
        DS18B20_fnReadData();
        sleep(1);
        //printf("temp value is : %lf \n",result);
    }
  
    //HW_DS18B20_fnCloseSensor();

    return 0;
}