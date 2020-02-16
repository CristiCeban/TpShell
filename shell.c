#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX 1024
static char line[1024];

void affiche_cmd(char *argv[]);
int parse_line(char *s,char **argv[]);
void print_dir();
int takeInput(char* str);

int main(int argc,char *argv[])
{
	char option;
	char inputString[MAX];
		while(1){
			print_dir();
			fflush(NULL);
 
			if (!fgets(line, 1024, stdin)) 
				return 0;
 
		}

	return 0;
}


void affiche_cmd(char *argv[]){
	int i = 0;
	printf("\n");
	while(argv[i]!=NULL){
		printf(" %s ",argv[i++]);
	}
	printf("\n");
}

void print_dir(){
	char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\n%s$ ", cwd); 
}

/*int parse_line(char *s,char **argv[]){
	char key[]= " ";
	char *pch = strpbrk(s,key);
	int sizen=100;
	int sizec=1024;
	char temp[sizen][sizec];
	int i = 0;
	int nr_col=0;
	while(pch!=NULL){
		int j = 0;
		while(s!=pch){
			if(*s==' ')
			s++;
			temp[i][j]=*s;
			s++;
			j++;
		} 
		i++;
		pch = strpbrk (pch+1,key);
	}
	int j = 0;
	while(*s!='\0'){
		if(*s==' ')
		s++;
		temp[i][j]=*s;
		j++;
		s++;
	}
	i++;
	printf("\n");
	for(int k = 0;k<i;k++){
		int j = 0;
		while(temp[k][j]!='\0'){
			printf("%c",temp[k][j]);
			j++;
		}
		printf("\n");
	}
	temp[i][0]=NULL;
	//	affiche_cmd(temp);
	//affiche_cmd(*argv);
	return 0;
}*/
