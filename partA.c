// C Program to design a shell in Linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAXCOM 1000 
#define MAXLIST 100 
#define clear() printf("\033[H\033[J")


int Input (char* str)
{	
	char str1[120];
	printf("\n@12040300_ArjitBhamu~~~~~~~~~~~~~>>>>>>");
	gets(str1);
	if (strlen(str1) != 0) {
		strcpy(str, str1);
		return 0;
	} else {
		return 1;
	}
}
void currtDirec()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDirectory: %s", cwd);
}
void Execution_(char** arr)
{
	pid_t p = fork();
	if (p == -1) {
		printf("\nchild is not forking");
		return;
	} else if (p == 0) {
		if (execvp(arr[0], arr) < 0) {
			printf("\nCommand not found");
		}
		exit(0);
	} else {
		
		wait(NULL);
		return;
	}
}
void Help()
{
	puts("\n~~~~~THIS IS ARJIT'S SHELL~~~~" "\nList of Commands supported:" "\n>cd" "\n>ls" "\n>exit" "\n>all commands in UNIX shell" "\n>space tackling");
	return;
}
int mycommands(char** arr)
{
	int n= 4, i, e= 0;
	char* c_list[n];
	char* name;
	c_list[0] = "exit";
	c_list[1] = "cd";
	c_list[2] = "help";
	c_list[3] = "hello";
	for (i = 0; i < n; i++) {
		if (strcmp(arr[0], c_list[i]) == 0) {
			e = i + 1;
			break;
		}
	}
	switch (e) {
	case 1:
		printf("\nGoodbye take care \n");
		exit(0);
	case 2:
		chdir(arr[1]);
		return 1;
	case 3:
		Help();
		return 1;
	case 4:
		name = getenv("USER");
		printf("\nHello %s.\n"
			"\nUse help command for help..\n",
			name);
		return 1;
	default:
		break;
	}
	return 0;
}
void Space_tackle(char* str, char** arr)
{
	int i;
	for (i = 0; i < MAXLIST; i++) {
		arr[i] = strsep(&str, " ");
		if (arr[i] == NULL)
			break;
		if (strlen(arr[i]) == 0)
			i--;
	}
}
int checking_string(char* str, char** arr)
{
		Space_tackle(str, arr);
	if (mycommands(arr))
		return 0;
	else
		return 1 ;
}
int main()
{
	char input[MAXCOM], *arr[MAXLIST];
	int e = 0;
	
	while (1) {
		currtDirec();
		if (Input(input))
			continue;
		e = checking_string(input,
		arr);
		if (e == 1)
			Execution_(arr);		
	}
	return 0;
}

