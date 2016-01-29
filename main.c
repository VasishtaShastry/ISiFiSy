#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>
#include <dirent.h>


void printFiller ();
int returnCmdNum (char []);
int returnErrorFlag (int, int);
void printErrorMsg (int);
void oops (char*, char*);



void main(){

	char inp[100], para1[20], para2[20], para3[20], cmd[10];
	int numOfParas, cmdNum, errorFlag, processErrorFlag;
	
	const char* inr_sym = "\u20B9 ";
	printf("\nWelcome");

	printf("\nFor more info use command -info");
	printFiller();

	while(1){

		printf ("%s", inr_sym);
		gets(inp);
		
		if (inp[0] == '\0')	continue;
		
		numOfParas = sscanf (inp, "%s %s %s %s", cmd, para1, para2, para3 );
		
		cmdNum = returnCmdNum (cmd);

		if (cmdNum == 4){

			printFiller ();
			exit (0);
		}

		errorFlag = returnErrorFlag (cmdNum, numOfParas);
		
		if (errorFlag != 0){
			printErrorMsg (cmdNum);
			continue;
		}

		if (cmdNum == -1)	continue;
		switch	(cmdNum){

			case 1: myCopy (para1, para2);
					break;

			case 2:	myWrite	(para1, para2);
					break;

			case 3: myInfo (para1);
					break;

			case 5: myTouch (para1);
					break;

			case 6: myCAT (para1);
					break;

			case 7: unlink (para1);
					break;

			case 8: myLs ();
					break;

			default: printf ("Sorry !! Something went wrong\nTry again");

		}
		
		printFiller ();
		
	}

}

void printFiller(){
	printf ("\n");
	printf ("=============================");
	printf ("\n");
}

int returnCmdNum (char command[10]){


	if( !(strcmp(command, "copy")) || !(strcmp(command, "Copy")) || !(strcmp(command, "COPY")) || !(strcmp(command, "cpy")))	return 1;

	if( !(strcmp(command, "write")) || !(strcmp(command, "Write")) || !(strcmp(command, "WRITE")))	return 2;

	if( !(strcmp(command, "info")) || !(strcmp(command, "Info")) || !(strcmp(command, "INFO")))	return 3;

	if( !(strcmp(command, "quit")) || !(strcmp(command, "Quit")) || !(strcmp(command, "q")))	return 4;

	if( !(strcmp(command, "touch")) || !(strcmp(command, "Touch")) || !(strcmp(command, "tch")))	return 5;

	if( !(strcmp(command, "cat")) || !(strcmp(command, "CAT")))	return 6;

	if( !(strcmp(command, "delete")) || !(strcmp(command, "del")))	return 7;

	if( !(strcmp(command, "list")) || !(strcmp(command, "ls")))	return 8;

	return -1;

}

int returnErrorFlag (int cmdNum, int numOfParas){

	if ((cmdNum == 3 || cmdNum >= 5) && numOfParas == 2)	return 0;

	if ((cmdNum ==1 || cmdNum == 2) && numOfParas == 3)	return 0;

	if (cmdNum == 8 && numOfParas == 1 )	return 0;

	return 1;	
}

void printErrorMsg (int cmdNum){

	printFiller ();
	printf ("ERROR");
	switch (cmdNum){

		case -1: printf ("\nCommand couldn't be recognised\ntry again\n");
				break;

		case 1:	printf ("\ninvalid usage of copy\n");
				break;

		case 2:	printf ("\ninvalid usage of write\n");
				break;
		
		case 3:	printf ("\ninvalid usage of info\n");
				break;

		default: printf ("\ninvalid usage\n");
	}
	printf ("For more information use command \'info\'");
	printFiller ();

}



void oops(char *s1, char *s2)
 {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
 }