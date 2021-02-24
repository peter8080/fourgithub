//错误一 结构体的话后面直接struct xxx{};  函数的话直接就int xxx(){}

#include <stdio.h>
#include <stdlib.h>

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

};

struct InputCommand* addvoiceContrlToInputCommandLink(struct Input InputCommand* phead);


