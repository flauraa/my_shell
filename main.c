#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char input_str[1000] = "";
	char cwd[1024];

	while(1){
		getcwd(cwd, sizeof(cwd));
		printf(" \033[1;31m%s \033[35m%s \033[1;32m$\033[0m ", 
			getenv("USER"), cwd);

		scanf ("%[^\n]%*c", input_str);

		char* args[1000];
		for(int i = 0; i < 1000; i++) args[i] = NULL;

		int i = 0;
		args[i] = strtok(input_str, " ");
		while(args[i] != NULL) args[++i] = strtok(NULL, " ");

		if(!strcmp(args[0], "cd")){
			chdir(args[1]);
			continue;
		}

		pid_t pid = fork();
		if(pid == 0) execvp(args[0], args);
		else if(pid < 0) printf("%s\n", "error");
		else wait(NULL);
	}
}