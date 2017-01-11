#include <stdio.h>
#include <string.h>
#include <mpi.h>

void My_Allreduce(int local[], int global[], int count,  int TAM){
  //printf("%d %d\n", local[1], sum[1]);
  int split = 2, holder, index;
  while(split <= TAM){
    //printf("asdf\n");
    if(count % split < split/2) index = count+(split/2);
    else index = count - (split/2);
    MPI_Send(&global[count],1,MPI_INT,index,0,MPI_COMM_WORLD);
    MPI_Recv(&holder,1,MPI_INT,index,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    global[count]+=holder;
    //printf("%d\n", count);
    split = split*2;
    //printf("%d\n",sum[count]);
  }
  //printf("holee\n");

}

int main(void){
  int comm_sz;
  int my_rank;
  int local[8] = {5,2,-1,-3,6,5,-7,2};
  int global[8] = {5,2,-1,-3,6,5,-7,2};
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  My_Allreduce(local,global,my_rank,8);
  //printf("jodfsd\n");
  printf("Proceso %d tiene valor %d\n", my_rank,global[my_rank]);
  MPI_Finalize();
  return 0;

}
