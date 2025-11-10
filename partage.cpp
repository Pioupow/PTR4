#include "partage.hpp"
#include <iostream>
#include <cstring>

TPartage::TPartage(void)
    : etatModules{false, false, false, false, false, false},
      changement(false)
{
}

bool TPartage::getEtatModule(uint8_t index)
{
    if (index >= etatModules.size())
        return false;
    mutexEtat.take();
    bool etat = etatModules[index];
    mutexEtat.release();
    return etat;
}
void TPartage::setEtatModule(uint8_t index, bool etat)
{
    if (index >= etatModules.size())
        return;
    mutexEtat.take();
    if (etatModules[index] != etat)
    {
        etatModules[index] = etat;
        changement = true;
    }
    mutexEtat.release();
}
void TPartage::toggleEtatModule(uint8_t index)
{
    if (index >= etatModules.size())
        return;
    mutexEtat.take();
    etatModules[index] = !etatModules[index];
    changement = true;
    mutexEtat.release();
}
void TPartage::getTousEtats(bool *dest)
{
    if(!dest)
        return;
    mutexEtat.take();
    for(size_t i = 0; i < etatModules.size(); ++i)
    {
        dest[i] = etatModules[i];
    }
    mutexEtat.release();
}
bool TPartage::getChangement(void)
{
    mutexEtat.take();
    bool val = changement;
    mutexEtat.release();
    return val;
}
void TPartage::resetChangement(void)
{
    mutexEtat.take();
    changement = false;
    mutexEtat.release();
}