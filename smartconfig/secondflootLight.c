#include <stdio.h>
#include <stlib.h>
#include "contrlDevices.h"

struct Devices* findDevicesName(char *name, struct Devices* phead)
{
    struct Devices* sign = phead;
    if(sign == NULL)
    {
        return NULL;
    }else{
        while(sign != NULL){
            if(strcmp(sign->deviceName,name) == 0)
            {
                return sign;
            }
            sign = sign->next;
        }
        return NULL;
    }
}

int main()
{
    char name[128];

    if(wiringPiSetup() == -1)
    {
        return -1;
    }
    struct Devices* tmp = NULL;
    struct Devices* devicesphead = NULL;
    devicesphead = addBathroomLightToDevicesLink(devicesphead);



    while(1)
    {
        printf("please input");
        scanf("%s",name);
        tmp = findDevicesName(name,devicesphead);
        if(tmp != NULL)
        {
            tmp->deviceInit(tmp->pinNum);
            tmp->open(tmp->pinNum);
        }
    }
    
    
    return 0;
}