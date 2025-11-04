#ifndef CONSOMMATRICE_HPP
#define CONSOMMATRICE_HPP

#include <cstdint>
#include "thread.hpp"
#include "partage.hpp"
#include "temps.hpp"

class TConsommatrice : public TThread
{
    private:
        int id;
        uint8_t tab[100];

        

    public:
        TConsommatrice(const char *name, void *shared, int policy, int priority, int32_t cpu, int _id);
        ~TConsommatrice(void);

        void task(void) override;
        bool verifChecksum(uint8_t *pTab);
};

#endif // CONSOMMATRICE_HPP