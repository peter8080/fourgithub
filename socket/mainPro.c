//错误一 要比较的话，就会有两个指针 struct Devices *tmp 和struct Devices*devicehead
//错误二 链表的头指针设法是把自己作为指针参数传进去devicehead = addBathroomLightToDeviceesLink(devicehead);
//错误三 tmp作为对比的指针，他里面带有name还有整个链表devicehead
//错误四 用struct Devices* 而不是int 因为返回的tmp是指针，所以创建的函数为返回值为指针的结构体 
//错误五 代码习惯，对比的函数要先把传进来的指针拿下来，然后看一下是否为空， 函数中sign的由来
//错误六 strcmp就算传进来的值不为空，但是以要用while if return嵌套也可能会有不是这个值的情况出现，所
//错误七 strcmp(sign,phead)==0 的条件下，如果成立那么就意味着 sign = phead,所以直接return sign
//错误八 比较的函数是strcmp！！！！！！！
//错误九 这就是链表的查找 strcmp里面的比较是用指针的那个结构体里面的名字，和传进来的名字做比较  所以有strcmp(sign->deviceName, name) ,若为零则找到
//错误十 当发现这个tmp找到了之后，先调用初始化，然后调用打开的函数，这个函数看看需要什么参数然后通过tmp来调 如：tmp->deviceInit(tmp->pinNum)
//错误十一 strcmp里面传进去的值是两个指针，所以要用char * name

//错误1 while(1) nread = xx;if(nread == 0){}else if(){}else{};调用声音线程里面的判断用了这么一个结构
//错误2 %s内存放的字符串在 voicehandler->command下 voice_thread最后一个%s输出的由来
//错误3 线程的函数传的参数 void *datas
//错误4 初始化成功之后才开始while(1)
//错误5 else以后是可以直接if的   if(...){}else{ if(){}else{} }的由来
//错误6 Init里面传的是NULL而不是0 Init(voiceHandler,NULL,NULL)的由来
//错误7 c_addr是一个结构体，所以要强制指针转换并且要取地址  
//错误8 sizeof(struct sockaddr_in)  这种有struct的才是一个结构体完整的大小
//test git commit -m "17:52"
#include <stdio.h>
#include <string.h>
#include "contrlDevices.h"

struct Devices *devicehead = NULL;
struct InputCommand *pcommandHead = NULL;

struct Devices* findDeviceByName(char *name,struct Devices* phead)
{
    struct Devices* sign  = NULL;
    if(sign == NULL)
    {
        return NULL;
    }else{
        while(sign != NULL)
        {
            if(strcmp(sign->deviceName,name) == 0)
            {
                return sign;
            }
            sign = sign->next;
        }
        return NULL;
    }

};

void *voice_thread(void *datas)
{
    int nread;
    struct InputCommand * voiceHandler;
    voiceHandler = findDeviceByName("voice",voiceHandler);
    if(voiceHandler == NULL)
    {
        printf("this is not failed");
        pthread_exit();
    }
    else{
        if(voiceHandler->Init(voiceHandler,NULL,NULL) < 0){
            printf("Init is fail");
            pthread_exit();
        }else{
            while(1){
                nread = voiceHandler->getCommand(voiceHandler);
                if(nread == 0){
                    printf("read is 0");
                }else{
                    printf("read is %s",voiceHandler->command;
                }
            }
        }
    }
}
void *read_thread(void *datas)
{

}

void *socket_thread(void *datas)
{
    pthread_t readThread;
    int c_fd;
    struct sockaddr_in c_addr;
    /*原型是extern void *memset(void *buffer, int c, int count)
    buffer为指针或是数组,c是赋给buffer的值,count是buffer的长度.
    这个函数在socket中多用于清空数组.
    如:原型是memset(buffer, 0, sizeof(buffer))*/
    memset(c_addr,0,sizeof(struct sockaddr_in));
    int clen = sizeof(struct sockaddr_in);

    struct InputCommand* socketHandler;
    socketHandler = findDeviceByName("socket",socketHandler);
    if(socketHandler == NULL){
        printf("this socket_thread is failed");
        pthread_exit();
    }
    socketHandler->Init(socketHandler,NULL,NULL)
    else{
        while(1)
        {
            //int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
            c_fd = accept(socketHandler->sfd,(struct sockaddr *)&c_addr,&clen)；
            pthread_create(&readThread,0,read_thread,0);
        }
    }

}
int main()
{
    char name[128];

    pthread_t voiceThread;
    pthread_t socketThread;
    struct Devices *tmp = NULL;
    if(wiringPiSetup() == -1)
    {
        return -1;
    }
    
    devicehead = addBathroomLightToDevicesLink(devicehead);
    devicehead = addFireToDevicesLink(devicehead);

    
    while(1)
    {
        printf("select your input\n");
        scanf("%s",name);
        tmp = findDeviceByName(name,devicehead);
        if(tmp != NULL)
        {
            tmp->deviceInit(tmp->pinNum);
            tmp->open(tmp->pinNum);
        }
    }

    pthread_create(&voiceThread,0,voice_thread,0);
    pthread_create(&socketThread,0,socket_thread,0);
    return 0;
}