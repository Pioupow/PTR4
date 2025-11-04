#include "clavier.hpp"
#include "screen.hpp"
#include "task_heure.hpp"
#include "task_fullpower.hpp"
#include "task_nom.hpp"
#include "task_fichier.hpp"
#include "task_nombre.hpp"
#include "task_config.hpp"
#include "com.hpp"
#include <cstring>

int main(int argc, char *argv[])
{
    char car = 0;

    // Initialisation tâche principale (main)
    TThread::initTaskMain(SCHED_FIFO, 0);

    // Création clavier et console
    TClavier *clavier = TClavier::getInstance();
    TScreen *screen  = new TScreen();
    screen->start();

    // Nouvelles tâches demandées
    TTaskHeure     *tHeure     = new TTaskHeure("Heure", screen, SCHED_RR, 78, 0);
    TTaskFullPower *tFull      = new TTaskFullPower("FullP", screen, SCHED_RR, 10, 0); // priorité la plus faible
    TTaskNom       *tNom       = new TTaskNom("Nom", screen, SCHED_RR, 77, 0, "Nathan");
    TTaskFichier   *tFichier   = new TTaskFichier("Fichier", screen, SCHED_RR, 76, 0);
    TTaskNombre    *tNombre    = new TTaskNombre("Nombre", screen, SCHED_RR, 75, 0);
    TTaskConfig    *tConfig    = new TTaskConfig("Config", screen, SCHED_RR, 74, 0);

    // Démarrage tâches
    tHeure->start();
    tFull->start();
    tNom->start();
    tFichier->start();
    tNombre->start();
    tConfig->start();

    // Traitement tâche principale (affiche message et attend 'q'/'Q' pour quitter)
    screen->dispStr(1,1,"Test RT (NL  09/25/2025)");

    static char buffer[41];
    static int pos = 0;
    int count = 0;
    //memset(buffer, ' ', 40);
    buffer[0] = '\0';
    //buffer[40] = '\0';
    do
    {
        if(clavier->kbhit())
        {
            car = clavier->getch();
            // Afficher caractère sur une ligne max 40 (simple logique)
            //static std::string line;
            if((car=='q') || (car=='Q')) break;
            if(car == '\n' || car == '\r') { /* ignore / ou afficher */ }
            else
            {
                /*if(line.size() < 40) line.push_back((char)car);
                else
                {
                    buffer[pos] = car;
                    pos = (pos + 1) % 40;
                    screen->dispStr(1, 14, buffer);
                }*/
               if(count < 40)
               {
                   buffer[count++] = car;
                   buffer[count] = '\0';
               }
               else
               {
                  buffer[pos] = car;
                  pos = (pos + 1) % 40;
               }
               screen->dispStr(1, 14, buffer);
            }
        }
        usleep(50000); // 50ms
    }
    while( (car != 'q') && (car != 'Q') );

    // Destruction des tâches
    delete tConfig;
    delete tNombre;
    delete tFichier;
    delete tNom;
    delete tFull;
    delete tHeure;

    // Destruction console
    delete screen;

    return 0;
}