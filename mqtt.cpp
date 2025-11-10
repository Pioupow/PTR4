#include "mqtt.hpp"
#include "configuration.hpp"

using namespace std;

TMqtt::TMqtt(void *shared,const char *id,const char *host,int port) : mosqpp::mosquittopp(id)
	{
	screen = (TScreen *)shared;
	partage = TPartage::getInstance();

	mqttTable["module/1"] = &TMqtt::messageModule1;
	mqttTable["module/2"] = &TMqtt::messageModule2;
	mqttTable["module/3"] = &TMqtt::messageModule3;
	mqttTable["module/4"] = &TMqtt::messageModule4;
	mqttTable["module/5"] = &TMqtt::messageModule5;
	mqttTable["module/6"] = &TMqtt::messageModule6;

	mosqpp::lib_init();

	connect(host,port,120);
	}

TMqtt::~TMqtt()
	{
	mosqpp::lib_cleanup();
	}

void TMqtt::on_connect(int rc)
	{
	if(rc == 0)
	{
	    screen->dispStr(1,10,"Connected : OK  ");

	    subscribe(NULL,"module/#",0);
	}
	else
		screen->dispStr(1,10,"Connected : Fail");
	}

void TMqtt::on_message(const struct mosquitto_message *message)
	{
	string topic = message->topic;
	string payload = (char *)message->payload;

	screen->dispStr(1,11,(char *)message->topic);
	screen->dispStr(15,11,"    ");
	screen->dispStr(15,11,(char *)message->payload);

	auto it = mqttTable.find(topic);
	if(it != mqttTable.end())
		it->second(this,payload);
	}

void TMqtt::on_subscribe(int mid,int qos_count,const int *granted_pos)
	{
	screen->dispStr(1,12,"on_subscribe");
	}

void TMqtt::messageModule1(string val)
	{
		screen->dispStr(1,13,"MSG mod1");
	}

void TMqtt::messageModule2(string val)
	{
		screen->dispStr(1,14,"MSG mod2");
	}

void TMqtt::messageModule3(string val)
	{
		screen->dispStr(1,15,"MSG mod3");
	}

void TMqtt::messageModule4(string val)
	{
		screen->dispStr(1,16,"MSG mod4");
	}

void TMqtt::messageModule5(string val)
	{
		screen->dispStr(1,17,"MSG mod5");
	}

void TMqtt::messageModule6(string val)
	{
		screen->dispStr(1,18,"MSG mod6");
	}

string TMqtt::getMqttConfig(string nameFichierConfig)
	{
	}

