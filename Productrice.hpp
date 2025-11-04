#ifndef PRODUCTRICE_HPP
#define PRODUCTRICE_HPP

#include "mutex.hpp"

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include "thread.hpp"
#include "partage.hpp"
#include "screen.hpp"

class TProductrice : public TThread
{
    private:
    TPartage *partage;
    TScreen *screen;
    bool useProtection;

    uint8_t calculChecksum(uint8_t *tab);

    public:
    TProductrice(const char *name, void *shared, bool protect, int policy, int priority, int32_t cpu);
    virtual ~TProductrice();

    void task(void) override;
};

#endif // PRODUCTRICE_HPP
