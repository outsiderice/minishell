/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_prototype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:04:15 by kate              #+#    #+#             */
/*   Updated: 2024/06/14 13:04:16 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <unistd.h>
/* pipe(fd) -> creates the 
*/


int main() {
    int pipefd[2];
    char buffer[128];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    write(pipefd[1], "Hello, world!", 13);
    read(pipefd[0], buffer, 13);

    printf("Read from pipe: %s\n", buffer);
    return 0;
}
