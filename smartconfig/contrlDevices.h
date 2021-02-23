//错误一 忘记加初始化  int(*deviceInit)(int pinNum)
//错误二 他是最原始的结构体了
//#include <wiringPi.h>
#include <stdlib.h>


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

struct Devices* addBathroomLightToDevicesLink(struct Devices* phead);
struct Devices* addFireToDevicesLink(struct Devices* phead);


