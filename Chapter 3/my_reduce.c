#include <stdio.h>
#include <string.h>
#include <mpi.h>

void My_Reduce(int local[], int sum[], int count, int dest_process, int TAM){
  //printf("%d %d\n", local[1], sum[1]);
  int half = TAM/2, holder;
  while(count < half){
    //printf("asdf\n");
    MPI_Recv(&holder,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    sum[count]+=holder;
    //printf("%d\n", count);
    half = half/2;
    //printf("%d\n",sum[count]);
  }
  holder = sum[count];
  if(count!=0) {
    //printf("hola %d\n", count);
    MPI_Send(&holder,1,MPI_INT,count % half,0,MPI_COMM_WORLD);
  }
  //printf("holee\n");

}

int main(void){
  int comm_sz;
  int my_rank;
  int local[8] = {1,1,1,1,1,1,1,1};
  int sum[8] = {1,1,1,1,1,1,1,1};
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  My_Reduce(local,sum,my_rank,0,8);
  //printf("jodfsd\n");
  if(my_rank==0){
    printf("%d\n", sum[0]);
    }
  MPI_Finalize();
  return 0;

}
