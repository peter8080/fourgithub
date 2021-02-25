//socket 控制模块框架
//步骤一 创建一个声音控制的输入指令结构体
//步骤二 指令名叫voice         设备名叫deviceName
//步骤三 指令的初始化 {'\0'}的由来
//步骤四 初始化，声音的初始化
//步骤五 通过引入函数指针，然后去调用自己定义的函数 voiceInit和voiceGetCommand 
//步骤六 声音模块的初始化--之前声音模块的代码 
//步骤七 引入 声音串口 相关的头文件
//步骤八 对声音获取的值进行处理voiceGetCommand 它的fd来自于voiceInit
//步骤九 read函数不认识 所以#include <unistd.h>
//步骤十 exit函数不认识 #include <stdlib.h>
//步骤十一 暴露一下声音控制模块，才能加入链表 

//步骤1 把声音模版改一下 然后加入socket套接字 先要加入以前写的代码的头文件
//步骤2 初始化 改socketInit函数的由来 1.socket 创建套接字的由来，以及一些通信协议，端口的校证 socket后三行的由来
//步骤3   bind的由来 传socker信息指针进socket函数 int socketInit(struct InputCommander *socketMes)的由来
//步骤4 atoi 字符串变成整数 所以要有atoi(socketMes->port)
//步骤5 在结构体里面对端口号和ip地址进行赋值  .port = 8887的由来
//步骤6 进行初始化到listen 有返回值的函数，return s_fd的由来
//步骤7 创建好了s_addr，要养成习惯memset一下
//步骤8 让socketInit和socketGetCommand联系起来 socketMes->sfd = s_fd的由来
//步骤9 获得指令只需要做accept和read

//步骤一 socket初始化 有这么一个结构体出现在创建和绑定上面 s_addr  struct sockaddr_in的由来 
//步骤二 清空一下这个结构体 memset(&s_addr,0,sizeof(struct sockaddr_in))的由来 
//步骤三 启动socket向它传递我们的通信协议AF_INET，SOCK_STREAM流格式套接字                         0->自动UDP或者TCP三个值，启动失败会返回-1，否则是一个值，后面绑定和监听才能利用这一值来进行操作
//步骤四 固定Ipv4 ，转端口号，转IP地址   s_addr.sin_family的由来 s_addr.sin_port = htons(atoi(socketMes->port))的由来 inet_aton(socketMes->ipAddress,&s_addr.sin_addr)的由来
//步骤五 由于bind函数第二个参数 在绑定中中间无法使用 sockaddr_in，但是后面算长度要用，bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in))的由来
//步骤六 开始监听s_fd，listen(s_fd，10)的由来
//步骤七 赋值s_fd socketMes->sfd = s_fd 的由来
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


int socketInit(struct InputCommander *socketMes,char *ipAddress,char *port)
{
	//1.socket 创建套接字，然后AF_INET宏和SOCK_STREAM宏头文件包含了
	int s_fd;
	struct sockaddr_in s_addr;  //socket库里面的结构体
	memset(&s_addr,0,sizeof(struct sockaddr_in)); //memset数据清空 

	s_fd = socket(AF_INET, SOCK_STREAM, 0);//IPV4 流式套接字 0->自动UDP或者TCP
	if(s_fd == -1){
		perror("socket");
		exit(-1);
	}

	s_addr.sin_family = AF_INET;//IPV4
	s_addr.sin_port = htons(atoi(socketMes->port)); //转端口号：传进来的值是字符串 atoi的由来 变字符串为整数 
	inet_aton(socketMes->ipAddress,&s_addr.sin_addr);//转IP：用这个inet_aton把ip地址转为了32位的
	
	//2.bind  绑定
	
	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in)); //(struct sockaddr*)bind固定的结构体类型来的 

	//3.listen 监听
	listen(s_fd,10);//10里面有三次握手

	//给socketGetcommand留的
	socketMes->sfd = s_fd;
	return s_fd;
}

int socketGetCommand(struct InputCommander *socketMes)
{
	int c_fd;
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in)); //memset数据清空

	//4.accept（接受）
	int clen = sizeof(struct sockaddr_in);
	c_fd = accept(socketMes->sfd,(struct sockaddr *)&c_addr,&clen);

	//5.read
	int n_read = 0;
	
	n_read = read(c_fd, socketMes->command,sizeof(socketMes->command));
	if(n_read == -1){
		perror("read");
	}else if(n_read>0){
		printf("\nget:%d\n",n_read);
	}else{
		printf("client quit\n");
	}
	return n_read;
}

struct InputCommander socketCortrl = {
	.commandName =  "socketContrl",
	.command = {'\0'},
	.Init = socketInit,
	.getCommand = socketGetCommand,
	.log = {'\0'},
	.port = "8887",
	.ipAddress = "192.168.1.108",
	.next = NULL
};

struct InputCommander* addsocketContrlToInputCommandLink(struct InputCommander* phead)
{
	struct InputCommander* sign = phead;
	if(sign == NULL){
		sign = &socketContrl;
		return sign;
	}else{
		socketContrl.next = sign;
		sign = &socketContrl;
		return sign;
	}
};

