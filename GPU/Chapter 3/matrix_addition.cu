#include <stdio.h>
#include <stdlib.h>

__global__
void matAddKernel(float *A, float *B, float *C, int n){
  int i = threadIdx.x + blockDim.x * blockIdx.x;
  if(i < n*n) C[i] = A[i] + B[i];
}

void matAdd(float* A, float* B, float* C, int n){
  int size = n*n*sizeof(float);
  float *d_A, *d_B, *d_C;

  cudaMalloc((void **) &d_A, size);
  cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_B, size);
  cudaMemcpy(d_B,B,size,cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_C, size);

  matAddKernel<<<ceil((n*n)/256.0), 256>>>(d_A,d_B,d_C,n);
  
  cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);

  cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
}


int main(){
  int n,i,j;
  float *h_A,*h_B,*h_C;
  scanf("%d", &n);
  h_A = (float*) malloc(n*n*sizeof(float));
  h_B = (float*) malloc(n*n*sizeof(float));
  h_C = (float*) malloc(n*n*sizeof(float));
  for(i = 0; i < n; i++){
    //scanf("%f", &h_A[i]);
    for(j = 0; j < n; j++)
      h_A[i*n+j] = 1;
  }
  for(i = 0; i < n; i++){
    //scanf("%f", &h_B[i]);
    for(j = 0; j < n; j++)
      h_B[i*n+j] = 1;
  }
  matAdd(h_A,h_B,h_C,n);
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
        printf("%f ", h_C[i*n+j]);
    }
    printf("\n");	
  }
  printf("\n");
  return 0;
}
