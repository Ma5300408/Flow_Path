#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define Vertex 8
#define Min(x,y)(((x)>(y))?(y):(x))

int  F[Vertex][Vertex];
int  R[Vertex][Vertex];

bool visit[Vertex];
int path[Vertex];
int Flow[Vertex];
int Max_Flow;
int  C[Vertex][Vertex]   = { 0, 1, 0, 0, 0, 0, 0, 0,
                               0, 0, 16, 13, 0, 0, 0, 0,
                               0, 0, 0, 4, 12, 0, 0, 0,
                               1, 0, 10, 0, 0, 1, 14, 0,
                               0, 0, 0, 9, 0, 0, 0, 20,
                               0, 0, 0, 0, 0, 0, 0, 0, 
                               0, 0, 0, 0, 7, 0, 0, 4,
                               0, 0, 1, 0, 0, 0, 0, 0
                             };


struct node{
   int data;
  struct node *next;
};

struct node * head = NULL;
struct node * tail = NULL;

int enqueue(int v){
  
  struct node * temp = (struct node*)malloc(sizeof(struct node));
   temp->data = v;
   if(head == NULL)head = tail = temp;
   
  else{
     tail->next = temp;
     tail = temp;

   }

   temp->next = NULL;
   return 0;

}

int dequeue(){

  if(head == NULL){

      tail = NULL;
      return -1;
    }
 

  else{
      struct node * temp;
     temp = head;
     int pop_value  = temp->data;
     head = head->next;
     free(temp);     
     return pop_value;
   }

}

int IsEmpty(){


   if(head == NULL)return 1;
   else return 0;


}


int BFS(int s,int t)
{
    
     int k;
     for(k = 0; k < Vertex; k++)visit[k]= false;
    visit[s] = true;
    path[s] = s;
    enqueue(s);

    while(!IsEmpty()){

       int v = dequeue();
       int j;
       for(j = 0; j < Vertex; j++){

              if(!visit[j] && R[v][j] > 0)
              {
                  //  printf("R[%d][%d]: %d",v,j,R[v][j]);
                    visit[j] = true;
                  //  printf(" path[%d]: %d\n ",j,v);
                    path[j] = v;
                   Flow[j] = Min(Flow[v],R[v][j]);
                   enqueue(j);
                           
                  if(j == t)return Flow[t];
              }
       }
    }

  return 0; 
}


int Edmond_Karp(int s,int t){

    Flow[s] = 1e9;
    int i,j;
    int k,w;

    for(i = 0; i < Vertex; i++)
      for(j = 0; j < Vertex; j++){
          F[i][j] = 0;
          R[i][j] = C[i][j];
       // printf("R[%d][%d]: %d,C[%d][%d]: %d\n",i,j,R[i][j],i,j,C[i][j]);
      }
 
   
    int f,df;
    for(f = 0; df = BFS(s,t); f+=df){
          //   for(k = 0; k < Vertex; k++)printf(" %d ",path[k]);
         //    printf("\n");
             //  getchar();         
              printf(" %d ",df);
         for(i = path[t], j=t; i!=j; i = path[j=i])
         {
             printf("[%d]: %d ",j,i);
             F[i][j] = F[i][j] + df;
             F[j][i] = -F[i][j];
             R[i][j] = C[i][j] - F[i][j];
            // R[j][i] = C[j][i] - F[j][i];  This line make the problem.
         }
        /*printf("\n"); 
       for(k = 0; k < Vertex; k++){
         for(w = 0; w < Vertex; w++){
             printf(" %d ",R[k][w]);
         }
         printf("\n");
       }*/
      /*for(k = 0; k < Vertex; k++){
             if(path[k] != k)path[k] = s;
           printf("path[%d]:%d\n",k,path[k]);
        }*/
    // getchar();
       printf("\n");
    }


   
  return f;
}



int main(){
 
  int k;
for(k = 0; k < Vertex; k++)path[k] = -1;

 printf("Max-Flow: %d\n" ,Edmond_Karp(1,7));


 return 0;
}
