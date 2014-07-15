#include "Condition.h"

Condition::Condition(pthread_cond_t &sig)
    :signal(sig)
{
    pthread_cond_init(&signal, NULL);
}

Condition::~Condition(){
    pthread_cond_destroy(&signal);
}

void Condition::wait(pthread_mutex_t &mutex){
    pthread_cond_wait(&signal, mutex);
}

void Condition::signal(pthread_cond_t &sig){
    pthread_cond_signal(sig);
}

void Condition::broadcast(pthread_cond_t &sig){
    pthread_cond_broadcast(sig);
}
