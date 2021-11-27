/*
 * Matthew Lake 
 * 10/20/2021
 * CS 3080 Lab Assignment 3 
 * This program is excercing our ability with using producers and consumers and the Pthread process.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Number of threads
#define NUM_THREADS 2		

//Size of the buffer
#define BSIZE 10	

//Number of items to produce and consume
#define NUM_ITEMS 10		

//Shared buffer
int buf[BSIZE];
int NextIn=0, NextOut=0;

//Producer and Consumer funtions
void * producer(void *);	
void * consumer(void *);	

//Array of the threads to use with size of 2
pthread_t tid[NUM_THREADS];      

//Variables to be calculated and printed
int min = 1000 + 1;
int max = 0;
int sum = 0;
int currentNumOut;
int currentNumIn;

int main( ) 
{
	int i = NUM_THREADS;

	printf("\n **** Main Program creating threads ++++ \n");

	//Create threads
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid[0], &attr, producer, NULL);
	pthread_create(&tid[1], &attr, consumer, NULL);

	//Join threads to terminate them
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("\n *** main() reporting: all %d threads terminated \n\n ", i);

	printf("\n The minimum integer was: %d\n" , min);
	printf("\n The maximum integer was: %d\n" , max);
	int avg = sum / NUM_ITEMS;
	printf("\n The average is: %d\n", avg);

	return 0; 

}  /* end main */

  

void * producer(void * parm)
{
	printf("\n ++++ Producer started ++++ \n");

	//Get pthread ID and use it for the seed
	pthread_t myID = pthread_self();
	srand(myID);

	for (int i=0; i<NUM_ITEMS; i++) {	

		//Produce item 
		currentNumIn = rand() % 1000;
		//Place item in the buffer
		buf[NextIn] = currentNumIn;
		NextIn++;
		
		printf(" Produced item: %d\n", currentNumIn);
	}

	printf("\n +++ Producer exiting +++ \n");
	pthread_exit(0);
}    

void * consumer(void * parm)
{
	printf("\n --- Consumer started --- \n");
	for (int i=0; i<NUM_ITEMS; i++){
        // fetch an item from the buffer
		currentNumOut = buf[NextOut];
		NextOut++;
			
		//Busy for loop
		int wait;
		int waiting;
		for (int i = 0; i < 100000; i++) {
			wait = 60 * 90;
			waiting = wait;
		}
		printf(" Consuming item: %d\n", currentNumOut);

		//Update varibles
		if (currentNumOut > max) {
			max = currentNumOut;
		}

		if (currentNumOut < min) {
			min = currentNumOut;
		}
		sum = sum + currentNumOut;
	}

	printf("\n --- Consumer exiting ----\n");
	pthread_exit(0);
}


