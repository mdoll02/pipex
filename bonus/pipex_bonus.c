/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/13 09:40:27 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		cmd_count;

	if (argc < 5)
		error("Invalid number of arguments");
	cmd_count = 2;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	pipex.fd_infile = open(pipex.argv[1], O_RDONLY);
	if (pipex.fd_infile == -1)
		error (pipex.argv[1]);
	pipex.fd_outfile = open(pipex.argv[argc - 1], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.fd_outfile == -1)
		error (pipex.argv[argc - 1]);
	dup2(pipex.fd_infile, STDIN_FILENO);
	while (cmd_count < argc - 2)
	{
		ft_pipex(pipex, cmd_count);
		cmd_count++;
	}
	dup2(pipex.fd_outfile, STDOUT_FILENO);
	execute(argv[argc - 2], pipex);
	return (0);
}

void	ft_pipex(t_pipex pipex, int cmd_count)
{
	int		pipe_ret;
	int		end[2];

	pipe_ret = pipe(end);
	if (pipe_ret == -1)
		error("error while creating pipe");
	pipex.pid = fork();
	if (pipex.pid == -1)
		error("error while forking");
	if (pipex.pid == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		execute(pipex.argv[cmd_count], pipex);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		waitpid(pipex.pid, NULL, WNOHANG);
	}
}
