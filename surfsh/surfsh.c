#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LEN 20

void init_shell() {
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
	printf("%s", str);
	scanf("%s", reference);
}

void getUserIntInput(char *str, int *reference) {
	printf("%s", str);
	scanf("%i", reference);
}

int main(void){
	init_shell();

	char path[MAX_LEN] = "/bin/";
	char command[MAX_LEN];
	int numberOfArguments = 0;

	getUserStringInput("Qual comando quer executar?", command);
	getUserIntInput("Quantos argumentos você quer digitar?", &numberOfArguments);
	char arguments[80];
	arguments[0] = command;

	int i;
	for (i = 1; i <= numberOfArguments; ++i) {
		char argument[MAX_LEN];
		getUserStringInput("Insira o argumento:", argument);
		arguments[i] = argument;
	}
	printf("%s", command);
	printf("%s", path);
	printf("%i", numberOfArguments);
	// pid_t child_pid = fork();
	// if (child_pid == 0) {
	// 	//Run ping command
	// 	execlp("/bin/ping","ping","8.8.8.8","-c","50",NULL);
	// 	return 0;
	// }
	// else {
	// 	wait(NULL);
	// 	printf("Task is done\n");
	// 	return 0;
	// }
}
