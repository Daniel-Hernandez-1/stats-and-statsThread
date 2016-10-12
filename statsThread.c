// Daniel Hernandez
// Rudy Leiva
// 3/4/16
// CSC 341
// Project 2 (Part 2)

/*
Project 2 (Part 2): This program is passed command line arguments at the time of execution. The program goes through the all the arguments to get a count of how many valid arguments were provided. Anything that isnt a valid argument is excluded from this count. If no arguments are passed in the command line or all the arguments passed were not valid, some information is displayed on how to properly execute this program and the program will terminate at that point. Once there is a count, an array of integers is created to hold the number of elements given by the value of count. Then the program goes through each command line argument and for each argument that is a valid number, it will be converted from character to integer and added to the integer array. Next, the program creates 3 threads using the pthread_create() function. Each thread is provided a seperate pthread_t variable, NULL for attributes, a pointer to a different function, and pointer to the integer array (the pointer is a void * and is then cast back into an int). Each thread then performs its calculation and each result is ouput by the appropriate thread while the main thread waits for the other to complete. When all threads are completed, they are joined back to the main thread and the program will end successfully.
*/

// Required include statements
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Required global data for processes
int minValue = 0;
int maxValue = 0;
int avgValue = 0;
int globalCount;	// value of count will go here so threads can use in calculation of values
int * array;		// pointer to an array of integers

void * calcAverage(void * ptr);		// prototype function for calculating average
void * calcMinimum(void * ptr);		// prototype function for calculating minimum
void * calcMaximum(void * ptr);		// prototype function for calculating maximum

int main(int argc, char * argv[]) // begin main()
{
	int count = 0;		// stores value of how many valid arguments were provided
	int pos = 0;		// used to keep track of index position in the integer array
	int test;		// used to check for valid argument, data is only written when valid
	int i;			// counter variable
	int j;			// counter variable
	int k;			// counter variable
	
	// These variables are used for the creation of the threads
	pthread_t thread1, thread2, thread3;
	int thrd1, thrd2, thrd3;
	
	// For loop goes through all command line arguments and tests if they are integers
	for(i = 0; i < argc; i++)
	{
		if(sscanf(argv[i], "%d", &test) == 1)
		{
			count++; // increment value if argument is valid (written to test variable)
		}
	}
	
	// Either no arguments were passed from the command line or all were invalid.
	if(count == 0)
	{
		printf("Usage: ./statsThread [list of numbers delimited by the space character]\n");
		printf("Info: Anything entered that is not a number is ignored.\n");
		exit(0);	// terminate program
	}
	
	globalCount = count;		// set globalCount to count so that it can be used by threads
	int numarray[count];		// create integer array with appropriate size
	
	// Convert all valid arguments to integers and add them to the integer array
	for(j = 0; j < argc; j++)
	{
		if(sscanf(argv[j], "%d", &test) == 1)
		{
			numarray[pos++] = atoi(argv[j]);	// conversion from char to int
		}
	}

	array = numarray;	// set integer array pointer to point to the integer array
	
	thrd1 = pthread_create(&thread1, NULL, calcAverage, (void *) array); // create 1st thread
	
	if(thrd1 != 0)
	{
		printf("Error: Thread not created.\n"); // check if thread wasnt created
	}
	
	thrd2 = pthread_create(&thread2, NULL, calcMinimum, (void *) array); // create 2nd thread
	
	if(thrd2 != 0)
	{
		printf("Error: Thread not created.\n"); // check if thread wasnt created
	}
	
	thrd3 = pthread_create(&thread3, NULL, calcMaximum, (void *) array); // create 3rd thread
	
	if(thrd3 != 0)
	{
		printf("Error: Thread not created.\n"); // check if thread wasnt created
	}
	
	// Wait for all threads to finish before proceeding
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	exit(EXIT_SUCCESS); // End program
} // end main()

// function to calculate the average. A pointer to the integer array is passed.
void * calcAverage(void * ptr)	// begin calcAverage()
{
	int k;
	int * numarray;		// pointer to an array of integers
	
	// Dereference void pointer and cast it to type int * 
	// numarray now points to the integer array
	numarray = (int *) ptr;
	
	for(k = 0; k < globalCount; k++)
	{
		avgValue = avgValue + numarray[k];	// calculate average
	}
	
	avgValue = avgValue / globalCount;		// calculate average
	
	// Output average and also the thread id
	printf("The average value is: %d \t\t(Thread ID: %lu)\n", avgValue, pthread_self());
} // end calcAverage()

// function to calculate the minimum value. A pointer to the integer array is passed.
void * calcMinimum(void * ptr) // begin calcMinimum()
{
	int k;
	int * numarray;		// pointer to an array of integers
	
	// Dereference void pointer and cast it to type int *
	// numarray now points to the integer array
	numarray = (int *) ptr;
	
	for(k = 0; k < globalCount; k++)
	{
		if(minValue == 0 || (minValue > numarray[k]))
		{
			minValue = numarray[k];		// calculate minimum
		}
	}
	
	// Output minimum value and also the thread id
	printf("The minimum value is: %d \t\t(Thread ID: %lu)\n", minValue, pthread_self());
} // end calcMinimum()

// function to calculate the maximum value. A pointer to the integer array is passed.
void * calcMaximum(void * ptr) // begin calcMaximum()
{
	int k;
	int * numarray;		// pointer to an array of integers
	
	// Dereference void pointer and cast it to type int *
	// numarray now points to the integer aray
	numarray = (int *) ptr;
	
	for(k = 0; k < globalCount; k++)
	{
		if(maxValue == 0 || (maxValue < numarray[k]))
		{
			maxValue = numarray[k];		// calculate maximum value
		}
	}
	
	// Output maximum value and also the thread id
	printf("The maximum value is: %d \t\t(Thread ID: %lu)\n", maxValue, pthread_self());
} // end calcMaximum()
