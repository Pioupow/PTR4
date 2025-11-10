#ifndef PARTAGE_HPP
#define PARTAGE_HPP

#include "singleton.hpp"
#include "mutex.hpp"
#include <array>
#include <cstdint>

class TPartage : public TSingleton<TPartage> {
    friend class TSingleton<TPartage>;
private:
    std::array<bool, 6> etatModules;
    TMutex mutexEtat;
    bool changement;

    TPartage(void);

    TPartage(const TPartage &) = delete;
    TPartage &operator=(const TPartage &) = delete;

public:
    bool getEtatModule(uint8_t index);
    void setEtatModule(uint8_t index, bool etat);
    void toggleEtatModule(uint8_t index);
    void getTousEtats(bool *dest);
    bool getChangement(void);
    void resetChangement(void);

};

#endif // PARTAGE_HPP