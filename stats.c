// Daniel Hernandez
// Rudy Leiva
// 3/4/16
// CSC 341
// Project 2 (Part 1)

/*
Project 2 (Part 1): This program is passed command line arguments at the time of execution. The program goes through the all the arguments to get a count of how many valid arguments were provided. Anything that isnt a valid argument is excluded from this count. If no arguments are passed in the command line or all the arguments passed were not valid, some information is displayed on how to properly execute this program and the program will terminate at that point. Once there is a count, an array of integers is created to hold the number of elements given by the value of count. Then the program goes through each command line argument and for each argument that is a valid number, it will be converted from character to integer and added to the integer array. Next, the fork() function is used to create new processes that will performe the required statistical calculations for average, minimum, and maximum value.
*/

// Required include statements
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Required global data for processes
int minValue = 0;
int maxValue = 0;
int avgValue = 0;

int main(int argc, char * argv[]) // begin main()
{
	int count = 0;		// stores the value of how many valid arguments were provided
	int pos = 0;		// used to keep track of index position in the integer array
	int test;		// used to check for valid argument, data is only written when valid
	int i;			// counter variable
	int j;			// counter variable
	int k;			// counter variable
	
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
		printf("Usage: ./stats [list of numbers delimited by the space character]\n");
		printf("Info: Anything entered that is not a number is ignored.\n");
		exit(0); // terminate program.
	}
	
	int numarray[count];		// create integer array with appropriate size
	
	// convert all valid arguments to integers and add them to the integer array.
	for(j = 0; j < argc; j++)
	{
		if(sscanf(argv[j], "%d", &test) == 1)
		{
			numarray[pos++] = atoi(argv[j]); 	// conversion from char to int.
		}
	}
	
	pid_t pid1 = fork(); // create first child process
	
	if(pid1 < 0)
	{
		printf("Error: fork failed.\n");	// check if child process wasn't created
	}
	else if(pid1 == 0)		// have child process perform average value calculation
	{
		for(k = 0; k < count; k++)
		{
			avgValue = avgValue + numarray[k];
		}
		
		avgValue = avgValue / count;
		
		// Print out values, including PID and parent PID
		printf("The average value is: %d \t\t(PID: %d, PPID: %d)\n", avgValue, getpid(), getppid());
		
		exit(0); // end child process
	}
	else
	{
		wait(NULL);	// Parent waits for child to complete
	}
	
	pid_t pid2 = fork();		// create second child process
	
	if(pid2 < 0)
	{
		printf("Error: fork failed.\n");	// check if child process wasn't created
	}
	else if(pid2 == 0)
	{
		for(k = 0; k < count; k++)
		{
			if(minValue == 0 || (minValue > numarray[k]))
			{
				minValue = numarray[k];		// have child value perform calculation for minimum
			}
		}
		
		// Print out values, including PID and parent PID
		printf("The minimum value is: %d \t\t(PID: %d, PPID: %d)\n", minValue, getpid(), getppid());
	
		exit(0); // end child process
	}
	else
	{
		wait(NULL); // Parent waits for child to complete.
	}
	
	pid_t pid3 = fork();		// create third child process
	
	if(pid3 < 0)
	{
		printf("Error: fork failed.\n");	// check if child process wasn't created
	}
	else if(pid3 == 0)
	{
		for(k = 0; k < count; k++)
		{
			if(maxValue == 0 || (maxValue < numarray[k]))
			{
				maxValue = numarray[k];		// have child process perform calculation for maximum
			}
		}
		
		// Print out values, including PID and parent PID
		printf("The maximum value is: %d \t\t(PID: %d, PPID: %d)\n", maxValue, getpid(), getppid());
		
		exit(0); // end child process
	}
	else
	{
		wait(NULL); // Parent waits for child to complete
	}
} // end main()
