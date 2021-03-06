#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define maxLetters 510

pid_t pid; //global process id


void printUserNPath() {    //a method that printing the current username and path
    char cwd[1024];
    char* username = getenv("USER");
    getcwd(cwd, sizeof(cwd));
    printf("\n%s@%s>",username, cwd);
}

void error() {
    printf("ERR\n");
    exit(1); //1 = ERROR TO STATUS
}

void freeArrayInput(char** input)
{
    int i=0;
    while(input!= NULL && input[i] != NULL)
    {
        free(input[i]);
                i++;
    }
    free(input);
//    int i = 0;
//    while (input[i])
//        free(input[i++]);
//    free(input);
}

int argCounter(char str[]) {
    int counter = 0;
    char * command = strtok(str , " \n"); // add more marks

    while (command != NULL) {
        counter++;
        command = strtok(NULL , " \n");
    }
    //printf("%d", wordCounter);
    counter++; // for the last place to be NULL
    return counter;
}

char** argOrginizer(char str[] ,char** arr, int counter) {

    char * command = strtok(str , " \n"); // add more marks
    // str = strtok(str , ". ,;?!"); // add more marks

    for (int i = 0; i < counter-1 ; i++) {
        arr[i] = (char*)malloc((strlen(command)+1)*sizeof(char));
        strcpy(arr[i],command);
        command = strtok(NULL , "\n ");
        //printf("%s", arr[i]);
    }
    arr[counter-1] = NULL;
    return arr;
}

int cd(char *pth){  // WORKING!!!
    char path[maxLetters];
    path[0] = '\0';
    strcpy(path,pth);

    char cwd[maxLetters];
    if(pth[0] != '/') {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }
        else {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,path);
        chdir(cwd);
//        chdir(pth);
    }

    return 0;
}


int main() {

    int numOfCommands = 0;
    int lenOfCommands = 0;
    char str[510] = "\0";			// creating a new string
    while(strcmp(str, "done")) {

        printUserNPath();            // print the path and username
        fgets(str, maxLetters, stdin); // getting a string from the user

        char temp[maxLetters];        // creating a temp array

        strcpy(temp, str);        // copy the current string to the temp string

        int wordCounter = argCounter(temp);

        char **arr = (char **) malloc((wordCounter) * sizeof(char *));

        if (arr == NULL)
            error();
        argOrginizer(str, arr, wordCounter);


        if(strcmp(arr[0], "cd") == 0) {        // NOT WORKING !!!
                cd(arr[1]);
                continue;
        }
        pid = fork(); // creating a new process

        if (pid < 0) {  // error creating the son process
            error();
        }

        if (pid == 0) {
            if(arr[0] != NULL)
                execvp(arr[0], arr);   //WORKSSSSSSSS
            fprintf(stderr, "%s: command not found\n", arr[0]);
            exit(EXIT_FAILURE);
        } else {
            int status;
            wait(&status);
            if(status == EXIT_SUCCESS)
            {
                numOfCommands++;
                if(arr[0] != NULL)
                    lenOfCommands += strlen(arr[0]);
            }
            freeArrayInput(arr);
            arr = NULL;
        }

    }
    printf("Num of cmd: %d\nCmd length: %d\nBye !", numOfCommands, lenOfCommands);  // ADD A CONDITION WITH THE FATHER'S PID TO PREVENT DUPLICATE PRINTING
    exit(0); // ADD COUNTERS FOR COMMANDS AND ARGUMENTS




}

/*
 *
 *
 * char *remove_cr(char *string)
{
int i=0;
while(string[i])
{
if (string[i] == '\n')
string[i] = '\0';
i++;
}
return string;
}
*
*
int main() {
	pid_t x;

	char* firstCommand[] = {"ls", "-l", NULL};
	char* secoundCommand[] = {"pwd", NULL};
	x = fork();

	if(x == 0) {
		execvp(firstCommand[0], firstCommand);
		return 0;
	}
	else
	wait(NULL);
	execvp(secoundCommand[0], secoundCommand);
	return 0;
}
	*/


/*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define maxLetters 510

int main()
{
char str[maxLetters];
printf("please type a line \n");
fgets(str , maxLetters , stdin);
                                         //printf("%c\n" , str[1]);
char temp[maxLetters];
strcpy(temp,str);
                                            //printf("%c\n" , temp[1]);
int count = 0;
char * ptr = strtok(temp , " \n");
while (ptr!=NULL)
 {
	count++;
	ptr = strtok(NULL , " \n");
 }
                                            //printf("%d\n" , count);
count++;   				// for the last place to be NULL
char **arr = (char **) malloc(count*sizeof(char*));
if(arr == NULL)
	exit(1);
ptr = strtok(str , " \n");
int i;
for (i = 0; i<count-1 ; i++)
 {
	arr[i] = (char*)malloc((strlen(ptr)+1)*sizeof(char));
	strcpy(arr[i],ptr);
	ptr = strtok(NULL , " \n");
 }
arr[count-1] = NULL;


return 0;
}

*/

/* #include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	printf("I am the parent process, creating a new process\n");
	pid_t x;
	x = fork();

	if(x == 0) {
		for(int i = 0; i < 6; i++) {
			printf("I am the child process: Counting %i\n", i);
		}
		return 0;
	}
	else
		wait(NULL);
                printf("The child process with ID <%d> is terminated\n", x);

	return 0;

}

*/



/* #include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

int main() {
	pid_t x;

	char* firstCommand[] = {"ls", "-l", NULL};
	char* secoundCommand[] = {"pwd", NULL};
	x = fork();

	if(x == 0) {
		execvp(firstCommand[0], firstCommand);
		return 0;
	}
	else
	wait(NULL);
	execvp(secoundCommand[0], secoundCommand);
	return 0;
}


*/
