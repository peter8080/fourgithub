//�����豸ͷ�ļ�
//����һ �����ṹ��
//����� �����豸���ֵĿռ�               ��һ  �е�����char deviceName[128];  
//������ �����豸��״̬             �ڶ��е�����int status;
//������ �����أ��豸��ʼ��,���ַ����--��״̬���ı�״̬�����ú���ָ�룩 ��3.4.5�е�����int (*open)(); 
//������ �ṹ��ָ��ر���next �ڰ��е�����struct Devices *next;
//������ �������� �����е�����int pinNum;
//������ ��Ҫ���θ�����ָ�� int (*open)(int pinNum);-�����������ݵ����� 
//����� ����wiringPi��ͷ�ļ�����Ϊ�����豸��������������ͷ�ļ�

#include <wiringPi.h>
#include <stdlib.h>

struct Devices
{
	char deviceName[128];  //�豸����
	int status; //״̬
	int pinNum; 
	int (*open)(int pinNum); 
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum); 
	int (*readStatus)(int pinNum);
	int (*changeStatus)(int status);
	struct Devices *next;
	
};

struct Devices* addBathroomLightToDeviceLink(struct Devices *phead);
struct Devices* addRestaurantLightToDeviceLink(struct Devices *phead);
struct Devices* addLivingroomLightToDeviceLink(struct Devices *phead);
struct Devices* addSecondflootLightToDeviceLink(struct Devices *phead);
struct Devices* addFireToDeviceLink(struct Devices *phead);






