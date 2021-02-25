//����һ ��׼print ���������#include <stdio.h>
//����� �����豸ͷ�ļ�           #include "contrlDevices.h"
//������ ����ԡ�ҵ�  struct Devices *pdeviceHead������
//������ ��һ��tmpָ�����ҽ�ԡ�ҵƵ��豸 struct Devices *tmp������
//������ ��һ��ͨ�õ����豸����-findDeviceByName,������strcmp���Ƚ����
//������ ����#include<string.h>  --����strcmp������ԭ��
//������ ��ݮ�ɿ��ʼ��           wiringPiSetup������
//����� �����������ĸ��ƣ�������Ҫ�û��ж����룬���Ҽ����ĸ�����
//����� char nameȻ�����û����������tmp����ȥ�����ĸ�ָ��
//����ʮ ������ָ��ģ��ӽ�����pcommandHead������
//����ʮһ ���ֶ��ض��� ѡ����Ȼ��ctrl+б�� ��ݼ��ҳ���

//����1 �����̳߳صĽ���  pthread_create����������
//����2 ����һ������ pthread_t voiceThread ������
//����3 ��voice_pthread ��3.1��������ȥ
//����4 �������������������߳�ʱ���õĺ���  void *voice_thread(void* datas)������
//����5 Ȼ��ͬ����ʽ����socket�߳�
//����6 �ҳ�������ָ�� ����tmp�������������������������ΪvoiceHandler
//����7 Ϊ����������Ҳ�ܵ�������ͷ struct InpuCommand *pCommandhead�ŵ���������-ȫ�ֵ�����
//����8 ����ҵ�voice�Ļ� ����Init����
//����9 �߳����ǲ���return��
//����10 ��ʼ���ɹ���ȡָ�ָ��Ҫ�Ż����� voiceHandler->getCommand(voiceHandler)������
//����11 ���������ָ�� int nread������
//����12 �Ҳ������˳��߳� pthread_exit()������
//����13 �������̲߳��ϵĶ� ���ϵ�ȥ���� nread����while������
//����14 ��Init�������������ṹ�屾���գ���  voiceHandler->Init(voicehandler,NULL,NULL)������

//����1 socket�̵߳Ľ�������������
#include <stdio.h>
#include <string.h>
#include "contrlDevices.h"
#include "inputCommand.h"
#include <unistd.h>
struct Devices *pdeviceHead = NULL;
struct InputCommander *pcommandHead = NULL;
struct InputCommander *socketHandler = NULL;




struct Devices* findDeviceByName(char *name,struct Devices *phead)
{
	struct Devices *zhiZhen = phead;
	if(zhiZhen == NULL)
	{
		return NULL;
	}else{
		while (zhiZhen != NULL)
		{
			if(strcmp(zhiZhen->deviceName,name)==0)
			{
				return zhiZhen;
			}
			zhiZhen = zhiZhen->next;			
		}
		return NULL;
	}
}

//���������̵߳��õĺ��� ����ԭ��ֻҪ������Ϊ�յģ�Init���Ƿ�>=��ʼ������ʼ��֮��û�������ӡһ�У��������ӡ������
void *voice_thread(void* datas)
{
	struct InputCommander *voicehandler;
	
	voicehandler = findDeviceByName("voice",pcommandHead); 
	if(voicehandler == NULL){
		printf("Not find voiceHandler\n");
		pthread_exit();
	}else{
		if(voiceHandler->Init(voicehandler,NULL,NULL) < 0) 
		{
			printf("Init is error");
			pthread_exit();
		}else{
			while(1){
				nread = voiceHandler->getCommand(voicehandler);
				if(nread == 0)
				{
					printf("no data form voice\n");
				}else{
					printf("do device contrl:%s\n",voicehandler->command);
				}
			}
		}
	}
}


//����һ �̺߳��� ���ص���������ָ�루�����͵Ĳ�����
//����� ����init
//������ ��c_fd�ӹ�������Ϊ�ͻ���Ҫ���ֲ��ϵĽ��롣 ����c_fd�ĳ�ʼ��֮�������
//������ �����߳�        pthread_create������
//������ ���߳� pthread_t readThread������ �ŵ�pthread_create����ȥ
//������ ����һ�������̺߳��� void *read_thread(void*datas)������
//������ �ѱ�����ȫ�� intc_fd�����˿�ͷ *socketHandlerҲ�ǵ�
//����� ��Ϊ��read ���Լ���ͷ�ļ�

void *read_thread(void*datas)
{
	int nread;
	nread = read(c_fd, socketMes->command,sizeof(socketMes->command));
	if(n_read == -1){
		perror("read");
	}else if(n_read>0){
		printf("\nget:%d\n",n_read);
	}else{
		printf("client quit\n");
	}
	return n_read;
}

void *socket_thread(void* datas)
{
	int c_fd;
	int n_read = 0;
	pthread_t readThread;
		
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in)); //memset�������
	int clen = sizeof(struct sockaddr_in);
	
	socketHandler = findDeviceByName("socketContrl",pcommandHead); 
	if(socketHandler == NULL){
		printf("Not find socketHandler\n");
		pthread_exit();
	}
	socketHandler->Init(socketHandler,NULL,NULL);
	while(1){
		c_fd = accept(socketHandler->sfd,(struct sockaddr *)&c_addr,&clen);
		pthread_create(&readThread,NULL, read_thread,NULL);//�������߳�ȥ�Խ�
	}
	
}

int main()
{
	//����ԡ�ҵ�
	char name[128];
	pthread_t voiceThread;
	pthread_t socketThread;
	
	struct Devices *tmp = NULL;
	if (wiringPiSetup() == -1)
		{
			return -1;
		}
	struct Devices *pdeviceHead = NULL;
	//�豸������ʼ��
	pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);
	pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
	pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
	pdeviceHead = addSecondflootLightToDeviceLink(pdeviceHead);
	pdeviceHead = addFireToDeviceLink(pdeviceHead);
	

	
	struct InputCommander *pcommandHead = NULL;
	//ָ�����ʼ��
	pcommandHead = addvoiceContrlToInputCommandLink(pcommandHead);
	pcommandHead = addsocketContrlToInputCommandLink(pcommandHead);
	
	//��Ϊtmp����find����֮��ΪNULL�ͷ���NULL��Ȼ������������if
	while (1)
		{
			printf("Select bathroomLight livingroomLight restaurantLight secondflootLight\n");
			printf("Input:\n");
			scanf("%s",name);
			tmp = findDeviceByName(name,pdeviceHead);
			if(tmp != NULL){
					tmp->deviceInit(tmp->pinNum);
					tmp->open(tmp->pinNum);
			}
		}

	
	//pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(start_routine)(void*), void *arg) �ڶ���ֵ���̵߳�����
	//3.�̳߳صĽ���
	//3.1 �����߳�	--ͨ���������Ƶ�
	pthread_create(&voiceThread, NULL, voice_thread, NULL);
	
	//3.2 socket�߳�   --ͨ��TCPЭ����Ƶ�
	pthread_create(&socketThread, NULL, socket_thread, NULL);
	//3.3 ����ͷ�߳�
	
	//3.4 �����߳�
	
	
	return 0;
}
