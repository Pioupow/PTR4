#ifndef TACHEMQTT_HPP
#define TACHEMQTT_HPP

#include "thread.hpp"
#include "mqtt.hpp"
#include "partage.hpp"
#include "screen.hpp"
#include "configuration.hpp"
#include <string>
#include <chrono>


class TacheMqtt : public TThread
{
private:
    TMqtt *mqttClient;
    std::string host;
    TScreen *screen;
public:
    TacheMqtt(const char *name, void *shared, int32_t policy, int32_t priority, int32_t cpu);
    ~TacheMqtt();

    void task(void);
};

#endif // TACHEMQTT_HPP