#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


typedef struct node {
    
    char id;
    struct node *next;
    
} Node;

typedef struct queue {
    
    Node* front;
    Node* rear;
    
    int size;
    
} Queue;


void enqueue(Queue *rua, int currentChar) {
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    new_node->id = 65 + currentChar;
    
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

char dequeue(Queue *rua) {
  
    Node* temp = rua->front;
    char element = temp->id;
    
    if (rua->front == rua->rear)
        rua->front = rua->rear = NULL;  
        
    else
        rua->front = rua->front->next;
        
    free(temp); 
    rua->size--;
    
    return element;
}

char Car(Queue *rua, int n){
    
    if (rua->front == NULL || n > rua->size)   
        return ' ';
        
    Node* temp = rua->front;
    
    for(int i=1; i<n; i++)
        temp = temp->next;
    
    return temp->id;
}

void view1(Queue* ruas[]){
    
    char c = dequeue(ruas[0]);
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", ruas[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(ruas[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(ruas[0], 1));
        printf("      --+---+--+-------+--+---+--\n");
        printf("rua 2  _ %c _ %c | %c     |   _   _     \n", Car(ruas[1],2), Car(ruas[1],1),mov[0]);
        printf(" (%d)           | %c     | %c   %c    rua 4\n", ruas[1]->size, mov[1], Car(ruas[3],1), Car(ruas[3],2));
        printf("      --+---+--+-------+--+---+--\n");
        printf("               | %c | %c |\n", mov[2], Car(ruas[2],1));
        printf("               | %c     |\n", mov[3]);
        printf("               | %c | %c |\n", mov[4], Car(ruas[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", ruas[2]->size);
        
        usleep(199000);
        system("clear");
        
        i++;
    }
}

void view2(Queue* ruas[]){
    
    char c = dequeue(ruas[1]); //RUA 2
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", ruas[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(ruas[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(ruas[0], 1));
        printf("      --+---+--+-------+--+---+--\n");
        printf("rua 2  _ %c _ %c | %c   %c | %c _ %c _ %c   \n", Car(ruas[1],2), Car(ruas[1],1),
        mov[0], mov[1], mov[2], mov[3], mov[4]);
        printf(" (%d)           |       | %c   %c    rua 4\n", ruas[1]->size, Car(ruas[3],1), Car(ruas[3],2));
        printf("      --+---+--+-------+--+---+--\n");
        printf("               |   | %c |\n", Car(ruas[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(ruas[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", ruas[2]->size);
        
        usleep(199000);
        system("clear");
        
        i++;
    }
}

void view3(Queue* ruas[]){
    
    char c = dequeue(ruas[2]); //RUA3
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", ruas[0]->size);
        printf("               +       +\n");
        printf("               | %c | %c |\n", Car(ruas[0],2), mov[4]);
        printf("               |     %c |\n", mov[3]);
        printf("               | %c | %c |\n", Car(ruas[0], 1), mov[2]);
        printf("      --+---+--+-------+--+---+--\n");
        printf("rua 2  _ %c _ %c |     %c |   _   _     \n", Car(ruas[1],2), Car(ruas[1],1), mov[1]);
        printf(" (%d)           |     %c | %c   %c    rua 4\n", ruas[1]->size, mov[0], Car(ruas[3],1), Car(ruas[3],2));
        printf("      --+---+--+-------+--+---+--\n");
        printf("               |   | %c |\n",Car(ruas[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(ruas[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", ruas[2]->size);
        
        usleep(199000);
        system("clear");
        
        i++;
    }
}

void view4(Queue* ruas[]){
    
    char c = dequeue(ruas[3]); //RUA 4
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", ruas[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(ruas[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(ruas[0], 1));
        printf("      --+---+--+-------+--+---+--\n");
        printf("rua 2  _ %c _ %c |       |   _   _     \n", Car(ruas[1],2), Car(ruas[1],1));
        printf(" (%d)  %c   %c   %c| %c   %c | %c   %c    rua 4\n", ruas[1]->size, mov[4], mov[3], mov[2], mov[1], mov[0],
        Car(ruas[3],1), Car(ruas[3],2));
        printf("      --+---+--+-------+--+---+--\n");
        printf("               |   | %c |\n", Car(ruas[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(ruas[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", ruas[2]->size);
        
        usleep(199000);
        system("clear");
        
        i++;
    }
}


int main() {

    Queue* rua1 = (Queue*)malloc(sizeof(Queue));
    Queue* rua2 = (Queue*)malloc(sizeof(Queue)); 
    Queue* rua3 = (Queue*)malloc(sizeof(Queue));
    Queue* rua4 = (Queue*)malloc(sizeof(Queue));
    
    Queue* ruas[4] = {rua1, rua2, rua3, rua4};
    
    int currentChar = 0;
    int n = 36;
    int ordem[n];
    
    for(int i=0; i<n; i++){
        
        int radint = rand() % 4 + 1;
        ordem[i] = radint;
        
        switch(radint){
            
            case 1:
                enqueue(ruas[0], currentChar);
                currentChar++;
                break;
            case 2:
                enqueue(ruas[1], currentChar);
                currentChar++;
                break;
            case 3:
                enqueue(ruas[2], currentChar);
                currentChar++;
                break;
            case 4:
                enqueue(ruas[3], currentChar);
                currentChar++;
                break; 
        }
        
        if (currentChar == 26)
            currentChar = 0;
    }
    
    for(int i=0; i<n; i++){
        
        switch(ordem[i]){
            
            case 1:
                view1(ruas);
                break;
                
            case 2:
                view2(ruas);
                break;
            
            case 3:
                view3(ruas);
                break;
                
            case 4:
                view4(ruas);
                break;
        }
        
    }
    
    return 0;
}