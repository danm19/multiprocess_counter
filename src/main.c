
#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <unistd.h> /* fork() */
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
  
	  int *qtde_num, *n ,i = 0, j = 2, *k, fail = 0, *num, num_primos, *vet_aux, maior = 0, stop = 0, ok = 0;
	  char numero, *recebnum; 

	  int protection = PROT_READ | PROT_WRITE;
	  int visibility = MAP_SHARED | MAP_ANON;

	  pid_t filho[3];
	
	  num = malloc(64*sizeof(int));
	  qtde_num = malloc(sizeof(int));		
          k = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);

	  (*qtde_num) = 0;
	
	  while (scanf("%d", &num[i]) != -1){    
	       printf("numero: %d\n", num[i]);
	       i++;    
	       (*qtde_num)++;
	  }   	  

	  vet_aux = (int*) mmap(NULL, sizeof(int)*(*qtde_num), protection, visibility, 0, 0);
	
          for (i = 0; i < (*qtde_num); i++)
	      vet_aux[i] = -1;
	
	  for (*k = 0; *k < (*qtde_num); (*k)++){

	      if (vet_aux[*k] == -1){

	      filho[*k] = fork();

		      if (filho[*k] == 0){

			 while (j < 10 && fail == 0){ 
			      if (((num[*k] % j == 0) && (j != num[*k])) || (num[*k] == 1)){ 
				    fail = 1; 
				    vet_aux[*k] = 0;

			      }
			      else if (j == 9)		
				    vet_aux[*k] = 1;			
 
			      j++;				
	
			 }

		         exit(0);

		    }

	      } 
	 
	}


	for (i = 0; i < (*qtde_num); i++)
	    waitpid(filho[i], NULL, 0);
	       
	for (i = 0; i < (*qtde_num); i++)
	    if (vet_aux[i] == 1)
		num_primos++;
	
        printf ("Total: %d\n", num_primos);


	return 0;

}
