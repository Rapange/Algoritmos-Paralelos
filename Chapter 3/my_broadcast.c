#include <stdio.h>
#include <string.h>
#include <mpi.h>

void My_Broadcast(int data_p[], int count, int source_proc, int TAM){
  //printf("%d %d\n", local[1], sum[1]);
  int holder = data_p[source_proc];
  MPI_Status status;
  if(count != 0){
    //printf("asdf\n");
    MPI_Recv(&holder,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    data_p[count]=holder;
    TAM = status.MPI_TAG;
    //printf("%d\n", count);
    while(TAM - count > 1){
      MPI_Send(&holder,1,MPI_INT,(TAM+count)/2,TAM,MPI_COMM_WORLD);
      TAM = (TAM+count)/2;
    }
    if(TAM - count == 1 && TAM != status.MPI_TAG) MPI_Send(&holder,1,MPI_INT,count+1,count+1,MPI_COMM_WORLD);
    //printf("%d\n",sum[count]);
  }
  else {
    //printf("hola %d\n", count);
    while(TAM - count > 1){
      MPI_Send(&holder,1,MPI_INT,(TAM+count)/2,TAM,MPI_COMM_WORLD);
      TAM = (TAM+count)/2;
    }
  }
  //printf("holee\n");

}

int main(void){
  int comm_sz;
  int my_rank;
  int data_p[8] = {3,0,0,0,0,0,0,0};
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  My_Broadcast(data_p,my_rank,0,8);
  if(my_rank!=0){
    printf("Valor de %d en proceso %d\n", data_p[my_rank],my_rank);
  }
  MPI_Finalize();
  return 0;

}
