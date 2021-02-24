//��������ģ����
//����һ ����һ���������Ƶ�����ָ��ṹ��
//����� ָ������voice         �豸����deviceName
//������ ָ��ĳ�ʼ�� {'\0'}������
//������ ��ʼ���������ĳ�ʼ��
//������ ͨ�����뺯��ָ�룬Ȼ��ȡ�����Լ�����ĺ��� voiceInit��voiceGetCommand 
//������ ����ģ��ĳ�ʼ��--֮ǰ����ģ��Ĵ��� 
//������ ���� �������� ��ص�ͷ�ļ�
//����� ��������ȡ��ֵ���д���voiceGetCommand ����fd������voiceInit
//����� read��������ʶ ����#include <unistd.h>
//����ʮ exit��������ʶ #include <stdlib.h>
//����ʮһ ��¶һ����������ģ�飬���ܼ������� 

//����ʮ�� ��ʼ����Ҫ��ָ���豸���ڣ����Զ��ں�������һ��ָ�룬struct InputCommander ������
//��ʮ��  Ȼ�����voicer->deviceName��voicer->fd��voicer->command

//����1 Ū��mainPro�����voice����������voiceGetcommand��getCommand�ǵ���read���� ɾ���ж�����ֻ��Ҫ֪����������ͨ��
//
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "inputCommand.h"

//Init������ָ�����ڣ������ݷŵ���fd���棬������fd
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
	read(voicer->fd, voicer->command, sizeof(voicer->command));

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