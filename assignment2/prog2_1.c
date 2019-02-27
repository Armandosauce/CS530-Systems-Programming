#include "prog2_1.h"

TSAFELIST* tSafeConstruct() {

	TSAFELIST* tlist = (TSAFELIST*)malloc(sizeof(TSAFELIST));
	
	tlist->mutex = 0;
	tlist->head = NULL;
	
	return tlist;
}

void tSafeDestruct(TSAFELIST* tlist) {

	free(tlist);

}

TSAFENODE* createNode(mpz_t number) {
  
  TSAFENODE *tnode = (TSAFENODE*) malloc(sizeof(TSAFENODE));
  tnode->next = NULL;
  mpz_init_set(tnode->number, number);
  
  return tnode;
  
}

void tSafeEnqueue(TSAFELIST* tlist, mpz_t number) {
  
  TSAFENODE *tnode = createNode(number);
 
  TSAFENODE* ptr = tlist->head; 
  
  if(!ptr) {
    tlist->head = tnode;
    return;
  }
  
  while(ptr->next) {
    ptr = ptr->next;
  }
  
  ptr->next = tnode;
  
}



TSAFEDATA tSafeDequeue(TSAFELIST* tlist) {

  TSAFEDATA tdata;
  
  TSAFENODE* curr;
  
  if(tlist->head) {
    
    tdata.isValid = 1;
    mpz_init_set(tdata.value, tlist->head->number);
    
    tlist->head = tlist->head->next;
    
  }
  else {
  
    tdata.isValid = 0;
    
  }
  return tdata;
}


void tSafePrint(TSAFELIST* tlist) {

  TSAFENODE* ptr = tlist->head;
  
  int i = 0;
  
  while(ptr) {
  	
  	printf("%d: ", i);
    gmp_printf("%Zd", ptr->number);
    printf("\n");
    ptr = ptr->next;
    i++;   
  
  }
  
}








