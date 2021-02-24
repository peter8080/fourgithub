//继电器组的代码测试-确保硬件是正常工作的
//步骤一 先通过CRT用SSH模式连接上树莓派
//步骤二 把代码放入树莓派
//步骤三 gcc jiDianQi.c -o led -lwiringPi
//步骤四 ./led 

#include <wiringPi.h>
#include <stdio.h>

#define LED1 21
#define LED2 22
#define LED3 23
#define LED4 24

int main()
{
	int cmd;
	if(wiringPiSetup() == -1)
	{
		return -1;
	}
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);

	digitalWrite(LED1,HIGH);
	digitalWrite(LED2,HIGH);
	digitalWrite(LED3,HIGH);
	digitalWrite(LED4,HIGH);

	while(1){
		scanf("%d",&cmd);
		switch (cmd)
			{
				case 1:
					digitalWrite(LED1,LOW);
					break;
				case 10:
					digitalWrite(LED1,HIGH);
					break;
				case 2:
					digitalWrite(LED2,LOW);
					break;
				case 20:
					digitalWrite(LED2,HIGH);
					break;
				case 3:
					digitalWrite(LED3,LOW);
					break;
				case 30:
					digitalWrite(LED3,HIGH);
					break;
				case 4:
					digitalWrite(LED4,LOW);
					break;
				case 40:
					digitalWrite(LED4,HIGH);
					break;
			}

	}
}
