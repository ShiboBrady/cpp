#include "conduction.h"
#include "mutex.h"
Conduction::Conduction(){
    pthread_cond_init(&sig, NULL);
}

Conduction::~Conduction(){
    pthread_cond_destroy(&sig);
}

void Conduction::wait(pthread_mutex_t *mutex){
    pthread_cond_wait(&sig, mutex);
}

void Conduction::signal(){
    pthread_cond_signal(&sig);
}

void Conduction::broadcast(){
    pthread_cond_broadcast(&sig);
}

pthread_cond_t *Conduction::getSig(){
    return &sig;
}
