#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int seconds;
int green_light;
int init(void);

void play(void);
void print_doll(void);
void evil_doll(void);
void quizzes(void); 

int main(void) 
 {	
	 if(!init()) 
		 perror("init()");
	 
	 return 0;
 }

int 
init(void) {
	 seconds = 0;
	 green_light = 1;
	 pthread_t task1;
	 pthread_t task2;
 	 return (!pthread_create(&task1, NULL, (void *)&play, NULL) && 
 	 	 !pthread_create(&task2, NULL, (void *)&evil_doll, NULL) && 
	         !pthread_join(task1,NULL) && 
	         !pthread_join(task2,NULL));
}

void 
play(void) 
{	
	puts("MINI SQUID GAME\n");
	while(green_light)  
	      quizzes();
	
}

void 
evil_doll(void) 
{	
	while(green_light && seconds++ < 5) 
	      sleep(1);

	puts("\r\nELIMINATED");
	print_doll();
	exit(-1);
}

void 
quizzes(void)
{	
	time_t t;
	srand((unsigned) time(&t));
	int level = 100;
	int answer = 0;
        int a = rand() % level;
        int b = rand() % level / 5;
	puts("-----------------GREEN-LIGHT-----------------YOU HAVE FIVE SECONDS!");
	printf("%d", a);
	/* We need a parser here... */
	switch(rand() % 3) {
	       case 0: printf("+%d",b); a += b; break;
	       case 1: printf("-%d",b); a -= b; break;
	       case 2: printf("*%d",b); a *= b; break;
	       default: break;
	    }
	seconds = 0;
	putchar('?');
	fscanf(stdin,"%8d",&answer); 
	fflush(stdout);
	green_light = (answer == a);
}

void 
print_doll(void) 
{	
	char *file = "Squid-Game.ascii.txt";
	FILE *doll = fopen(file,"r");
	if(!doll) {
		perror(file);
	     	doll = NULL;
		return;
	}
	char c = '\0';
	while((c = fgetc(doll)) != EOF) {
		putchar(c);
		usleep(500);
	}
	fclose(doll);
	doll = NULL;
}
