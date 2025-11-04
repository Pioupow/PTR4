#include "Productrice.hpp"
#include "temps.hpp"
#include "screen.hpp"
TProductrice::TProductrice(const char *name, void *shared, bool protect, int policy, int priority, int32_t cpu)
    : TThread(name,shared,policy, priority, cpu)
    {
        screen = (TScreen *)shared;
        partage = (TPartage *)shared;
        useProtection = protect;
        srand(time(NULL));
    }

    TProductrice::~TProductrice(void)
    {
    }

    void TProductrice::task(void)
    {
        signalStart();
        uint8_t tab[100];
        screen->dispStr(1, 7, "La productrice " + std::string(thread.name) + " démarre la production.");
        while(1)
        {
            for (int i = 0; i<99; i++)
                tab[i] = rand() % 256;
            
            tab[99] = calculChecksum(tab);

            if (useProtection)
                partage->protectTab1();

            partage->setTab1(tab);

            if (useProtection)
                partage->unProtectTab1();
                
            usleep(100000); // 100 ms

            for(int i = 0; i<99; i++)
                tab[i] = rand() % 256;

            tab[99] = calculChecksum(tab);

            if (useProtection)
                partage->protectTab2();
            
            partage->setTab2(tab);

            if (useProtection)
                partage->unProtectTab2();
            static int i = 0;
            screen->dispStr(1, 8, "Production recommence dans 100 ms" + std::to_string(i++));
            usleep(100000); // 100 ms et hop on recommence
        }
    }

    uint8_t TProductrice::calculChecksum(uint8_t *tab)
    {
        uint16_t somme = 0;
        for (int i = 0; i < 99; i++)
        {
            somme += tab[i];
        }
        return static_cast<uint8_t>(~somme + 1);
    }