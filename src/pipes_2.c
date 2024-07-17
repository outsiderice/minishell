#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void close_pipes(int **pipes, int first, int last, int len)
{
	while (first <= last && first < len )
	{
		close(pipes[first][0]);
		close(pipes[first][1]);
		free(pipes[first]);
		++first;
	}
	free(pipes);
	return;
}

int main(int ac, char **av)
{
	int	**pipes;
	int	i;
	int ttl_cmnds;
	ttl_cmnds = 3;
	int	pid[ttl_cmnds];

	pipes = malloc(sizeof(int *) * (ttl_cmnds - 1));
	i = 0;
	while (i < ttl_cmnds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < ttl_cmnds)
	{
		if (i != ttl_cmnds - 1 && pipe(pipes[i]) == -1)
		{
			printf("error in pipe\n");
			return (1);
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if(i != 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i != ttl_cmnds -1)
				dup2(pipes[i][1], STDOUT_FILENO);

			close_pipes(pipes, 0, i, ttl_cmnds - 1);
            if (i == 0)
				execlp("ping", "ping", "-c", "5", "google.com", NULL);
			else if (i == 1)
				execlp("grep", "grep", "tt", NULL);
			else if (i == 2)
				execlp("grep", "grep", "3", NULL);
				//execlp("wc", "wc", NULL);
		}
		i++;
	}
	i = 0;
	close_pipes(pipes, 0, ttl_cmnds, ttl_cmnds - 1);
	while (i < ttl_cmnds - 1)
	{
		waitpid(pid[i], NULL, 0);
		++i;
	}
	return (0);
}
/*
int main(int ac, char **av)
{
	int	fd[2];
	if (pipe(fd) == -1)
		return(1);
	int pid1 = fork();
	if (pid1 < 0) 
		return(2);
	if (pid1 == 0)
	{
		//child process
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	int pid2 = fork();
	if (pid2 == 0)
        {
                //child process
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
						char *a;
				printf("GYJ");
				read(fd[0], &a, 8);
				write(1, &a, 8);
		close(fd[0]);
                execlp("grep", "grep", "tt", NULL);
        }
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av) {
    int pipes[2][2];
    int i;
    int pid[2];

    i = 0;
    while (i < 2) {
        if (pipe(pipes[i]) == -1) {
            printf("error in pipe\n");
            return 1;
        }
        pid[i] = fork();
        if (pid[i] < 0) {
            printf("error in fork\n");
            return 2;
        }
        if (pid[i] == 0) {
            if (i == 0) {
                // First child process
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
                execlp("ping", "ping", "-c", "5", "google.com", NULL);
            } else if (i == 1) {
                // Second child process
                dup2(pipes[0][0], STDIN_FILENO);
                close(pipes[0][0]);
                close(pipes[0][1]);
                close(pipes[1][0]);
                close(pipes[1][1]);
                execlp("grep", "grep", "rtt", NULL);
            }
        }
        i++;
    }
    // Close pipes in the parent process
    close(pipes[0][0]);
    close(pipes[0][1]);
    close(pipes[1][0]);
    close(pipes[1][1]);
    // Wait for both child processes
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);

    return 0;
}*/

