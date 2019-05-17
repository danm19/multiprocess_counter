#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <unistd.h> /* fork() */
#include <sys/mman.h> 
#include <sys/wait.h>

int verifica_primo(int x){

	int j = 2, fail = 0, aux = 0;

	while (j < 10 && fail == 0){ 
	      
	      if (((x % j == 0) && (j != x)) || (x == 1)){ 
		    fail = 1; 
		    aux = 0;
	      }
	      else if (j == 9)		
		    aux = 1;			

	      j++;				

	 }

         return aux;
}

int main() {
  
	  int qtde_num, *n ,i = 0, j = 2, k, fail = 0, num[64], num_primos, *vet_aux, maior = 0, stop = 0, ok = 0;
	  char numero, *recebnum; 

	  int protection = PROT_READ | PROT_WRITE;
	  int visibility = MAP_SHARED | MAP_ANON;

	  pid_t filho[3];	   

	  qtde_num = 0;
	
	  while (scanf("%d", &num[i]) != (-1)){    
	       i++;    
	       (qtde_num)++;
	  }   	  

	  vet_aux = (int*) mmap(NULL, sizeof(int)*(qtde_num), protection, visibility, 0, 0);
	
          for (i = 0; i < (qtde_num); i++)
	      vet_aux[i] = -1;
	
	  while (k < qtde_num){

	      if (vet_aux[k] == -1){

	      	    filho[k] = fork();

		    if (filho[k] == 0){
			
			 vet_aux[k] = verifica_primo(num[k]);
		         exit(0);
       
		    }

	      } 

	      if (k == 2 && filho[k] == 0){		
		 waitpid(filho[k], NULL, 0);
		 k = 0;     
	      }
	 
	      k++;

	}

	for (i = 0; i < (qtde_num); i++)
	    waitpid(filho[i], NULL, 0);
	       
	for (i = 0; i < (qtde_num); i++)
	    if (vet_aux[i] == 1)
		num_primos++;
	
        printf ("%d\n", num_primos);


	return 0;

}
