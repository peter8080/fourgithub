//卧室灯框架编写
//步骤一 引入头文件-控制设备 
//步骤二 创建一个浴室的结构体              注：用=号
//步骤三 通过.name的形式调用结构体内容                 调灯的名字 开关 初始化 结构体第1.2.3.4的由来
//步骤四 维护灯的状态 结构体第5行的由来
//步骤五 创建开,关，初始化浴室灯的函数
//步骤六 创建一个控制灯状态的函数（传入状态） 上到下第四个函数的由来
//步骤七 把浴室灯加到设备控制链表中--头插法
//步骤八 这个浴室灯的引脚设为22               .pinNum = 22,把pinNum值传进各个函数
//步骤九 初始化浴室灯 pinMode为输出，并且开始为高电平
#include "contrlDevices.h"


int livingroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int livingroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int livingroomLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int livingroomLightCloseStatus(int status)
{
	
}
struct Devices livingroomLight = {
	.deviceName = "livingroomLight",
	.pinNum = 23,
	.open = livingroomLightOpen,
	.close = livingroomLightClose,
	.deviceInit = livingroomLightInit,
	.changeStatus = livingroomLightCloseStatus
};

//这是一个接口-》需要暴露给头文件，并且在main中调用
//并且 当这个函数被调用的时候-》把bathroomLight加入链表中
struct Devices* addLivingroomLightToDeviceLink(struct Devices *phead)
{
	if(phead == NULL){
		phead = &livingroomLight;
		return phead;
	}else{
		livingroomLight.next = phead;
		phead = &livingroomLight;
		return phead;
	}
};


