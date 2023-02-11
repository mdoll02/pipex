/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/11 12:11:08 by mdoll            ###   ########.fr       */
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
	while (cmd_count < argc - 2)
	{
		ft_pipex(pipex, cmd_count);
		cmd_count++;
	}
	parent(pipex);
	return (0);
}

void	ft_pipex(t_pipex pipex, int cmd_count)
{
	int		pipe_ret;

	pipe_ret = pipe(pipex.end);
	if (pipe_ret == -1)
		error("error while creating pipe");
	pipex.pid = fork();
	if (pipex.pid == -1)
		error("error while forking");
	if (pipex.pid == 0)
		child(pipex, cmd_count);
	waitpid(pipex.pid, NULL, WNOHANG);
}
