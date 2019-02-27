#include "prog2_1.h"

int globalCounter;
pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;
TSAFELIST* numberList;

gmp_randstate_t state;
mp_bitcnt_t B;
int K;
int num_enqueued = 0;

int main(int argc, char* argv[]) {

  TSAFEDATA data;
  pthread_t t1, t2, t3, t4;
  
  if(argc < 3) 
  {
    fprintf(stderr, "Incorrect number of command line arguments!\n");
    return -1;
  }
  
  printf("Assignment #2-2, Armando Perez, armandoperez0001@gmail.com\n");
  
  numberList = tSafeConstruct();
  
  globalCounter = 0;
  gmp_randinit_default(state);
  
  K = atoi(argv[1]);
  B = atoi(argv[2]);
  
  pthread_create(&t1, NULL, generatePrimes, 0);
  pthread_create(&t2, NULL, generatePrimes, 0);
  pthread_create(&t3, NULL, generatePrimes, 0);
  
  while(1) {
    
    usleep(100);
    
    if(pthread_mutex_trylock(&counterguard) != EBUSY) {
      
      data = tSafeDequeue(numberList);
      
      if(globalCounter == K && data.isValid == 0) {
        break;
      }
      
      if(data.isValid == 1) {
        
        gmp_printf("%Zd\n", data);
        
      }
      pthread_mutex_unlock(&counterguard);
    }
  }
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  
  return 0;
}

void getNextNum(mpz_t num) {
  
  mpz_rrandomb(num, state, B);
  //gmp_printf("%Zd\n", num);
  
}

void* generatePrimes(void *arg) {

  long thread_state = (long)(arg);
  int mrabin;
  int temp;
  
  mpz_t number;
  mpz_init(number);
  
  while(thread_state != -1) {
    
    getNextNum(number);
    mrabin = mpz_probab_prime_p(number, 100000);
    
    pthread_mutex_unlock(&counterguard);
    
    //critical section never reached in worker threads, not sure why
    
	  if(globalCounter == K) { 
	  	thread_state = -1;
	  }
		else if(mrabin == 1) {
	    tSafeEnqueue(numberList, number);
	    
	    temp = globalCounter;
	    temp++;
	    globalCounter = temp;
	  }
	  
  	pthread_mutex_unlock(&counterguard);
    
    usleep(2);
  }
  
  return NULL;

}



