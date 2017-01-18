#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

struct queue** queues;
int thread_count;
int done_sending;

struct Node{
  int m_data;
  struct Node* m_next;
};

void New_node(struct Node* node, int data){
  node->m_data = data;
  node->m_next = NULL;
}

struct queue{
  struct Node *m_head, *m_tail;
  int enqueued, dequeued;
};

void New_queue(struct queue* Q){
  Q->m_head = Q->m_tail = NULL;
  Q->enqueued = Q->dequeued = 0;
}

void Push(struct queue *Q, int dato){
  struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
  New_node(new_node,dato);
  if(!Q->m_head){
    Q->m_tail = Q->m_head = new_node;
    return;
  }
  Q->m_tail->m_next = new_node;
  Q->m_tail = new_node;
  Q->enqueued+=1;
}

int Pop(struct queue *Q){
  struct Node *tmp = Q->m_head;
  int message = -1;
  if(tmp) {
    if(Q->m_head == Q->m_tail) Q->m_tail = NULL;
    Q->m_head = tmp->m_next;
    message = tmp->m_data;
    tmp->m_next = NULL;
    free(tmp);
    Q->dequeued+=1;
  }
  return message;
}

int Empty(struct queue *Q){
  if(!Q->m_head) return 1;
  return 0;
}



void Send_msg(){
  int x = rand() % thread_count,msg = rand() % thread_count;
  #pragma omp critical
  Push(queues[x],msg);
}

void Try_receive(int my_rank){
  //while(Empty(queues[my_rank])) Pop(queues[my_rank]);
  int queue_size = queues[my_rank]->enqueued - queues[my_rank]->dequeued;
  int message;
  if(queue_size == 0) return;
  else if(queue_size == 1)
   #pragma omp critical
    message = Pop(queues[my_rank]);
  else
    message = Pop(queues[my_rank]);
  printf("%d\n", message);
}

int Done(int my_rank){
  int queue_size = queues[my_rank]->enqueued - queues[my_rank]->dequeued;
  //printf("%d %d %d\n", queue_size, done_sending, omp_get_num_threads());
  if(queue_size == 0 && done_sending == thread_count) {return 1;}
  else return 0;
}

void message_passing(int my_rank, int send_max){
  int sent_msgs;
  thread_count = omp_get_num_threads();
  //printf("%d\n", my_rank);
  for(sent_msgs = 0; sent_msgs < send_max; sent_msgs++){
    Send_msg();
    Try_receive(my_rank);
  }
  //printf("Mensajes enviados en thread: %d\n", sent_msgs);
  done_sending+=1;
  while(Done(my_rank)==0){
    //printf("Es %d\n", Done(my_rank));
    Try_receive(my_rank);
  }
}

int main(int argc, char* argv[]){
  int thread_count = strtol(argv[1], NULL, 10);
  int i, send_max;
  time_t t;
  srand((unsigned) time(&t));
  done_sending = 0;
  scanf("%d", &send_max);
  queues = malloc(thread_count * sizeof(struct queue*));
  for(i = 0; i < thread_count; i++){
    queues[i] = (struct queue*) malloc(sizeof(struct queue));
    New_queue(queues[i]);
  }
  Push(queues[0],3);
  //printf("%d\n", queues[0]->m_head->m_data);
#pragma omp parallel num_threads(thread_count)
  message_passing(omp_get_thread_num(), send_max);
  return 0;
}
