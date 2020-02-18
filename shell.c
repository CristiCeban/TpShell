#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MAX 1024
static char line[MAX];
char *var;
char *val;

void affiche_cmd(char *argv[]);
int parse_line(char *s, char **argv[]);
void print_dir();
int takeInput(char* str);
void simple_cmd(char *str);
int parse_line_redir (char * s, char **argv[], char **in, char **out);
int redir_cmd(char*argv[],char*in,char*out);
int parse_line_pipes(char*s,char***argv[],char**in,char**out);
void sighandler(int sig_num);
int main(int argc, char *argv[])
{
	
	char *in,*out;
	char option;
	while(1)
	{
		signal(SIGTSTP, sighandler); 
		print_dir();
		fflush(NULL);

		if (!fgets(line, MAX, stdin)) 
			return 0;
		char *cmd = line;
		parse_line(cmd,&argv);
		if (var!=NULL && val!= NULL && strstr(cmd,var)!=NULL)
			printf("%s",val);
		redir_cmd(&cmd,in,out);
	}
	
	//parse_line_pipes("cmd1 toto|cmd2 tata titi|cmd3",&argv,&in,&out);
	//parse_line("chaine=valeur",&argv);
	//parse_line_redir("command -v <input >output",&argv,&in,&out);
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


void simple_cmd(char *str){
	if (strstr(str, "exit") != NULL) {
		exit(0);
	}
	else if (strstr(str, "cd") != NULL){
		chdir("..");
	}
	else if (strstr(str, "./" )!= NULL){
		system(str);
	}
	else if (strstr(str, "ls")!=NULL){
		system(str);
	}
	else if (strstr(str,"$"!=NULL && var!=NULL && val!=NULL)){
		system(*val);
	}
}

int parse_line(char *s, char **argv[]){
	if(strstr(s,"=")!=NULL){
		char key[] = "=";
		char *temp = strdup(s);
		char *token = strtok(temp,key);
		int i = 0;
		while(token != NULL){
			if(i == 0){
				var =(char*)malloc(sizeof(char)*strlen(token)+1);
				var = token;
				i++;
			}
			else if(i == 1){
				val = (char*)malloc(sizeof(char)*strlen(token)+1);
				val = token;
			}
			token = strtok(NULL,key);
		}
		(*argv)[i] = NULL;
		//affiche_cmd(*argv);
	}
	else{
	char key[] = " ";
	char *temp = strdup(s);
	char *token = strtok(temp,key);
	int i = 0;
	while(token != NULL){
		(*argv)[i] = malloc(sizeof(char*)*(strlen(temp)+1));
		(*argv)[i++] = token;
		token = strtok(NULL,key);
	}
	(*argv)[i] = NULL;
	//affiche_cmd(*argv);
	}
	return 0;
}

int parse_line_redir (char *s, char **argv[], char **in, char **out){
	char key[] = " ";
	char *temp = strdup(s);
	char *token = strtok(temp,key);
	int i = 0;
	while(token != NULL){
		if(strstr(token,"<") != NULL){
			*in =(char*)malloc(sizeof(char)*(strlen(token)+1));
			char *temp1 = token;
			temp1++;
			*in=temp1;
		}
		else if(strstr(token,">") != NULL){
			*out =(char*)malloc(sizeof(char)*(strlen(token)+1));
			char *temp1 = token;
			temp1++;
			*out = temp1;
		}
		(*argv)[i] = malloc(sizeof(char*)*(strlen(token)+1));
		(*argv)[i++] = token;
		token = strtok(NULL,key);
	}
	(*argv)[i] = NULL;
	affiche_cmd(*argv);
	return 0;
}

int redir_cmd(char*argv[],char*in,char*out){
	simple_cmd(*argv);
}

int parse_line_pipes(char*s,char***argv[],char**in,char**out){
	char key[] = "|";
	char *temp = strdup(s);
	char *token = strtok(temp,key);
	int count = 0;
	int i = 0;
	while(s[i]!=NULL){
		if (s[i]=='|')
		count++;
		i++;
	}
	i = 0;
	char **tempPipe = (char**)malloc(sizeof(char*)*(count+1));
	while(token != NULL){
		tempPipe[i] = (char*)malloc(sizeof(char)*(strlen(token)+1));
		tempPipe[i++] = token;
		token = strtok(NULL,key);
	}
	tempPipe[i]=NULL;
	**argv=malloc(sizeof(char**)*(count+1));
	key[0] = ' ';
	for(int j = 0;j<=count;j++){
		char *temp1 = strdup(tempPipe[j]);
		token = strtok(temp1,key);
		int k = 0;
		count = 0;
		int it = 0;
		while(tempPipe[j][it]!=NULL){
			if (tempPipe[j][it++]==' ')
				count++;
		}
		**argv[j]=malloc(sizeof(char**)*(count + 1));
		while(token != NULL){
			**argv[k] = malloc(sizeof(char*)*(strlen(temp1)+1));
			**argv[k++] = token;
			token = strtok(NULL,key);
		}
	}
	(**argv)[i] = NULL;
	return 0;
}

void sighandler(int sig_num) 
{ 
    signal(SIGTSTP, sighandler); 
    printf("Cannot execute Ctrl+Z\n"); 
} 