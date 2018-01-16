#include <stdio.h>
#include <termios.h>
//For some variable names
#include <unistd.h>
#include <stdlib.h>

//Project 1
//Phillip Garza


int main(){
	//Need a termios Structure to hold old
	//attributes
	struct termios oldAttributes;
	char myPassword[100];
	char visibleInput[100];
	char inputChar;
	int i = 0;
	//Need to get the Attributes for read
	//or STDIN - Also passing a reference
	//to created struct
	tcgetattr(STDIN_FILENO,&oldAttributes);

	//Need to use bit masking to toggle 
	//Echo. XOR will toggle ECHO defined in 
	//termios.h
	oldAttributes.c_lflag  = oldAttributes.c_lflag ^ ECHO;

	//Set ECHO OFF
	//TCSANOW = the change happens now
	printf("Disabling echo\n");
	tcsetattr(STDIN_FILENO,TCSANOW,&oldAttributes);
	
	//Getting passphrase
	//Didn't know if you wanted complete sentences
	//using a string scanf only got the first word. 
	//this works
	printf("Enter Your Passphrase:");
	do{
		scanf("%c",&inputChar);
		myPassword[i]=inputChar;
		i++;
	}while(inputChar != '\n' && i < 100);
	//Output back to user
	printf("You entered %s",myPassword);

	//Need to use bit masking to toggle 
	//Echo. XOR will toggle ECHO defined in 
	//termios.
	printf("Default Behavior Restored\n");
	oldAttributes.c_lflag  = oldAttributes.c_lflag ^ ECHO;
	tcsetattr(STDIN_FILENO,TCSANOW,&oldAttributes);
	printf("Enter Your Passphrase:");
	i=0;
	do{
		scanf("%c",&inputChar);
		visibleInput[i]=inputChar;
		i++;
	}while(inputChar != '\n' && i < 100);
	//Output back to user
	printf("You entered %s",visibleInput);
	
	return EXIT_SUCCESS;
}
