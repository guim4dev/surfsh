#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t child_pid = fork();
	if (child_pid == 0) {
		//Run ping command
		execlp("/bin/ping","ping","8.8.8.8","-c","50",NULL);
		return 0;
	}
	else {
		wait(NULL);
		printf("Task is done\n");
		return 0;
	}
}
