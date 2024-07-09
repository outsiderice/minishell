#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*int	main(int ac, char *av[])
{
	int pid;
	int fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		int x;
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) < 0)
			return (2);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) < 0)
			return (3);
		close(fd[0]);
		printf("I got this from a child process %d\n", y);
	}
	return (0);
}*/

 /*
int 	main(int ac, char *av[])
{
	int fd[7][2];
	int i;
	int j;
	int pid[7];
	
	i = 0;
	while (i < 7)
	{
		if (pipe(fd[i]) < 0)
			//hay que cerrarlas todas que se han abierto prev
			return (1);
		i++;
	}
	i = 0;
	while (i < 7)
	{
	//Child process one
		pid[i] = fork();
		if (pid[i] < 0)
			//all fd should be closed
			return (2);
		if (pid[i] == 0)
		{
			j = 0;
			while (j < 7)
			{
				if (j != i && j != i - 1)
				{
					close(fd[j][0]);
					close(fd[j][1]);
				}
				else
				{
					close(fd[j][0]);
					close(fd[j-1][1]);
				}
				j++;
			}
			int x;
			if (read(fd[i-1][0], &x, sizeof(int)) < 0)
				return (3);
			x += 1;
			if (write(fd[i][1], &x, sizeof(int)) < 0)
				return (4);
			close(fd[i-1][0]);
			close(fd[i][1]);
			return (0);
		}
		i++;
	}
	j = 0;
	while (j < 7)
	{
		if (j != 0 && j != 6)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		else
		{
			close(fd[j][0]);
			close(fd[j-1][1]);
		}
		j++;
	}
	int x;
	x = 10;
	//scanf("%d", &x);
	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return (8);
	if (read(fd[6][0], &x, sizeof(int)) < 0)
		return (9);
	printf("El resultado es %d\n", x);
	close(fd[0][1]); 
	close(fd[6][0]);
	i = 0;
	while (i < 7)
		waitpid(pid[i], NULL, 0);
	return (0);
}*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


void wait_pids(int pid[], int num_children) {
    int i = 0;
    while (i < num_children) {
        waitpid(pid[i], NULL, 0);
        i++;
    }
}

// Function to close all pipes
void close_pipes(int fd[7][2], int num_pipes) {
    int i = 0;
    while (i < num_pipes) {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
}

// Function to close unused file descriptors in child processes
void close_unused_fds(int fd[7][2], int current_child, int num_pipes) {
    int i = 0;
    while (i < num_pipes) {
        if (i != current_child) 
            close(fd[i][0]); // Close read end if not needed
        
		if (current_child != (num_pipes - 1) )
		{
        	if (i != (current_child + 1)) 
            	close(fd[i][1]); // Close write end if not needed
		}
		else
		{
			if (i != 0)
				close(fd[i][1]);
		}
        i++;
    }
}

// Function to close unused file descriptors in child processes
void close_unused_parent_fds(int fd[7][2], int num_pipes) 
{
    int i = 0;
    while (i < num_pipes) 
	{
        if (i !=  num_pipes - 1) {
            close(fd[i][0]); // Close read end if not needed
        }
        if (i != 0) {
            close(fd[i][1]); // Close write end if not needed
        }
        i++;
    }
}

int main(int ac, char *av[]) 
{
    int fd[7][2];
    int i = 0;
    int pid[7];
	int num_pipes = 7;

    // Create pipes
    while (i < num_pipes) 
	{
        if (pipe(fd[i]) < 0) {
            // Close previously opened pipes before returning
            close_pipes(fd, num_pipes);
            return (1);
        }
        i++;
    }

    // Fork child processes
    i = 0;
    while (i < num_pipes) 
	{
		
        pid[i] = fork();
        if (pid[i] < 0) 
		{
            // Close all pipes before returning
            close_pipes(fd, num_pipes);
            return (2);
        }
        if (pid[i] == 0) 
		{
            // In child process
            close_unused_fds(fd, i, num_pipes);

            // Implement child process functionality here
			int x;
			if (read(fd[i][0], &x, sizeof(int)) < 0)
				return (3);
			dprintf(1, "Child process %d reads %d\n", i, x);
			x += 1;
			if (write(fd[(i+1)% num_pipes][1] , &x, sizeof(int)) < 0)
				return (4);
			close(fd[i][0]);
			close(fd[(i+1)%num_pipes][1]);
			return (0);

            //close_pipes(fd, num_pipes);
        }
        i++;
    }

    // Parent process: close all pipe file descriptors
    close_unused_parent_fds(fd, num_pipes);
	int x = 0;
	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return (4);
	if (read(fd[num_pipes-1][0], &x, sizeof(int)) < 0)
		return (3);
	close(fd[0][1]);
	close(fd[num_pipes-1][0]);
	printf("Result is %d\n", x);

    // Wait for child processes to finish
    wait_pids(pid, num_pipes);
	// waitpid(pid[6], NULL, 0);

    return (0);
}

/*
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// Wait for all child processes
void wait_pids(int pid[], int num_children) {
    int i = 0;
    while (i < num_children) {
        waitpid(pid[i], NULL, 0);
        i++;
    }
}

// Function to close all pipes
void close_pipes(int fd[7][2], int num_pipes) {
    int i = 0;
    while (i < num_pipes) {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
}

// Function to close unused file descriptors in child processes
void close_unused_fds(int fd[7][2], int current_child, int num_pipes) {
    int i = 0;
    while (i < num_pipes) {
        if (i != current_child) {
            close(fd[i][0]); // Close read end if not needed
        }
        if (i != current_child + 1) {
            close(fd[i][1]); // Close write end if not needed
        }
        i++;
    }
}

// Function to close unused file descriptors in parent process
void close_unused_parent_fds(int fd[7][2], int num_pipes) {
    int i = 0;
    while (i < num_pipes) {
        if (i != 0) {
            close(fd[i][1]); // Close write end if not needed
        }
        if (i != num_pipes - 1) {
            close(fd[i][0]); // Close read end if not needed
        }
        i++;
    }
}


int main(int ac, char *av[]) {
    int fd[7][2];
    int i = 0;
    int pid[7];
    int num_pipes = 7;

    // Create pipes
    while (i < num_pipes) {
        if (pipe(fd[i]) < 0) {
            // Close previously opened pipes before returning
            close_pipes(fd, num_pipes);
            return (1);
        }
        i++;
    }

    // Fork child processes
    i = 0;
    while (i < num_pipes) {
        pid[i] = fork();
        if (pid[i] < 0) {
            // Close all pipes before returning
            close_pipes(fd, num_pipes);
            return (2);
        }
        if (pid[i] == 0) {
            // In child process
            close_unused_fds(fd, i, num_pipes);

            // Read from previous pipe
            int x;
            if (read(fd[i][0], &x, sizeof(int)) < 0) {
                return (3);
            }

            dprintf(1, "Child process %d reads %d\n", i, x);
            x += 1;

            // Write to next pipe
            if (write(fd[(i + 1) % num_pipes][1], &x, sizeof(int)) < 0) {
                return (4);
            }

            close(fd[i][0]);
            close(fd[(i + 1) % num_pipes][1]);
            return (0);
        }
        i++;
    }

    // Parent process: close all unused pipe file descriptors
    close_unused_parent_fds(fd, num_pipes);

    // Start the chain by writing to the first pipe
    int x = 0;
    if (write(fd[0][1], &x, sizeof(int)) < 0) {
        return (4);
    }

    // Read the final result from the last pipe
    if (read(fd[num_pipes - 1][0], &x, sizeof(int)) < 0) {
        return (3);
    }

    printf("Result is %d\n", x);

    // Close the last remaining pipe ends
    close(fd[0][1]);
    close(fd[num_pipes - 1][0]);

    // Wait for child processes to finish
    wait_pids(pid, num_pipes);

    return (0);
}*/
