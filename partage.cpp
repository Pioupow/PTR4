#include "partage.hpp"
#include <cstring>

TPartage::TPartage(void)
    : controleOk(0),
      controleBad(0)
{
    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));
}

void TPartage::getTab1(uint8_t *pTab, copy_t type)
{
    switch (type)
    {
    case FULL:
        memcpy(pTab, tab1, sizeof(tab1));
        break;
    case FIRST_HALF:
        memcpy(pTab, tab1, sizeof(tab1) / 2);
        break;
    case SECOND_HALF:       
        memcpy(pTab, tab1 + sizeof(tab1) / 2, sizeof(tab1) / 2);
        break;
    }
}

void TPartage::setTab1(uint8_t *p_Tab)
{
    memcpy(tab1, p_Tab, sizeof(tab1));
}

void TPartage::getTab2(uint8_t *pTab, copy_t type)
{
    switch (type)
    {
    case FULL:
        memcpy(pTab, tab2, sizeof(tab2));
        break;
    case FIRST_HALF:
        memcpy(pTab, tab2, sizeof(tab2) / 2);
        break;
    case SECOND_HALF:
        memcpy(pTab, tab2 + sizeof(tab2) / 2, sizeof(tab2) / 2);
        break;
    }
} 

void TPartage::setTab2(uint8_t *p_Tab)
{
    memcpy(tab2, p_Tab, sizeof(tab2));
}

void TPartage::incControleOk(void)
{
    mutexCtrl.take();
    controleOk++;
    mutexCtrl.release();
}

void TPartage::incControleBad(void)
{
    mutexCtrl.take();
    controleBad++;
    mutexCtrl.release();
}

uint32_t TPartage::getControleOk(void)
{
    uint32_t val;
    mutexCtrl.take();
    val = controleOk;
    mutexCtrl.release();
    return val;
}

uint32_t TPartage::getControleBad(void)
{
    uint32_t val;
    mutexCtrl.take();
    val = controleBad;
    mutexCtrl.release();
    return val;
}

void TPartage::protectTab1(void)
{
    mutexTab1.take();
}

void TPartage::unProtectTab1(void)
{
    mutexTab1.release();
}

void TPartage::protectTab2(void)
{
    mutexTab2.take();
}

void TPartage::unProtectTab2(void)
{
    mutexTab2.release();
}