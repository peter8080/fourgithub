//错误一 普通创建结构体并不需要 *啥的 直接struct Devices bathroomLight = {.pinNum...} ;
//错误二 初始化的时候就应该digitalWrite（pinNum，HIGH）一下
//错误三 头插法返回的是指针，所以要加*，要用自身作为指针
//错误四 在点的结构体里面不用加;号

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


int openbathroomLight(int pinNum)
{
    digitalWrite(pinNum, LOW);
    printf("openbathroomLight is open");
}

int closebathroomLight(int pinNum)
{
    digitalWrite(pinNum, HIGH);
    printf("openbathroomLight is close");
}

int initbathroomLight(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum, 1);
}

struct Devices
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

struct Devices bathroomLight = 
{
    .deviceName = "bathroomLight",
    .pinNum = 21,
    .open = openbathroomLight,
    .close = closebathroomLight,
    .deviceInit = initbathroomLight,
    .next = NULL
};

struct Devices* addBathroomLightToDevicesLink(struct Devices* phead)
{
    if(phead == NULL)
    {
        phead = &bathroomLight;
        return phead;
    }else{
        bathroomLight.next = phead;
        phead = &bathroomLight;
        return phead;
    }
};