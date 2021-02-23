//错误一 要比较的话，就会有两个指针 struct Devices *tmp 和struct Devices*devicehead
//错误二 链表的头指针设法:是把自己作为指针参数传进去devicehead = addBathroomLightToDeviceesLink(devicehead);
//错误三 tmp作为对比的指针，他里面带有name还有整个链表devicehead
//错误四 用struct Devices* 而不是int 因为返回的tmp是指针，所以创建的函数为返回值为指针的结构体 
//错误五 代码习惯，对比的函数要先把传进来的指针拿下来，然后看一下是否为空， 函数中sign的由来
//错误六 strcmp就算传进来的值不为空，但是以要用while if return嵌套也可能会有不是这个值的情况出现，所
//错误七 strcmp(sign->deviceName,name)==0 的条件下，如果成立那么就意味着 sign = phead,所以直接return sign
//错误八 比较的函数是strcmp！！！！！！！
//错误九 这就是链表的查找 strcmp里面的比较是用指针的那个结构体里面的名字，和传进来的名字做比较  所以有strcmp(sign->deviceName, name) ,若为零则找到
//错误十 当发现这个tmp找到了之后，先调用初始化，然后调用打开的函数，这个函数看看需要什么参数然后通过tmp来调 如：tmp->deviceInit(tmp->pinNum)
//错误十一 strcmp里面传进去的值是两个指针，所以要用char * name
//错误十二 如果需要不断的进行的东西就需要放入while中， printf scanf
//错误十三 tmp也要放到循环中，因为每一次都要读取新的输入，然后调用比较的函数
#include <stdio.h>
#include <string.h>
#include "contrlDevices.h"

struct Devices* findDeviceByName(char *name,struct Devices* phead)
{
    struct Devices* sign  = NULL;
    if(sign == NULL)
    {
        return NULL;
    }else{
        while(sign != NULL)
        {
            if(strcmp(sign->deviceName,name) == 0)
            {
                return sign;
            }
            sign = sign->next;
        }
        return NULL;
    }

};

int main()
{
    char name[128];
    struct Devices *tmp = NULL;
    if(wiringPiSetup() == -1)
    {
        return -1;
    }
    struct Devices *devicehead = NULL;
    devicehead = addBathroomLightToDevicesLink(devicehead);
    devicehead = addFireToDevicesLink(devicehead);

    while(1)
    {
        printf("select your input\n");
        scanf("%s",name);
        tmp = findDeviceByName(name,devicehead);
        if(tmp != NULL)
        {
            tmp->deviceInit(tmp->pinNum);
            tmp->open(tmp->pinNum);
        }
    }
    return 0;
}