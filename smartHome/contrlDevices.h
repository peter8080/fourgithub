//控制设备头文件
//步骤一 创建结构体
//步骤二 声明设备名字的空间               第一  行的由来char deviceName[128];  
//步骤三 声明设备的状态             第二行的由来int status;
//步骤四 开，关，设备初始化,火灾方面的--读状态，改变状态（都用函数指针） 第3.4.5行的由来int (*open)(); 
//步骤五 结构体指针必备的next 第八行的由来struct Devices *next;
//步骤六 声明引脚 第三行的由来int pinNum;
//步骤七 需要传参给函数指针 int (*open)(int pinNum);-后面括号内容的由来 
//步骤八 包含wiringPi的头文件，因为所有设备都会调用我们这个头文件

#include <wiringPi.h>
#include <stdlib.h>

struct Devices
{
	char deviceName[128];  //设备名字
	int status; //状态
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






