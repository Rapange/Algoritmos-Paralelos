#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#define MAX 100

int thread_count;

void Tokenize(char* lines[], int line_count, int thread_count){
  int my_rank, i, j;
  char *my_token;
  char *saveptr_p;
#pragma omp parallel num_threads(thread_count) default(none) private(my_rank,i,j,my_token,saveptr_p) shared(lines,line_count)
  {
    my_rank = omp_get_thread_num();
#pragma omp for schedule(static,1)
    for(i = 0; i < line_count; i++){
      printf("Thread %d > line %d = %s", my_rank, i, lines[i]);
      j = 0;
      my_token = strtok_r(lines[i], " \t\n", &saveptr_p);
      while(my_token != NULL){
	printf("Thread %d > token %d = %s\n", my_rank, j, my_token);
	my_token = strtok_r(NULL, " \t\n", &saveptr_p);
	j++;
      }
			   
    }
  }
}
	      
int main(int argc, char* argv[]){
  thread_count = strtol(argv[1],NULL,10);
  int line_count,i;
  scanf("%d%*c", &line_count);
  char** lines;
  lines = malloc(line_count * sizeof(char*));
  for(i = 0; i < line_count; i++){
    lines[i] = malloc((MAX+1)*sizeof(char));
  }

  for(i = 0; i < line_count; i++){
    fflush(stdin);
    fgets(lines[i], MAX+1, stdin);
  }
  
  Tokenize(lines,line_count,thread_count);
  return 0;
}
