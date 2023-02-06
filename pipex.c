/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/06 14:15:21 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of Parameters.\n", STDERR_FILENO);
		ft_putstr_fd("Write: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
		exit(-1);
	}
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		error ("error while opening infile");
	fd_outfile = open(argv[4], O_RDWR | O_TRUNC);
	if (fd_outfile == -1)
		error("error while opening outfile");
	pipex(fd_infile, fd_outfile, argv, envp);
	return (0);
}

void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		end[2];
	int		pipe_ret;
	pid_t	pid;

	pipe_ret = pipe(end);
	if (pipe_ret == -1)
		error("error while creating pipe");
	pid = fork();
	if (pid == -1)
		error("error while forking");
	if (pid == 0)
		child(fd1, end, argv[2], envp);
	waitpid(pid, NULL, 0);
	if (pid > 0)
		parent(fd2, end, argv[3], envp);
}
