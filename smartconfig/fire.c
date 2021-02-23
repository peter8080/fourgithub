//错误一 虽然为函数指针但是去看这个open ，他是由int来的，所以我们对返回值没有什么要求

/*struct Devices
{

    char deviceName[128];
    int status;
    int pinNum;
    int (*close)(int pinNum);
    int (*open)(int pinNum);
    int (*read)(int pinNum);
    int (*deviceInit)(int pinNum);
    struct Devices *next;
};
*/

#include "contrlDevices.h"

int fireopen(int pinNum)
{
    digitalWrite(pinNum, LOW);
}

int fireclose(int pinNum)
{
    digitalWrite(pinNum, HIGH);
}

int initFire(int pinNum)
{
    pinMode(pinNum, INPUT);
    digitalWrite(pinNum, LOW);
}

int readfireStatus(int pinNum)
{
    int kk;
    kk = digitalRead(pinNum);
    return kk;
}

struct Devices fire = 
{
    .deviceName = "fire",
    .pinNum = 25,
    .open = fireopen,
    .close = fireclose,
    .deviceInit = initFire,
    .read = readfireStatus,
    .next = NULL
};

struct Devices* addFireToDevicesLink(struct Devices* phead)
{
    if(phead == NULL)
    {
        phead = &fire;
        return phead;
    }else{
        fire.next = phead;
        phead = &fire;
        return phead;
    }
};