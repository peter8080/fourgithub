//��¥�ƿ�ܱ�д
//����һ ����ͷ�ļ�-�����豸 
//����� ����һ��ԡ�ҵĽṹ��              ע����=��
//������ ͨ��.name����ʽ���ýṹ������                 ���Ƶ����� ���� ��ʼ�� �ṹ���1.2.3.4������
//������ ά���Ƶ�״̬ �ṹ���5�е�����
//������ ������,�أ���ʼ��ԡ�ҵƵĺ���
//������ ����һ�����Ƶ�״̬�ĺ���������״̬�� �ϵ��µ��ĸ�����������
//������ ��ԡ�ҵƼӵ��豸����������--ͷ�巨
//����� ���ԡ�ҵƵ�������Ϊ22               .pinNum = 22,��pinNumֵ������������
//����� ��ʼ��ԡ�ҵ� pinModeΪ��������ҿ�ʼΪ�ߵ�ƽ
#include "contrlDevices.h"


int secondflootLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int secondflootLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int secondflootLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int secondflootLightCloseStatus(int status)
{
	
}
struct Devices secondflootLight = {
	.deviceName = "secondflootLight",
	.pinNum = 24,
	.open = secondflootLightOpen,
	.close = secondflootLightClose,
	.deviceInit = secondflootLightInit,
	.changeStatus = secondflootLightCloseStatus
};

//����һ���ӿ�-����Ҫ��¶��ͷ�ļ���������main�е���
//���� ��������������õ�ʱ��-����bathroomLight����������
struct Devices* addSecondflootLightToDeviceLink(struct Devices *phead)
{
	if(phead == NULL){
		phead = &secondflootLight;
		return phead;
	}else{
		secondflootLight.next = phead;
		phead = &secondflootLight;
		return phead;
	}
};


