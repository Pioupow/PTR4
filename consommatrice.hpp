#ifndef CONSOMMATRICE_HPP
#define CONSOMMATRICE_HPP

#include <cstdint>
#include "thread.hpp"
#include "partage.hpp"
#include "temps.hpp"
#include "screen.hpp"

class TConsommatrice : public TThread
{
    private:
        TScreen *screen;
        int id;
        uint8_t tab[100];
        int useProtection;
    public:
        TConsommatrice(const char *name, void *shared, int policy, int priority, int32_t cpu, int _id, int protect);
        ~TConsommatrice(void);

        void task(void) override;
        bool verifChecksum(uint8_t *pTab);
};

#endif // CONSOMMATRICE_HPP