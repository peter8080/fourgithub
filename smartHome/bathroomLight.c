//ԡ�ҵƿ�ܱ�д
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

int bathroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int bathroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int bathroomLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int bathroomLightCloseStatus(int status)
{
	
}
struct Devices bathroomLight = {
	.deviceName = "bathroomLight",
	.pinNum = 21,
	.open = bathroomLightOpen,
	.close = bathroomLightClose,
	.deviceInit = bathroomLightInit,
	.changeStatus = bathroomLightCloseStatus
};

//����һ���ӿ�-����Ҫ��¶��ͷ�ļ���������main�е���
//���� ��������������õ�ʱ��-����bathroomLight����������
struct Devices* addBathroomLightToDeviceLink(struct Devices *phead)
{
	if(phead == NULL){
		phead = &bathroomLight;
		return phead;
	}else{
		bathroomLight.next = phead;
		phead = &bathroomLight;
		return phead;
	}
};

