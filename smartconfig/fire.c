//火灾框架的编写
//步骤一 改浴室灯的框架，然后初始化的时候改为INPUT fireInit的由来
//步骤二 定义一个专门读数据返回的函数 firestatusRead函数的由来
//步骤三 结构体也是点引用的方式，然后在mainPro上面加一行供选择，在contrlDevices暴露一下即可

#include "contrlDevices.h"

int fireOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int fireStatusRead(int pinNum)
{
	return digitalRead(pinNum);
}
int fireInit(int pinNum)
{
	pinMode(pinNum,INPUT);
	digitalWrite(pinNum,HIGH);
}
int fireStatus(int status)
{
	
}
struct Devices fire = {
	.deviceName = "fire",
	.pinNum = 25,
	.open = fireOpen,
	.readStatus = fireStatusRead,
	.deviceInit = fireInit,
	.changeStatus = fireStatus
};

//这是一个接口-》需要暴露给头文件，并且在main中调用
//并且 当这个函数被调用的时候-》把bathroomLight加入链表中
struct Devices* addFireToDeviceLink(struct Devices *phead)
{
	if(phead == NULL){
		phead = &fire;
		return phead;
	}else{
		fire.next = phead;
		phead = &fire;
		return phead;
	}
};


