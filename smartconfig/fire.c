//���ֿ�ܵı�д
//����һ ��ԡ�ҵƵĿ�ܣ�Ȼ���ʼ����ʱ���ΪINPUT fireInit������
//����� ����һ��ר�Ŷ����ݷ��صĺ��� firestatusRead����������
//������ �ṹ��Ҳ�ǵ����õķ�ʽ��Ȼ����mainPro�����һ�й�ѡ����contrlDevices��¶һ�¼���

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

//����һ���ӿ�-����Ҫ��¶��ͷ�ļ���������main�е���
//���� ��������������õ�ʱ��-����bathroomLight����������
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


