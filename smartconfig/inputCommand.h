//错误一 char[] 多大要写一下 一般为char ip[128]
//
#include <wiringPi.h>
#include <stdlib.h>

struct InputCommander
{
    char commandName[128];
    char command[128];
    int sfd;
    char ip;
    char ipAddress;
    
}