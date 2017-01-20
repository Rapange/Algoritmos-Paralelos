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

struct stack{
  struct Node *m_head, *m_tail;
  int m_size, m_cost;
};

void New_stack(struct stack* Q){
  Q->m_head = Q->m_tail = NULL;
  Q->m_size = Q->m_cost = 0;
}

void Push(struct stack *Q, int dato){
  struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
  New_node(new_node,dato);
  if(!Q->m_head){
    Q->m_tail = Q->m_head = new_node;
  }
  else{
    new_node->m_cost = A[Q->m_tail->m_data][new_node->m_data];
    new_node->m_next = Q->m_tail;
    Q->m_tail = new_node;
    Q->m_cost += new_node->m_cost;
  }
  Q->m_size+=1;
}

int Pop(struct stack *Q){
  struct Node *tmp = Q->m_tail;
  int message = -1;
  if(tmp) {
    if(Q->m_head == Q->m_tail) Q->m_tail = Q->m_head = NULL;
    else{
      Q->m_tail = Q->m_tail->m_next;
      tmp->m_next = NULL;
    }
    Q->m_cost -= tmp->m_cost;
    free(tmp);  
    Q->m_size-=1;
  }
  return message;
}

int Empty(struct stack *Q){
  if(!Q->m_head) return 1;
  return 0;
}

void Print_stack(struct stack *Q){
  struct Node* tmp = Q->m_tail;
  while(tmp){
    printf("%d ", tmp->m_data);
    tmp = tmp->m_next;
  }
  printf("\n");
  return;
}

struct Node* Tour_city(struct stack* tour, int i){
  struct Node* tmp = tour->m_tail;
  int cont = 0;
  while(tmp && cont < i){
    tmp = tmp->m_next;
    cont+=1;
  }
  return tmp;
}

int City_count(struct stack* Q){
  return Q->m_size;
}

int Feasible(struct stack* Q, int city){
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

void Update_best_tour(struct stack *Q){
  if(!Best) Best = (struct stack*) malloc(sizeof(struct stack));
  Print_stack(Q);
  printf("Se actualiza\n");
  memcpy(Best,Q,sizeof(struct stack));
  Print_stack(Best);
  return;
}

void Add_city(struct stack *tour, int city){
  Push(tour,city);
  return;
}

void Remove_last_city(struct stack *tour, int city){
  Pop(tour);
  return;
}

void Depth_first_search(struct stack tour){
  int city;
  if(City_count(&tour) == n){
    //Print_stack(&tour);
    //printf("%d\n", City_count(&tour));
    if(Best_tour(&tour)) Update_best_tour(&tour);
  }
  else{
    for(city = 0; city < n; city++)
      if(Feasible(&tour,city)){
	printf("Se agrega %d'\n", city);
	Add_city(&tour,city);
	Depth_first_search(tour);
	Remove_last_city(&tour,city);
      }
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
  Add_city(&Q,0);
  printf("Empieza DFS\n");
  Depth_first_search(Q);
  printf("Termina DFS\n");// %d\n", Best->m_size);
  Print_stack(Best);
  return 0;
}
