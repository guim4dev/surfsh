#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define BASE_LEN 50

static void run_shell();
static void init_shell();
static void getUserStringInput(char *str, char *reference);
static void getUserIntInput(char *str, int *reference);

void sig_handler(int signo) {
  if (signo == SIGUSR1) {
		run_shell();
	}
}

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
	// Limpar para não interferir na próxima chamada
	scanf("%*[^\n]");
	printf("\033[0m");
	printf("\n");
}

void getUserIntInput(char *str, int *reference) {
	printf("\033[1;36m");
	printf("%s\n", str);
	printf("\033[1;32m");
	while ((scanf("%i", reference)) != 1) { // Quando não for sucesso
		// Limpar
		scanf("%*[^\n]");
		printf("\033[1;36m");
		// Repetir pedido no loop
		printf("Valor não era um número inteiro. Por favor, insira novamente:\n");
		printf("\033[1;32m");
	}
	// Limpar para não interferir na próxima chamada
	scanf("%*[^\n]");
	printf("\033[0m");
	printf("\n");
}

int pathNotExecutable(char *path) {
	if ((access(path, F_OK) != -1) && (access(path, X_OK) != -1)) {
		return 0;
	}
	return 1;
}

void run_shell() {
	char path[2*BASE_LEN];
	char basePath[BASE_LEN];
	#ifdef __linux__ // LINUX
		strcpy(basePath,"/bin/");
	#else // MACOS
		strcpy(basePath,"/sbin/");
	#endif
	strcpy(path, basePath);

	char command[BASE_LEN];
	int numberOfArguments = 0;

	getUserStringInput("Qual comando quer executar?", command);
	strcat(path, command);
	while(pathNotExecutable(path)) {
		strcpy(path, basePath);
		getUserStringInput("Comando inválido. Por favor, insira novamente:", command);
		strcat(path, command);
	}
	getUserIntInput("Quantos argumentos você quer digitar?", &numberOfArguments);
	char *arguments[numberOfArguments+2];
	char *argument;

	arguments[0] = command;
	arguments[numberOfArguments+1] = NULL;

	int i;
	for (i = 1; i <= numberOfArguments; ++i) {
		argument = malloc(BASE_LEN);
		getUserStringInput("Insira o argumento:", argument);
		arguments[i] = argument;
	}

	pid_t child_pid = fork();
	if (child_pid == 0) {
		execv(path, arguments);
	}
	else {
		wait(NULL);
		printf("\033[1;32m");
		printf("\nTarefa concluída.\n");
	}
}

int main(void) {
	int pid = getpid();
	printf("%d", pid);
	signal(SIGINT, sig_handler);
	init_shell();
	run_shell();
	return 0;
}
