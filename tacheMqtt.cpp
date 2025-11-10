#include "tacheMqtt.hpp"

TacheMqtt::TacheMqtt(const char *name, void *shared, int32_t policy, int32_t priority, int32_t cpu)
    : TThread(name, shared, policy, priority, cpu), mqttClient(nullptr)
{
    TConfiguration config("./mqtt.def");
    host = config.getParametreConfiguration();
    mqttClient = new TMqtt(shared, "ClientMQTT", host.c_str());
}

TacheMqtt::~TacheMqtt()
{
    if (mqttClient)
    {
        delete mqttClient;
        mqttClient = nullptr;
    }
}

void TacheMqtt::task(void)
{
    signalStart();
    TPartage *partage = TPartage::getInstance();
    while(1)
    {
        mqttClient->loop();

        if(partage->getChangement())
        {
            bool etats[6];
            partage->getTousEtats(etats);
            for(int i = 0; i < 6; ++i)
            {
                std::string topic = "module/" + std::to_string(i + 1);
                std::string payload = etats[i] ? "on" : "off";
                mqttClient->publish(nullptr, topic.c_str(), payload.length(), payload.c_str());
            }
            partage->resetChangement();
        }
        usleep(100000); // 100 ms
    }
}

