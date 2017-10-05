 #include <time.h>
  
   #define NUM_PHIL     5
 - #define NUM_FORK     5
 + #define NUM_FORK     5 
 + #define NUM_CHAIRS   5/2
  
  sem_t forks[NUM_FORK];
 +sem_t chairs[NUM_CHAIRS];
  int getRand(float max){
    return 1 + (rand() * max) / RAND_MAX;
  }
 @@ -28,16 +30,12 @@ void *philLive(void *threadid){
    {
      printf("I am phil %ld, thinking \n", tid);
      thinking();
 -    if(tid % 2 == 0){
 -      sem_wait(&forks[tid]);
 -      sem_wait(&forks[(tid + 1) % NUM_PHIL]);
 -    }
 -    else{
 -      sem_wait(&forks[(tid + 1) % NUM_PHIL]);
 -      sem_wait(&forks[tid]);
 -    }
 +    sem_wait(&chairs[tid]);
 +    sem_wait(&forks[tid]);
 +    sem_wait(&forks[(tid + 1) % NUM_PHIL]);
      printf("I am phil %ld, eating \n", tid);
      eating();
 +    sem_post(&chairs[tid]);
      sem_post(&forks[tid]);
      sem_post(&forks[(tid + 1) % NUM_PHIL]);
    }
