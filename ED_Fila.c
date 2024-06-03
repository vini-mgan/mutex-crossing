#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    
    char id;
    struct node *next;
    
} Node;

typedef struct queue {
    
    Node* front;
    Node* rear;
    
    int size;
    int currentChar;
    
} Queue;


void enqueue(Queue *rua) {
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    if(rua->currentChar == 26)
        rua->currentChar = 0;
    
    new_node->id = 65 + rua->currentChar;  
    rua->currentChar++;
    
    new_node->next = NULL;  
    
    if (rua->front == NULL && rua->rear == NULL) {  
        rua->front = rua->rear = new_node;
        rua->size++;
        return;  
    }  
    
    rua->rear->next = new_node;  
    rua->rear = new_node;  
    
    rua->size++;
}  

void dequeue(Queue *rua) {
    
    if (rua->front == NULL)   
        return;  
  
    Node* temp = rua->front;
    char element = temp->id;
    
    if (rua->front == rua->rear)
        rua->front = rua->rear = NULL;  
        
    else
        rua->front = rua->front->next;
        
    free(temp); 
    rua->size--;
}

char Car(Queue *rua, int n){
    
    if (rua->front == NULL || n > rua->size)   
        return ' ';
        
    Node* temp = rua->front;
    
    for(int i=1; i<n; i++)
        temp = temp->next;
    
    return temp->id;
}



int main() {

    Queue* rua1 = (Queue*)malloc(sizeof(Queue));
    Queue* rua2 = (Queue*)malloc(sizeof(Queue)); 

    enqueue(rua1);
    enqueue(rua1);
    
    for(int i=0; i<26; i++){
        
        enqueue(rua1);
    
        printf("%c | %c | %c\n", Car(rua1, 1), Car(rua1, 2), Car(rua1, 3));
        
        dequeue(rua1);
    }
    
    return 0;
}
