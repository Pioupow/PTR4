#include "mutex.hpp"
#include <stdexcept>

TMutex::TMutex(void)
    {
        if (pthread_mutex_init(&mutex, nullptr) != 0)
            {
            throw std::runtime_error("erreur d'init du mutex");
            }
    }

TMutex::~TMutex()
    {
        pthread_mutex_destroy(&mutex);
    }

void TMutex::take(void)
    {
        pthread_mutex_lock(&mutex);
    }

void TMutex::release(void)
    {
        pthread_mutex_unlock(&mutex);
    }  
