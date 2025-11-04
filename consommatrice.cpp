#include "consommatrice.hpp"
#include <iostream>
#include <ctime>
#include <chrono>

TConsommatrice::TConsommatrice(int _id): id(_id)
{
}

void TConsommatrice::run(void)
{
    TPartage &partage = TPartage::getInstance();
    TTemps chrono;

    while(1)
    {
        partage.protectTab1();
        partage.getTab1(tab,TPartage::FULL);
        usleep(50000); // 50 ms de traitement
        partage.unProtectTab1();

        if(verifChecksum(tab))
            partage.incControleOk();
        else
            partage.incControleBad();

        usleep(25000);

        partage.protectTab2();
        partage.getTab2(tab,TPartage::FULL);
        usleep(50000); // 50 ms de traitement
        partage.unProtectTab2();

        if(verifChecksum(tab))
            partage.incControleOk();
        else
            partage.incControleBad();
    }
}

bool TConsommatrice::verifChecksum(uint8_t *pTab)
{
    uint8_t somme = 0;
    for (int i = 0; i < 99; i++)
    {
        somme += pTab[i];
    }
    uint8_t checksum = static_cast<uint8_t>(~somme % 256);
    return (checksum == pTab[99]);
}