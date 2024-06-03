#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>

typedef pthread_mutex_t mutex_t;
typedef pthread_t thread;

mutex_t mutex;

typedef struct node {
    
    char id;
    struct node *next;
    
} Node;

typedef struct queue {
    
    Node* front;
    Node* rear;
    
    int size;
    
} Queue;

typedef struct args {
    
    Queue* rua[4];
    int currentChar;

} Args;

void enqueue(struct args *R, int n) {
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    if(R->currentChar == 26)
        R->currentChar = 0;
    
    new_node->id = 65 + R->currentChar;
    R->currentChar++;
    
    new_node->next = NULL;  
    
    if (R->rua[n-1]->front == NULL && R->rua[n-1]->rear == NULL) {  
        R->rua[n-1]->front = R->rua[n-1]->rear = new_node;
        R->rua[n-1]->size++;
        return;  
    }  
    
    R->rua[n-1]->rear->next = new_node;  
    R->rua[n-1]->rear = new_node;  
    
    R->rua[n-1]->size++;
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

void *view1(void *ptr){
    
    pthread_mutex_lock(&mutex);
    
    Args *R = (Args*)ptr;
    
    char c = dequeue(R->rua[0]);
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", R->rua[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(R->rua[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(R->rua[0], 1));
        printf("      --+---+--+\033[32m-------\033[39m+--+---+--\n");
        printf("rua 2  _ %c _ %c \033[31m|\033[39m %c     \033[31m|\033[39m   _   _   (%d) \n", 
        Car(R->rua[1],2), Car(R->rua[1],1),mov[0]), R->rua[3]->size;
        printf(" (%d)           \033[31m|\033[39m %c     \033[31m|\033[39m %c   %c    rua 4\n", 
        R->rua[1]->size, mov[1], Car(R->rua[3],1), Car(R->rua[3],2));
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("               | %c | %c |\n", mov[2], Car(R->rua[2],1));
        printf("               | %c     |\n", mov[3]);
        printf("               | %c | %c |\n", mov[4], Car(R->rua[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", R->rua[2]->size);
        
        usleep(299000);
        system("clear");
        
        i++;
    }
    
    pthread_mutex_unlock(&mutex);
}

void *view2(void *ptr){
    
    pthread_mutex_lock(&mutex);
    
    Args *R = (Args*)ptr;
    
    char c = dequeue(R->rua[1]); //RUA 2
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", R->rua[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(R->rua[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(R->rua[0], 1));
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("rua 2  _ %c _ %c \033[32m|\033[39m %c   %c \033[31m|\033[39m %c _ %c _ %c (%d) \n", 
        Car(R->rua[1],2), Car(R->rua[1],1), mov[0], mov[1], mov[2], mov[3], mov[4], R->rua[3]->size);
        printf(" (%d)           \033[32m|\033[39m       \033[31m|\033[39m %c   %c    rua 4\n", R->rua[1]->size, Car(R->rua[3],1), Car(R->rua[3],2));
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("               |   | %c |\n", Car(R->rua[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(R->rua[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", R->rua[2]->size);
        
        usleep(299000);
        system("clear");
        
        i++;
    }
    
    pthread_mutex_unlock(&mutex);
}

void *view3(void *ptr){
    
    pthread_mutex_lock(&mutex);
    
    Args *R = (Args*)ptr;
    
    char c = dequeue(R->rua[2]); //RUA3
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", R->rua[0]->size);
        printf("               +       +\n");
        printf("               | %c | %c |\n", Car(R->rua[0],2), mov[4]);
        printf("               |     %c |\n", mov[3]);
        printf("               | %c | %c |\n", Car(R->rua[0], 1), mov[2]);
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("rua 2  _ %c _ %c \033[31m|\033[39m     %c \033[31m|\033[39m   _   _   (%d) \n", 
        Car(R->rua[1],2), Car(R->rua[1],1), mov[1], R->rua[3]->size);
        printf(" (%d)           \033[31m|\033[39m     %c \033[31m|\033[39m %c   %c    rua 4\n", 
        R->rua[1]->size, mov[0], Car(R->rua[3],1), Car(R->rua[3],2));
        printf("      --+---+--+\033[32m-------\033[39m+--+---+--\n");
        printf("               |   | %c |\n",Car(R->rua[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(R->rua[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", R->rua[2]->size);
        
        usleep(299000);
        system("clear");
        
        i++;
    }
    
    pthread_mutex_unlock(&mutex);
}

void *view4(void *ptr){
    
    pthread_mutex_lock(&mutex);
    
    Args *R = (Args*)ptr;
    
    char c = dequeue(R->rua[3]); //RUA 4
    char tst = 'X';
    
    int i = 0, j=0;
    while(i < 5){
        
        int mov[5] = {32, 32, 32, 32, 32};
        
        mov[j % 5] = c;
        j = j + 1;
    
        printf("\n\n");
        printf("                rua 1 (%d)\n", R->rua[0]->size);
        printf("               +       +\n");
        printf("               | %c |   |\n", Car(R->rua[0],2));
        printf("               |       |\n");
        printf("               | %c |   |\n", Car(R->rua[0], 1));
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("rua 2  _ %c _ %c \033[31m|\033[39m       \033[32m|\033[39m   _   _   (%d) \n", Car(R->rua[1],2), Car(R->rua[1],1), R->rua[3]->size);
        printf(" (%d)  %c   %c   %c\033[31m|\033[39m %c   %c \033[32m|\033[39m %c   %c    rua 4\n", 
        R->rua[1]->size, mov[4], mov[3], mov[2], mov[1], mov[0], Car(R->rua[3],1), Car(R->rua[3],2));
        printf("      --+---+--+\033[31m-------\033[39m+--+---+--\n");
        printf("               |   | %c |\n", Car(R->rua[2],1));
        printf("               |       |\n");
        printf("               |   | %c |\n", Car(R->rua[2],2));
        printf("               +       +\n");
        printf("                rua 3 (%d)\n\n\n", R->rua[2]->size);
        
        usleep(299000);
        system("clear");
        
        i++;
    }
    
    pthread_mutex_unlock(&mutex);
}


int main( ) {
    
    thread t1,t2,t3, t4;

    struct args *R = (struct args*)malloc(sizeof(struct args));

    R->rua[0] = (Queue*)malloc(sizeof(Queue));
    R->rua[1] = (Queue*)malloc(sizeof(Queue)); 
    R->rua[2] = (Queue*)malloc(sizeof(Queue));
    R->rua[3] = (Queue*)malloc(sizeof(Queue));
    
    int currentChar = 0;
    int n = 36;
    int ordem[n];
    
    pthread_t threads[n];
    
    for(int i=0; i<n; i++){
        
        int radint = rand() % 4 + 1;
        ordem[i] = radint;
        
        switch(radint){
            
            case 1:
                enqueue(R,1);
                break;
            case 2:
                enqueue(R,2);
                break;
            case 3:
                enqueue(R,3);
                break;
            case 4:
                enqueue(R,4);
                break; 
        }
        
        if (currentChar == 26)
            currentChar = 0;
    }
    
    
    for(int i=0; i<n; i++){
        
        switch(ordem[i]){
            
            case 1:
                pthread_create(&threads[i], NULL, view1, (void *)R);
                break;
                
            case 2:
                pthread_create(&threads[i], NULL, view2, (void *)R);
                break;
            
            case 3:
                pthread_create(&threads[i], NULL, view3, (void *)R);
                break;
                
            case 4:
                pthread_create(&threads[i], NULL, view4, (void *)R);
                break;
        }
    }
    
    for(int i=0; i<n; i++){
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}