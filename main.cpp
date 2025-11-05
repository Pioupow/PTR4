#include "Productrice.hpp"
#include "consommatrice.hpp"
#include "partage.hpp"
#include "screen.hpp"
#include "clavier.hpp"
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    // Création clavier et console
    TScreen *screen  = new TScreen();
    screen->start();
    screen->dispStr(1,1,"Initialisation...");
    TClavier *clavier = TClavier::getInstance();
    TPartage *partage = TPartage::getInstance();
    screen->dispStr(1,2,"LAB MUTEX - 2 prod et 2 cons");
    const int policy = SCHED_FIFO;

    // Nouvelles tâches demandées
    TProductrice *prod1 = new TProductrice("Productrice1", screen, policy, 90, 0, 1);
    TConsommatrice *cons1 = new TConsommatrice("Consommatrice1", screen, policy, 89, 0, 1, 1);
    TConsommatrice *cons2 = new TConsommatrice("Consommatrice2", screen, policy, 88, 0, 2, 1);
    TProductrice *prod2 = new TProductrice("Productrice2", screen, policy, 87, 0, 1);
    screen->dispStr(1,3,"Appuyez sur 'q' ou 'Q' pour quitter");
    // Démarrage tâches
    TThread::initTaskMain(SCHED_FIFO, 0);
    prod1->start();
    prod2->start();
    screen->dispStr(1,4,"prod1");
    cons1->start();
    screen->dispStr(8,4,"cons1");
    screen->dispStr(15,4,"prod2");
    cons2->start();
    screen->dispStr(23,4,"cons2");

    // Traitement tâche principale (affiche message et attend 'q'/'Q' pour quitter)

    


    bool running = true;
    while (running)
    {
        uint32_t ok = partage->getControleOk();
        uint32_t bad = partage->getControleBad();

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "Contrôles OK : %10u", ok);
        screen->dispStr(1, 5, buffer);
        snprintf(buffer, sizeof(buffer), "Contrôles KO : %10u", bad);
        screen->dispStr(1, 6, buffer);

        int car = clavier->kbhit() ? clavier->getch() : -1;
        if(car != -1)
        {
            if (car == 'q' || car == 'Q')
            {
                running = false;
            }
        }

        usleep(100000); // 100ms
    }

    // Destruction des tâches
    delete prod1;
    delete cons1;
    delete cons2;
    delete prod2;

    // Destruction console
    delete screen;

    return 0;
}