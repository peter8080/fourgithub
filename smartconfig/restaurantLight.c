//�����ƿ�ܱ�д
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


int restaurantLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int restaurantLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int restaurantLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int restaurantLightCloseStatus(int status)
{
	
}
struct Devices restaurantLight = {
	.deviceName = "restaurantLight",
	.pinNum = 22,
	.open = restaurantLightOpen,
	.close = restaurantLightClose,
	.deviceInit = restaurantLightInit,
	.changeStatus = restaurantLightCloseStatus
};

//����һ���ӿ�-����Ҫ��¶��ͷ�ļ���������main�е���
//���� ��������������õ�ʱ��-����bathroomLight����������
struct Devices* addRestaurantLightToDeviceLink(struct Devices *phead)
{
	if(phead == NULL){
		phead = &restaurantLight;
		return phead;
	}else{
		restaurantLight.next = phead;
		phead = &restaurantLight;
		return phead;
	}
};


