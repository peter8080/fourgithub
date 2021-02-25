//socket ����ģ����
//����һ ����һ���������Ƶ�����ָ��ṹ��
//����� ָ������voice         �豸����deviceName
//������ ָ��ĳ�ʼ�� {'\0'}������
//������ ��ʼ���������ĳ�ʼ��
//������ ͨ�����뺯��ָ�룬Ȼ��ȥ�����Լ�����ĺ��� voiceInit��voiceGetCommand 
//������ ����ģ��ĳ�ʼ��--֮ǰ����ģ��Ĵ��� 
//������ ���� �������� ��ص�ͷ�ļ�
//����� ��������ȡ��ֵ���д���voiceGetCommand ����fd������voiceInit
//����� read��������ʶ ����#include <unistd.h>
//����ʮ exit��������ʶ #include <stdlib.h>
//����ʮһ ��¶һ����������ģ�飬���ܼ������� 

//����1 ������ģ���һ�� Ȼ�����socket�׽��� ��Ҫ������ǰд�Ĵ����ͷ�ļ�
//����2 ��ʼ�� ��socketInit���������� 1.socket �����׽��ֵ��������Լ�һЩͨ��Э�飬�˿ڵ�У֤ socket�����е�����
//����3   bind������ ��socker��Ϣָ���socket���� int socketInit(struct InputCommander *socketMes)������
//����4 atoi �ַ���������� ����Ҫ��atoi(socketMes->port)
//����5 �ڽṹ������Զ˿ںź�ip��ַ���и�ֵ  .port = 8887������
//����6 ���г�ʼ����listen �з���ֵ�ĺ�����return s_fd������
//����7 ��������s_addr��Ҫ����ϰ��memsetһ��
//����8 ��socketInit��socketGetCommand��ϵ���� socketMes->sfd = s_fd������
//����9 ���ָ��ֻ��Ҫ��accept��read

//����һ socket��ʼ�� ����ôһ���ṹ������ڴ����Ͱ����� s_addr  struct sockaddr_in������ 
//����� ���һ������ṹ�� memset(&s_addr,0,sizeof(struct sockaddr_in))������ 
//������ ����socket�����������ǵ�ͨ��Э��AF_INET��SOCK_STREAM����ʽ�׽���                         0->�Զ�UDP����TCP����ֵ������ʧ�ܻ᷵��-1��������һ��ֵ������󶨺ͼ�������������һֵ�����в���
//������ �̶�Ipv4 ��ת�˿ںţ�תIP��ַ   s_addr.sin_family������ s_addr.sin_port = htons(atoi(socketMes->port))������ inet_aton(socketMes->ipAddress,&s_addr.sin_addr)������
//������ ����bind�����ڶ������� �ڰ����м��޷�ʹ�� sockaddr_in�����Ǻ����㳤��Ҫ�ã�bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in))������
//������ ��ʼ����s_fd��listen(s_fd��10)������
//������ ��ֵs_fd socketMes->sfd = s_fd ������
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
    sa_family_t     sin_family;   //��ַ�壨Address Family����Ҳ���ǵ�ַ����
    uint16_t        sin_port;     //16λ�Ķ˿ں�
    struct in_addr  sin_addr;     //32λIP��ַ
    char            sin_zero[8];  //��ʹ�ã�һ����0���
};*/


int socketInit(struct InputCommander *socketMes,char *ipAddress,char *port)
{
	//1.socket �����׽��֣�Ȼ��AF_INET���SOCK_STREAM��ͷ�ļ�������
	int s_fd;
	struct sockaddr_in s_addr;  //socket������Ľṹ��
	memset(&s_addr,0,sizeof(struct sockaddr_in)); //memset������� 

	s_fd = socket(AF_INET, SOCK_STREAM, 0);//IPV4 ��ʽ�׽��� 0->�Զ�UDP����TCP
	if(s_fd == -1){
		perror("socket");
		exit(-1);
	}

	s_addr.sin_family = AF_INET;//IPV4
	s_addr.sin_port = htons(atoi(socketMes->port)); //ת�˿ںţ���������ֵ���ַ��� atoi������ ���ַ���Ϊ���� 
	inet_aton(socketMes->ipAddress,&s_addr.sin_addr);//תIP�������inet_aton��ip��ַתΪ��32λ��
	
	//2.bind  ��
	
	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in)); //(struct sockaddr*)bind�̶��Ľṹ���������� 

	//3.listen ����
	listen(s_fd,10);//10��������������

	//��socketGetcommand����
	socketMes->sfd = s_fd;
	return s_fd;
}

int socketGetCommand(struct InputCommander *socketMes)
{
	int c_fd;
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in)); //memset�������

	//4.accept�����ܣ�
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

