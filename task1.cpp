#include "task1.hpp"
#include "temps.hpp"

TTask1::TTask1(const char *name,void *shared,int32_t policy,int32_t priority,int32_t cpu) :
                                                       TThread(name,shared,policy,priority,cpu)
    {
	std::string nameMqtt;

	screen = (TScreen *)shared;
	partage = TPartage::getInstance();

	nameMqtt = TMqtt::getMqttConfig();
	mqtt = new TMqtt(screen,"testMqtt",nameMqtt.c_str());

    screen->dispStr(1,6,"Task MQTT (CPU :  ) :");
    screen->dispStr(30,6,nameMqtt.c_str());
   }

TTask1::~TTask1()
    {
	if(mqtt)
		delete mqtt;
    }

void TTask1::task(void)
    {
    // variable locale
    char strCar[2] = {'-','\0'};
    char bufStr[50];

    // synchronisation démarrage tâche
    signalStart();

    sleep(2); 

    while(1)
		{
		//traitement
		if(strCar[0] == '|')
			strCar[0] = '-';
		else
			strCar[0] = '|';
		screen->dispStr(23,6,strCar);

		if(partage->isChaqnge(1))
			{
			char val[20];

			sprintf(val,"%s",(partage->getModule1())? "on" : "off");
			mqtt->publish(NULL,"module/1",strlen(val),val);

			// ...
			}

		// ...

		if(mqtt->loop() != 0)
			mqtt->reconnect();

		usleep(250000);   // 250 ms
		}
    }
