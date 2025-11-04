#ifndef PARTAGE_HPP
#define PARTAGE_HPP

#include "singleton.hpp"
#include "mutex.hpp"
#include <cstdint>

class TPartage : public TSingleton<TPartage> {
    friend class TSingleton<TPartage>;
private:
    uint8_t tab1[100];
    uint8_t tab2[100];
    uint32_t controleOk;
    uint32_t controleBad;

    TMutex mutexTab1;
    TMutex mutexTab2;
    TMutex mutexCtrl;

    TPartage(void);

    TPartage(const TPartage &) = delete;
    TPartage &operator=(const TPartage &) = delete;

public:
    enum copy_t
    {
        FULL,
        FIRST_HALF,
        SECOND_HALF
    };

    void getTab1(uint8_t*pTab,copy_t type);
    void setTab1(uint8_t*p_Tab);
    void getTab2(uint8_t*pTab,copy_t type);
    void setTab2(uint8_t*p_Tab);

    void incControleOk(void);
    void incControleBad(void);
    uint32_t getControleOk(void);
    uint32_t getControleBad(void);

    void protectTab1(void);
    void unProtectTab1(void);
    void protectTab2(void);
    void unProtectTab2(void);

};

#endif // PARTAGE_HPP