//步骤一 标准print 所以有这句#include <stdio.h>
//步骤二 控制设备头文件           #include "contrlDevices.h"
//步骤三 调用浴室灯  struct Devices *pdeviceHead的由来
//步骤四 设一个tmp指针来找叫浴室灯的设备 struct Devices *tmp的由来
//步骤五 做一个通用的找设备函数-findDeviceByName,里面用strcmp来比较相等
//步骤六 加上#include<string.h>  --用了strcmp函数的原由
//步骤七 树莓派库初始化           wiringPiSetup的由来
//步骤八 由于增加了四个灯，所以需要用户判断输入，并且加了四个链表
//步骤九 char name然后让用户输入进来，tmp负责去找是哪个指令
//步骤十 把声音指令模块加进来，pcommandHead的由来
//步骤十一 出现多重定义 选中它然后ctrl+斜杆 快捷键找出来

//步骤1 声音线程池的建立  pthread_create函数的由来
//步骤2 定义一个变量 pthread_t voice_pthread 的由来
//步骤3 传voice_pthread 到3.1语音里面去
//步骤4 创建声音函数，启动线程时调用的函数  void *voice_thread(void* datas)的由来
//步骤5 然后同样方式创建socket线程
//步骤6 找出声音的指令 所以tmp在声音函数里面的由来，更名为voiceHandler
//步骤7 为了声音函数也能调用链表头 struct InpuCommand *pCommandhead放到了最外面-全局的由来
//步骤8 如果找到voice的话 调用Init函数
//步骤9 线程内是不能return的
//步骤10 初始化成功获取指令，指令要放回自身 voiceHandler->getCommand(voiceHandler)的由来
//步骤11 接收上面的指令 int nread的由来
//步骤12 找不到则退出线程 pthread_exit()的由来
//步骤13 让声音线程不断的读 不断的去操作 nread外套while的由来
//步骤14 向Init传三个参数，结构体本身，空，空  voiceHandler->Init(voicehandler,NULL,NULL)的由来

//步骤1 socket线程的建立
#include <stdio.h>
#include <string.h>
#include "contrlDevices.h"
#include "inputCommand.h"

struct Devices *pdeviceHead = NULL;
struct InputCommander *pcommandHead = NULL;


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

//启动声音线程调用的函数 工作原理，只要声音不为空的，Init看是否>=初始化，初始化之后没读到则打印一行，读到则打印读到的
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

void *socket_thread(void* datas)
{
	struct InputCommander *sockethandler;
	
	sockethandler = findDeviceByName("socketContrl",pcommandHead); 
	if(sockethandler == NULL){
		printf("Not find sockethandler\n");
		pthread_exit();
	}
	sock
}

int main()
{
	//调用浴室灯
	char name[128];
	pthread_t voice_thread;
	pthread_t socket_thread;
	
	struct Devices *tmp = NULL;
	if (wiringPiSetup() == -1)
		{
			return -1;
		}
	struct Devices *pdeviceHead = NULL;
	//设备工厂初始化
	pdeviceHead = addBathroomLightToDeviceLink(pdeviceHead);
	pdeviceHead = addLivingroomLightToDeviceLink(pdeviceHead);
	pdeviceHead = addRestaurantLightToDeviceLink(pdeviceHead);
	pdeviceHead = addSecondflootLightToDeviceLink(pdeviceHead);
	pdeviceHead = addFireToDeviceLink(pdeviceHead);
	

	
	struct InputCommander *pcommandHead = NULL;
	//指令工厂初始化
	pcommandHead = addvoiceContrlToInputCommandLink(pcommandHead);
	pcommandHead = addsocketContrlToInputCommandLink(pcommandHead);
	
	//因为tmp进入find函数之后为NULL就返回NULL，然后会跳过下面的if
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

	
	//pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(start_routine)(void*), void *arg) 第二个值是线程的属性
	//3.线程池的建立
	//3.1 语音线程	--通过语音控制灯
	pthread_create(&voice_thread, NULL, voice_thread, NULL);
	
	//3.2 socket线程   --通过TCP协议控制灯
	pthread_create(&socket_thread, NULL, socket_thread, NULL);
	//3.3 摄像头线程
	
	//3.4 火灾线程
	
	
	return 0;
}
