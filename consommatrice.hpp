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

        bool verifChecksum(uint8_t *pTab);

    public:
        explicit TConsommatrice(int _id);
        void run(void) override;
};

#endif // CONSOMMATRICE_HPP