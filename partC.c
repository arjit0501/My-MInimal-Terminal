#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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



void excecution(char** GG){
pid_t pid = fork();

if (pid == 0) {
if (execvp(GG[0], GG) < 0) {
}
exit(0);
} else {
wait(NULL);
return;
}
}






void excecution_2(char** GG){
pid_t pid = fork();

if (pid == 0) {
if (execvp(GG[0], GG) < 0) {
}
exit(0);
} else {
wait(NULL);
return;
}
}





void epipe(char** aa, char** aa2)
{
	int pipefd[2];
	pid_t b1, b2;

	if (pipe(pipefd) < 0) {
		printf("\nPipe not initialized");
		return;
	}
	b1 = fork();
	if (b1 < 0) {
		printf("\nChild process not fork");
		return;
	}

	if (b1 == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(aa[0], aa) < 0) {
			printf("\n Command not found ");
			exit(0);
		}
	} else {
		b2 = fork();

		if (b2 < 0) {
			printf("\nchild process not fork");
			return;
		}		
		if (b2 == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(aa2[0], aa2) < 0) {
				printf("\ncommand 2 not found");
				exit(0);
			}
		} else {
			wait(NULL);
			wait(NULL);
		}
	}
}





int separation_and(char* str, char** andarray)
{
int i;
for(i=0;i<2;i++) {
andarray[i] = strsep(&str, "&&");
if(andarray[i]== NULL)
break;
}
if(andarray[1] == NULL)
return 0;
else{
return 1;
}

}


int separation_re(char* str, char** andarray)
{
int i;
	for (i = 0; i < 2; i++) {
		andarray[i] = strsep(&str, ">");
		if (andarray[i] == NULL)
			break;
	}

	if (andarray[1] == NULL)
		return 0; 
	else {
		return 1;
	}

}



int p_pipe(char* str, char** strr)
{
	int i;
	for (i = 0; i < 2; i++) {
		strr[i] = strsep(&str, "|");
		if (strr[i] == NULL)
			break;
	}

	if (strr[1] == NULL)
		return 0; 
	else {
		return 1;
	}
}







void execredir(char** parsed, char**parsedredir)
{
pid_t pp;
pp = fork();
if (pp < 0)
    printf("\nNot fork");
else if (pp == 0)
{
    
        int fd1 = open(*parsedredir , O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR) ;
        dup2(fd1, STDOUT_FILENO);
       
        close(fd1);
        execvp(parsed[0], parsed);
   
   
}

else
{
   
    wait(NULL);
}
}









void Space_tackle(char* str, char** arr)
{
	int i;
	for (i = 0; i < 200; i++) {
		arr[i] = strsep(&str, " ");
		if (arr[i] == NULL)
			break;
		if (strlen(arr[i]) == 0)
			i--;
	}

}





int Main_checking(char* str, char** arr, char** pp)
{

char* strp[2];
char* andp[2];
char* rep[2];
int an=0;
int re=0;
an= separation_and (str, andp);
re= separation_re (str, rep);
int pip = 0;
pip =p_pipe(str, strp);

if (pip ) {
Space_tackle(strp[0], arr);
Space_tackle(strp[1], pp);

}
else if(an==1){
Space_tackle(andp[0], arr);
}


else if(re==1){
Space_tackle(rep[0], arr);
Space_tackle(rep[1], pp);
}
else if(re==0) {
Space_tackle(str, arr);
}
else{
Space_tackle(str, arr);
}

if(pip ==0 && an==0 && re==0){
return 1;
}
else if(pip ==1)
return 2;

else if(an==1){
return 3;
}
else if(re==1){
return 4;
}
}



int main()
{
char input[100], *tt[100];
char* hh[100];

char* pp1[100];
char* pp2[100];
int e=0;
while (1) {

if (Input(input))
continue;
char x[100];
strcpy(x,input);
if(strcmp(x,"exit")==0){
printf("\n\nSHell EXITED\n\n");
break;
}
e =Main_checking(input,tt, hh);
if (e == 1)
excecution(tt);

if (e == 2)
epipe(tt, hh);

if (e == 3){
char J[100];
int j;
for(int k=0;k<100;k++){
if(x[k]== '&'){
j=k;
break;
}
}
int c=0;
for(int k=j+2;k<100;k++){
J[c]=x[k];
c++;
}
printf("%s",J);
int h = Main_checking(J,pp1,pp2);
excecution(tt);
printf("\n\n");
excecution_2(pp1);
}


if (e == 4){

execredir(tt,hh);
}


}
return 0;
}


