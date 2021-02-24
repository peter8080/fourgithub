//错误一 函数原型一般为int aa(){}
//错误二 地址和串口号要用char来定义 char port[32]
//错误三 voiceControl没有用到端口号和ip地址，所以可以去掉
//voiceInit的方法 步骤一 先定义一个自身的指针
//步骤二 定义一个文件描述符 开启声音的这个操作，对linux来说会返回一个文件描述符来记录 
//用于接收 声音串口开启的文件描述符  int fd的由来  如果为-1则开启失败 exit(-1)的由来
//步骤三 把拿到的文件描述符的值放到声音的fd的存储区 voicer->fd = fd的由来

//voiceGetCommand 声音获取函数 步骤一 先定义一个自身的指针
//步骤二 定义一个文件描述符 读取声音的操作是一个文件（Linux下一切皆文件） int nread的由来
//步骤三 把上面初始化拿到的值读到command（指令）中 ，read(voicer->fd, voicer ->command,sizeof(voicer->command))的由来

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "inputCommand.h"

/*struct InputCommand
{
    char commandName[128];
    char deviceCommand[32];
    char command[32];
    char port[128];
    char address[128];
    int fd;
    int sfd;
    char log[1024];
    int (*Init)(struct InputCommand *voicer,char *address,char *port);
    int (*getCommand)(struct InputCommand* voicer);

    struct InputCommand* next;

};*/
int voiceInit(struct InputCommand *voicer,char *address,char *port)
{
	int fd;
	if(fd = serialOpen(voicerContrl.deviceName,9600) == -1)
	{
		exit(-1);
	}else{
		voicer->fd = fd;
		return fd;
	}
}

int voiceGetCommand(struct InputCommand* voicer)
{
	int nread;
	nread = read(voicer->fd,voicer->command,sizeof(voicer->command));
	return nread;
}

struct InputCommand voiceContrl = {
	.commandName = "voiceContrl",
	.deviceName = "/dev/ttyAMA0",
	.log = {'\0'},
	.command = {'\0'},
	.Init = voiceInit,
	.getCommand = voiceGetCommand,
	.next = NULL
};

struct InputCommand* addvoiceContrlToInputCommandLink(struct Input InputCommand* phead)
{
	struct InputCommand* tmp = phead;
	if(tmp == NULL){
		tmp = &voiceContrl;
		return tmp;	
	}else{
		voiceContrl.next = tmp;
		tmp = &voiceContrl;
		rerurn tmp;
	}
}; 