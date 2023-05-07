#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include<stdlib.h>
#include "prob.h"
#include "main.h"

/*
	- Define every helper function in prob.h file
	- Use Semaphores for synchronization purposes
 */ 
/**
* Declare semaphores here so that they are available to all functions.
*/
// sem_t* example_semaphore;
sem_t* sem_1;
sem_t* sem_2; 
sem_t* In1;
sem_t* In2; 
sem_t* Out1;
sem_t* Going1;
sem_t* InCheck1; 
sem_t* InCheck2;
sem_t* InCheck3; 


pthread_t thread[20];

int from[20];
int to[20];
int id[20];

int MAX_NUM_FLOORS = 20;
int MAX_NUM_PEOPLE = 20;
/**
 * TODO: 
 * Do any initial setup work in this function. You might want TO 
 * initialize your semaphores here. Remember this is C and uses Malloc for memory allocation.
 *
 * numFloors: TOtal number of floors elevaTOr can go TO. numFloors will be smaller or equal TO MAX_NUM_FLOORS
 * maxNumPeople: The maximum capacity of the elevaTOr
 *
 */
int NoFloors;
int Maximum_People;
int NUM_passengers;
void initialize(int NoFloors, int Maximum_People) {
	// example_semaphore = (sem_t*) malloc(sizeof(sem_t));
	
	sem_1=(sem_t*) malloc(sizeof(sem_t));
	sem_2=(sem_t*) malloc(sizeof(sem_t));
	In1=(sem_t*) malloc(sizeof(In1));
	In2=(sem_t*) malloc(sizeof(In2));
	Out1=(sem_t*) malloc(sizeof(Out1));
	InCheck1=(sem_t*) malloc(sizeof(InCheck1));
	
	sem_init(&sem_1,0,0);
	sem_init(&sem_2,0,0);
	NoFloors=20;
	Maximum_People=20; 
	
	return;
}

/**
 * Every passenger will call this function when 
 * he/she wants TO take the elevaTOr. (Already
 * called in main.c)
 * 
 * This function should print info "ID FROM TO" without quotes,
 * where:
 * 	ID = ID of the passenger (would be 0 for the first passenger)
 * 	FROM = source floor (FROM where the passenger is taking the elevaTOr)
 * 	TO = destination floor (floor where the passenger is going)
 * 
 * info of a passenger x_1 getting off the elevaTOr before a passenger x_2
 * should be printed before.
 * 
 * Suppose a passenger 1 FROM floor 1 wants TO go TO floor 4 and
 * a passenger 2 FROM floor 2 wants TO go TO floor 3 then the final print statements
 * will be 
 * 2 2 3
 * 1 1 4
 *
 */
void* goingFromTo(void *arg) {
	int i;
	for(i=0;i<20;i++)
	{
		printf("%d",id[i]);
		printf("%d",from[i]);
		printf("%d",to[i]);
	}

}

/*If you see the main file, you will get TO 
know that this function is called after setting every
passenger.

So use this function for starting your elevaTOr. In 
this way, you will be sure that all passengers are already
waiting for the elevaTOr.
*/
void start(){
	pthread_t elevator;
	pthread_create(&elevator, NULL,goingFromTo,NULL);
	int i;
//	sem_wait(sem_IncomingCheck1);
//	sem_post(&sem_1);
	for(i=0;i<NUM_passengers;i++)
	{
		goingFromTo(i);
		
		NUM_passengers--;
		if(NUM_passengers==0)
		{
			break;
		}
		else
		{
		
			while(NUM_passengers!=0)
			{
				NUM_passengers--;
				sem_wait(&sem_1);
			}
		}
	}
}

void print()
{
	int i;
	for(i=0;i<20;i++)
	{
		printf("%d",id[i]);
		printf("%d",from[i]);
		printf("%d",to[i]);
	}
}

