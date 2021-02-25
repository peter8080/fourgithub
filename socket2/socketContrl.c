//错误一 socket没有设备名，所以用不上deviceName
//错误二 char类型的赋值为 .log = {'\0'}  int类型的赋值为.fd = 0,
//错误三 地址和端口号要用字符串 char *address
//错误四 因为传进来的值是字符串 atoi(socketMes->port)
//错误五 bind绑定中间转换的值是固定的 (struct sockaddr*)&
//错误六 有两个判断的话，用if(n_read == -1){} && else if(n_read == 0){} && else{}
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "inputCommand.h"

//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#include <stdlib.h>
#include <string.h>

/*struct sockaddr_in{
    sa_family_t     sin_family;   //地址族（Address Family），也就是地址类型
    uint16_t        sin_port;     //16位的端口号
    struct in_addr  sin_addr;     //32位IP地址
    char            sin_zero[8];  //不使用，一般用0填充
};*/

/*
struct InputCommand
{
    char commandName[128];
    char deviceName[32];
    char command[32];
    char port[128];
    char address[128];
    int fd;
    int sfd;
    char log[1024];
    int (*Init)(struct InputCommand *voicer,char *address,char *port);
    int (*getCommand)(struct InputCommand* voicer);

    struct InputCommand* next;

};*/
int socketInit(struct InputCommand *socketMes,char *address,char *port)
{
    //创建s_fd
    int s_fd;
    struct sockaddr_in s_addr;
    memset(&s_addr,0,sizeof(s_addr));
    //socket启动
    s_fd = socket(AF_INET,SOCK_STREAM,0)
    if(s_fd == -1)
    {
        error(socket);
        exit(-1;
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(atoi(socketMes->port));
    inet_aton(socketMes->ipAddress,&s_addr.sin_addr);
    //绑定
    bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
    //监听
    listen(s_fd,10);
    //赋值回去
    socketMes->sfd = s_fd;
    return s_fd;
    
}

int socketGetCommand(struct InputCommand *socketMes)
{
    //创建c_fd
    int c_fd;
    struct sockaddr_in c_addr;
    memset(&c_addr,0,sizeof(c_addr));
    //接收accept
    c_fd = accept();
    //read
    int n_read;
    n_read = read(c_fd, sockMes->command,sizeof(srtuct sockaddr_in));

    if(n_read == -1)
    {
        error(n_read);
    }else if(n_read > 0)
    {
        printf("%s",n_read);
    }else
    {
        printf("read is outtime");
    }
    return n_read;
}

struct InputCommand socketContrl = 
{
    .commandName = "socketContrl",
    .log = {'\0'},
    //.fd = 12,
    .command = {'\0'},
    .port = "8880",
    .address = "192.168.1.108",
    .Init = socketInit,
    .getCommand = socketGetCommand,
    .next = NULL
};

struct InputCommand* addsocketContrlToinputCommandLink(struct InputCommand *phead)
{
    struct InputCommand* tmp = phead;
    if(tmp == NULL)
    {
        tmp = &socketContrl;
        return tmp;
    }else{
        socketContrl.next = tmp;
        tmp = &socketContrl;
        return tmp;
    }
};