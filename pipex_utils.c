/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/02 15:53:20 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

void	child(int fd1, int *end, char *cmd1)
{
	printf("child");
	dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd1);
	printf("ello im child\n");
	printf("%s\n", cmd1);
}

void	parent(int fd2, int *end, char *cmd2)
{
	printf("parent");
	dup2(end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(end[1]);
	close(fd2);
	printf("ello its me . da perent\n");
	printf("%s\n", cmd2);
}

void	pipex(int fd1, int fd2, char **argv)
{
	int		end[2];
	int		error;
	pid_t	pid;
	int		status;

	error = pipe(end);
	printf("created pipe\n");
	if (error == -1)
	{
		perror("error while creating pipe");
		exit(-1);
	}
	pid = fork();
	printf("%d\n", pid);
	if (pid == -1)
	{
		perror("error while forking");
		exit(-1);
	}
	else
		child(fd1, end, argv[2]);
	printf("%d\n", pid);
	waitpid(-1, &status, 0);
	parent(fd2, end, argv[3]);
}
