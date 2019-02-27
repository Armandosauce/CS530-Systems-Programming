#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <gmp.h>

typedef struct tsafenode {
	struct tsafenode *next;
	mpz_t number;
} TSAFENODE;

typedef struct tsafelist {
	pthread_mutex_t *mutex;
	TSAFENODE *head;
} TSAFELIST;

typedef struct tsafereturndata {
	// True(1)/False(0) if returned data is valid.
	int isValid; 
	mpz_t value;
} TSAFEDATA;


//prog2_1.c
TSAFELIST* tSafeConstruct();
void tSafeDestruct(TSAFELIST*);

TSAFENODE* createNode(mpz_t);

void tSafeEnqueue(TSAFELIST *,mpz_t);
TSAFEDATA tSafeDequeue(TSAFELIST *);

void tSafePrint(TSAFELIST*);

//prog2_2.c

void getNextNum();
void* generatePrimes(void *);

