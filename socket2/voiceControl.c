//����һ ����ԭ��һ��Ϊint aa(){}
//����� ��ַ�ʹ��ں�Ҫ��char������ char port[32]
//������ voiceControlû���õ��˿ںź�ip��ַ�����Կ���ȥ��
//voiceInit�ķ��� ����һ �ȶ���һ�������ָ��
//����� ����һ���ļ������� ���������������������linux��˵�᷵��һ���ļ�����������¼ 
//���ڽ��� �������ڿ������ļ�������  int fd������  ���Ϊ-1����ʧ�� exit(-1)������
//������ ���õ����ļ���������ֵ�ŵ�������fd�Ĵ洢�� voicer->fd = fd������

//voiceGetCommand ������ȡ���� ����һ �ȶ���һ�������ָ��
//����� ����һ���ļ������� ��ȡ�����Ĳ�����һ���ļ���Linux��һ�н��ļ��� int nread������
//������ �������ʼ���õ���ֵ����command��ָ��� ��read(voicer->fd, voicer ->command,sizeof(voicer->command))������

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