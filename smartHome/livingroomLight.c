//���ҵƿ�ܱ�д
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

//����һ���ӿ�-����Ҫ��¶��ͷ�ļ���������main�е���
//���� ��������������õ�ʱ��-����bathroomLight����������
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


