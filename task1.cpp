#include "task1.hpp"

TTask1::TTask1(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                            TThread(name,shared,policy,priority,cpu)
    {
	screen = (TScreen *)shared;

    screen->dispStr(1,3,"Task 1 :");
    }

TTask1::~TTask1()
    {
    }

void TTask1::task(void)
    {
    // variable locale
    char strCar[2] = {'-','\0'};

    // synchronisation démarrage tâche
    signalStart();

    while(1)
		{
		//traitement
		if(strCar[0] == '|')
			strCar[0] = '-';
		else
			strCar[0] = '|';
		screen->dispStr(10,3,strCar);

		usleep(250000);   // 250 ms
		}
    }
