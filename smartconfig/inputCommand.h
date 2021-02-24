//输入指令头文件
//步骤一 初始化串口 第三个的由来(函数指针的用法)
//步骤二 然后通过指令传入 第四个的由来（函数指针的用法）
//步骤三 getCommand函数和command的再产生联系 第二个的由来
//步骤四 存放日志需要空间 第五个的由来
//步骤五 结构体指针必备的next 第六行的由来

//步骤六 弄完所有的灯和火灾模块之后，在这边弄语音的控制，先加头文件
//步骤七 需要加一个deviceName给声音模块 deviceName的由来
//步骤八 创建一个fd         voiceContrl声音模块调用完会返回fd 
//步骤九 放这个头插法进来，让main调用inputCommand.h然后再调用到voiceControl.c

//步骤十 socket要用ip和端口port char port[12] char ipAddress[32]的由来
//步骤十一 socketGetCommand要用到s_fd int sfd的由来
//步骤十二 放接口进来
#include <wiringPi.h>
#include <stdlib.h>

struct InputCommander
{	
	char commandName[128];//指令名字
	char deviceName[128];//设备名字
	char command[32];//指令
	int (*Init)(struct InputCommander *voicer,char *ipAddress,char *port);//串口指令，地址，端口号
	int (*getCommand)(struct InputCommander *voicer);
	char log[1024];//日志
	int fd;
	char port[12];
	char ipAddress[32];
	int sfd;
	struct InputCommander *next;
};

struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander* phead);
struct InputCommander* addsocketContrlToInputCommandLink(struct InputCommander* phead);


