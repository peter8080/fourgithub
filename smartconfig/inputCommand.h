//����ָ��ͷ�ļ�
//����һ ��ʼ������ ������������(����ָ����÷�)
//����� Ȼ��ͨ��ָ��� ���ĸ�������������ָ����÷���
//������ getCommand������command���ٲ�����ϵ �ڶ���������
//������ �����־��Ҫ�ռ� �����������
//������ �ṹ��ָ��ر���next �����е�����

//������ Ū�����еĵƺͻ���ģ��֮�������Ū�����Ŀ��ƣ��ȼ�ͷ�ļ�
//������ ��Ҫ��һ��deviceName������ģ�� deviceName������
//����� ����һ��fd         voiceContrl����ģ�������᷵��fd 
//����� �����ͷ�巨��������main����inputCommand.hȻ���ٵ��õ�voiceControl.c

//����ʮ socketҪ��ip�Ͷ˿�port char port[12] char ipAddress[32]������
//����ʮһ socketGetCommandҪ�õ�s_fd int sfd������
//����ʮ�� �Žӿڽ���
#include <wiringPi.h>
#include <stdlib.h>

struct InputCommander
{	
	char commandName[128];//ָ������
	char deviceName[128];//�豸����
	char command[32];//ָ��
	int (*Init)(struct InputCommander *voicer,char *ipAddress,char *port);//����ָ���ַ���˿ں�
	int (*getCommand)(struct InputCommander *voicer);
	char log[1024];//��־
	int fd;
	char port[12];
	char ipAddress[32];
	int sfd;
	struct InputCommander *next;
};

struct InputCommander* addvoiceContrlToInputCommandLink(struct InputCommander* phead);
struct InputCommander* addsocketContrlToInputCommandLink(struct InputCommander* phead);


