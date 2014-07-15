#include "conduction.h"

Conduction::Conduction(){
    pthread_cond_init(&sig, NULL);
}

Conduction::~Conduction(){
    pthread_cond_destroy(&sig);
}

void Conduction::wait(){
    pthread_cond_wait(&sig, &(Mutex &mutex));
}

void Conduction::signal(){
    pthread_cond_signal(&sig);
}

void Conduction::broadcast(){
    pthread_cond_broadcast(&sig);
}
