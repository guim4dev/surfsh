#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define BASE_LEN 50

void init_shell() {
		printf("\033[1;32m");
    printf("\n\n******************"
        "************************");
    printf("\n\n\n\t**** Surf Shell ****");
    printf("\n\n\t-A Shell mais braba já feita-");
    printf("\n\n\n\n*******************"
        "***********************");
    printf("\n\n");
    sleep(1);
}

void getUserStringInput(char *str, char *reference) {
	printf("\033[1;36m");
	printf("%s\n", str);
	printf("\033[1;32m");
	scanf("%s", reference);
	printf("\033[0m");
	printf("\n");
}

void getUserIntInput(char *str, int *reference) {
	printf("\033[1;36m");
	printf("%s\n", str);
	printf("\033[1;32m");
	scanf("%i", reference);
	printf("\033[0m");
	printf("\n");
}

int main(void){
	init_shell();

	char path[2*BASE_LEN] = "/bin/";
	char command[BASE_LEN];
	char argument[BASE_LEN];
	int numberOfArguments = 0;

	getUserStringInput("Qual comando quer executar?", command);
	strcat(path, command);
	getUserIntInput("Quantos argumentos você quer digitar?", &numberOfArguments);
	char* arguments[numberOfArguments+2];
	arguments[0] = command;
	arguments[numberOfArguments+1] = NULL;

	int i;
	for (i = 1; i <= numberOfArguments; ++i) {
		getUserStringInput("Insira o argumento:", argument);
		arguments[i] = argument;
	}

	pid_t child_pid = fork();
	if (child_pid == 0) {
		execv(path, arguments);
		return 0;
	}
	else {
		wait(NULL);
		printf("\033[1;32m");
		printf("\nTarefa concluída.\n");
		return 0;
	}
}
