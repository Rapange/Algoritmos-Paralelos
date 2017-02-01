#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, **A;

struct Node{
  int m_data, m_cost;
  struct Node* m_next;
};

void New_node(struct Node* node, int data){
  node->m_data = data;
  node->m_next = NULL;
  node->m_cost = 0;
}

void New_queue(struct queue* Q){
  Q->m_head = Q->m_tail = NULL;
  Q->m_size = Q->m_cost = 0;
}

struct queue{
  struct Node* m_head, *m_tail;
  int m_size, m_cost;
}

void Push_queue(struct queue *Q, int dato){
  struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
  New_node(new_node,dato);
  if(!Q->m_head){
    Q->m_tail = Q->m_head = new_node;
  }
  else{
    new_node->m_cost = A[Q->m_tail->m_data][new_node->m_data];
    Q->m_tail->m_next = mew_node;
    Q->m_tail = new_node;
    Q->m_cost += new_node->m_cost;
  }
  Q->m_size+=1;
}

int Pop_queue(struct queue *Q){
  struct Node *tmp = Q->m_head;
  int message = -1;
  if(tmp) {
    if(Q->m_head == Q->m_tail) Q->m_tail = Q->m_head = NULL;
    else{
      Q->m_head = Q->m_head->m_next;
      tmp->m_next = NULL;
    }
    Q->m_cost -= tmp->m_cost;
    free(tmp);  
    Q->m_size-=1;
  }
  return message;
}


struct stack{
  struct queue *m_head, *m_tail;
  int m_size;
};



void New_stack(struct stack* Q){
  Q->m_head = Q->m_tail = NULL;
  Q->m_size = Q->m_cost = 0;
}

void Push(struct stack *Q, struct queue dato){
  struct queue* new_node = (struct queue*) malloc(sizeof(struct queue));
  new_node = &dato;
  if(!Q->m_head){
    Q->m_tail = Q->m_head = new_node;
  }
  else{
    new_node->m_next = Q->m_tail;
    Q->m_tail = new_node;
  }
  Q->m_size+=1;
}

struct queue Pop(struct stack *Q){
  struct Node *tmp = Q->m_tail;
  struct queue message;
  if(tmp) {
    if(Q->m_head == Q->m_tail) Q->m_tail = Q->m_head = NULL;
    else{
      Q->m_tail = Q->m_tail->m_next;
      tmp->m_next = NULL;
    }
    message = &tmp;
    //free(tmp);  
    Q->m_size-=1;
  }
  return message;
}

int Empty(struct stack *Q){
  if(!Q->m_head) return 1;
  return 0;
}

void Print_stack(struct queue *Q){
  struct Node* tmp = Q->m_tail;
  while(tmp){
    printf("%d ", tmp->m_data);
    tmp = tmp->m_next;
  }
  printf("\n");
  return;
}

struct Node* Tour_city(struct queue* tour, int i){
  struct Node* tmp = tour->m_tail;
  int cont = 0;
  while(tmp && cont < i){
    tmp = tmp->m_next;
    cont+=1;
  }
  return tmp;
}

int City_count(struct queue* Q){
  return Q->m_size;
}

int Feasible(struct queue* Q, int city){
  struct Node* tmp = Q->m_tail;
  while(tmp){
    if(tmp->m_data == city){
      return 0;
    }
    tmp = tmp->m_next;
  }
  return 1;
}

struct stack *Best = NULL;
int Best_tour(struct stack *Q){
  printf("Revisa con el mejor!\n");
  if(Best == NULL || Q->m_cost < Best->m_cost){
    printf("Nuevo mejor\n");
    return 1;
  }
  return 0;
}

void Update_best_tour(struct queue *Q){
  if(!Best) Best = (struct queue*) malloc(sizeof(struct queue));
  Print_stack(Q);
  printf("Se actualiza\n");
  memcpy(Best,Q,sizeof(struct queue));
  Print_stack(Best);
  return;
}

void Add_city(struct queue *tour, int city){
  Push_queue(tour,city);
  return;
}

void Remove_last_city(struct queue *tour, int city){
  Pop_queue(tour);
  return;
}

void Depth_first_search(int city){
  struct queue tour;
  struct queue curr_tour;
  struct stack Stack;
  int nbr = n-1;
  new_queue(&tour);
  Add_city(&tour,city);
  Push(&Stack,tour);
  while(Stack->m_size > 0){
    curr_tour = Pop(&stack);
    if(City_count(curr_tour) == n){
      if(Best_tour(curr_tour)){
	Update_best_tour(curr_tour);
      }
    }
    else{
      for(nbr = n-1; nbr >= 1; nbr--){
	if(Feasible(curr_tour,nbr)){
	  Add_city(curr_tour,nbr);
	  Push(&stack, curr_tour);
	  Pop(&curr_tour);
	}
      }
    }
    Free_tour(curr_tour);
  }
  

}

int main(){
  int i, j;
  scanf("%d", &n);
  struct stack Q;// = (struct stack*) malloc(sizeof(struct stack));
  New_stack(&Q);
  A = malloc(n * sizeof(int*));
  for(i = 0; i < n; i++) {
    A[i] = malloc(n * sizeof(int));
    for(j = 0; j < n; j++){
      scanf("%d", &A[i][j]);
    }
  }
  Add_city(0);
  printf("Empieza DFS\n");
  Depth_first_search(Q);
  printf("Termina DFS\n");// %d\n", Best->m_size);
  Print_stack(Best);
  return 0;
}
