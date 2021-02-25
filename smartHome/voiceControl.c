//语音控制模块框架
//步骤一 创建一个声音控制的输入指令结构体
//步骤二 指令名叫voice         设备名叫deviceName
//步骤三 指令的初始化 {'\0'}的由来
//步骤四 初始化，声音的初始化
//步骤五 通过引入函数指针，然后取调用自己定义的函数 voiceInit和voiceGetCommand 
//步骤六 声音模块的初始化--之前声音模块的代码 
//步骤七 引入 声音串口 相关的头文件
//步骤八 对声音获取的值进行处理voiceGetCommand 它的fd来自于voiceInit
//步骤九 read函数不认识 所以#include <unistd.h>
//步骤十 exit函数不认识 #include <stdlib.h>
//步骤十一 暴露一下声音控制模块，才能加入链表 

//步骤十二 初始化需要打开指定设备串口，所以对于函数传了一个指针，struct InputCommander 的由来
//接十二  然后才有voicer->deviceName，voicer->fd，voicer->command

//步骤1 弄完mainPro里面的voice函数后来调voiceGetcommand，getCommand是调用read函数 删掉判断条件只需要知道串口有无通信
//
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "inputCommand.h"

//Init：打开了指定串口，把数据放到了fd里面，返回了fd
/*文件描述符 — — 内核（kernel）利用文件描述符（file descriptor）来访问文件。文件描述符是非负整数。
打开现存文件或新建文件时，内核会返回一个文件描述符。读写文件也需要使用文件描述符来指定待读写的文件                int fd;
通过结合指针，线程，链表，头插法去控制多设备，以后给小车多加模块的时候，然后运用上*/
int voiceInit(struct InputCommander *voicer,char *ipAddress,char *port)
{
	int fd;
	if((fd = serialOpen(voicer->deviceName,9600)) == -1)
	{
		exit(-1);
	}
	voicer->fd = fd;
	return fd;
}

int voiceGetCommand(struct InputCommander *voicer)
{
	int nread = 0;
	nread = read(voicer->fd, voicer->command, sizeof(voicer->command));
	return nread;
}

struct InputCommander voiceContrl = {
	.commandName =  "voice",
	.deviceName = "/dev/ttyAMA0",   
	.command = {'\0'},
	.Init = voiceInit,
	.getCommand = voiceGetCommand,
	.log = {'\0'},
	.next = NULL
};

struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander* phead)
{
	struct InputCommander* sign = phead;
	if(sign == NULL){
		sign = &voiceContrl;
		return sign;
	}else{
		voiceContrl->next = sign;
		sign = &voiceContrl;
		return sign;
	}
};