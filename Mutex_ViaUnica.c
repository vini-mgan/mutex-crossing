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

struct args{
    int logR1;
    int logR2;
};


void *r2(void *logs){
    
    pthread_mutex_lock(&mutex);
    int i = 1, j = 0;
    
    ((struct args*)logs)->logR2--;
    
    while(j <= 5){
        int rua[5] = {32, 32, 32, 32, 32};

        rua[i % 5] = 67;
        i = i + 1;
        
        printf("%d on hold in R1\n", ((struct args*)logs)->logR1);
        printf("%d on hold in R2\n", ((struct args*)logs)->logR2);
        
        printf("\n\n");
        printf("               rua 1\n");
        printf("             +      +\n");
        printf("             |      |\n");
        printf("             +------+\n");
        printf("             |  C   |\n");
        printf("      +--+---+\033[31m------\033[39m+---+--+\n");
        printf("rua 4 %c  | %c\033[32m |\033[39m  %c   | %c | %c  rua 2\n", rua[0],rua[1],rua[2],rua[3],rua[4]);
        printf("      +--+---+------+---+--+\n");
        printf("             |      |\n");
        printf("             +------+\n");
        printf("             |      |\n");
        printf("             +      +\n");
        printf("               rua 3\n\n\n");
        usleep(199000);
        system("clear");
        j++;
    }
    
    pthread_mutex_unlock(&mutex);
}

void *r1(void* logs){
    
    pthread_mutex_lock(&mutex);
    int i = 1, j = 0;
    
    ((struct args*)logs)->logR1--;
    
    while(j <= 5){
        
            int rua[5] = {32, 32, 32, 32, 32};
            rua[i % 5] = 67;
            i = i + 1;

        printf("%d on hold in R1\n", ((struct args*)logs)->logR1);
        printf("%d on hold in R2\n", ((struct args*)logs)->logR2);

        printf("\n\n");
        printf("               rua 1\n");
        printf("             +      +\n");
        printf("             |  %c   |\n", rua[0]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[1]);
        printf("      +--+---+\033[32m------\033[39m+---+--+\n");
        printf("rua 4    | C \033[31m|\033[39m  %c   |   |    rua 2\n", rua[2]);
        printf("      +--+---+------+---+--+\n");
        printf("             |  %c   |\n", rua[3]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[4]);
        printf("             +      +\n");
        printf("               rua 3\n\n\n");
        usleep(199000);
        system("clear");
        j++;
    }
    
    pthread_mutex_unlock(&mutex);
}

int main(){
    
    struct args *logs = (struct args *)malloc(sizeof(struct args));

    logs->logR1 = 0;
    logs->logR2 = 0;

    thread t1,t2;

    pthread_mutex_init(&mutex,NULL); 
    
    while(1){
        
        logs->logR1 += rand() % 5+1;
        logs->logR2 += rand() % 5+1;

        system("clear");
        
        for(int i=logs->logR1; i>1; i--){
            pthread_create(&t1,NULL,r1,(void *)logs);
        }
        
        for(int i=logs->logR2; i>1; i--){
            pthread_create(&t2,NULL,r2,(void *)logs);
        }
        
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}