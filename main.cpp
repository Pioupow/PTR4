#include "partage.hpp"
#include "screen.hpp"
#include "clavier.hpp"
#include "tacheMqtt.hpp"
#include "configuration.hpp"
#include <unistd.h>
#include <iostream>
#include <cstdio>

int main(int argc, char *argv[])
{
    // Création clavier et console
    TScreen *screen  = new TScreen();
    screen->start();
    screen->dispStr(1, 1, "Lab5 - MQTT");
    screen->dispStr(1,2,"Initialisation du système MQTT...");
    TClavier *clavier = TClavier::getInstance();
    TPartage *partage = TPartage::getInstance();
    
    TacheMqtt *mqttTask = new TacheMqtt("TacheMqtt", screen, SCHED_FIFO, 80, 0);
    TThread::initTaskMain(SCHED_FIFO, 0);
    mqttTask->start();
    screen->dispStr(1,3,"Appuyez sur 1..6 pour changer L'état, 'Q' pour quitter.");

    bool running = true;
    bool etats[6] = {false, false, false, false, false, false};

    while(running)
    {
        partage->getTousEtats(etats);
        for (int i = 0; i < 6; ++i)
        {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "Module %d : %s", i + 1, etats[i] ? "ON " : "OFF");
            screen->dispStr(1, 6 + i, buffer);
        }

        int car = clavier->kbhit() ? clavier->getch() : -1;
        if (car != -1)
        {
            if (car >= '1' && car <= '6')
            {
                int moduleIndex = car - '1';
                bool nouvelEtat = !etats[moduleIndex];
                partage->setEtatModule(moduleIndex, nouvelEtat);
            }
            else if (car == 'Q' || car == 'q')
            {
                running = false;
            }
        }
        usleep(100000); // 100 ms

    }
    delete mqttTask;
    delete screen;
    return 0;
    
}