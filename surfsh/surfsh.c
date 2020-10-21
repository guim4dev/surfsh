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
	  	printf("PEGUEI!");
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
	fgets(reference, BASE_LEN, stdin);
	reference[strlen(reference) -1] = '\0';
	printf("\033[0m");
	printf("\n");
}

void getUserIntInput(char *str, int *reference) {
	char *input;
	char *endptr = NULL;
	printf("\033[1;36m");
	printf("%s\n", str);
	printf("\033[1;32m");
	fgets(input, BASE_LEN, stdin);
    *reference = (int) strtol(input, &endptr, 10);

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
	// PASSO 1
	getUserStringInput("Qual comando quer executar?", command);
	strcat(path, command);
	// VALIDANDO ERRO PASSO 1 - enquanto nao for executavel, perguntamos para o usuario ate ele fornecer um comando válido
	while(pathNotExecutable(path)) {
		strcpy(path, basePath);
		getUserStringInput("Comando inválido. Por favor, insira novamente:", command);
		strcat(path, command);
	}
	// PASSO 3
	getUserIntInput("Quantos argumentos você quer digitar?", &numberOfArguments);
	char *arguments[numberOfArguments+2];
	char *argument;

	arguments[0] = command; // setando primeiro item do array arguments para o comando em si
	arguments[numberOfArguments+1] = NULL; // setando ultimo item do array para NULL

	// PASSO 5 - perguntamos os argumentos numberOfArguments vezes e armazenamos nas posições corretas do array
	int i;
	char text[BASE_LEN];
	char num[BASE_LEN];
	for (i = 1; i <= numberOfArguments; ++i) {
		sprintf(num, "%d", i);
		strcpy(text, "Insira o argumento ");
		strcat(text, num);
		argument = malloc(BASE_LEN);
		getUserStringInput(text, argument);
		arguments[i] = argument;
	}

	// PASSO 6
	pid_t child_pid = fork();
	if (child_pid == 0) { // roda somente no processo filho
		execv(path, arguments); // execv passando path e array com os argumentos
	}
	// PASSO 7 - roda somente no processo pai, faz o wait do processo filho
	else {
		wait(NULL);
		printf("\033[1;32m");
		printf("\nTarefa concluída.\n");
	}
}

int main(void) {
	signal(SIGINT, sig_handler);
	init_shell();
	run_shell();
	return 0;
}
