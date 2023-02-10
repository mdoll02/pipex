/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/10 12:15:56 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != check_args(argv, argc))
		error("Wrong number of arguments");
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	ft_pipex(pipex);
	return (0);
}

void	ft_pipex(t_pipex pipex)
{
	int		pipe_ret;

	pipe_ret = pipe(pipex.end);
	if (pipe_ret == -1)
		error("error while creating pipe");
	pipex.pid = fork();
	if (pipex.pid == -1)
		error("error while forking");
	if (pipex.pid == 0)
		child(pipex);
	waitpid(pipex.pid, NULL, WNOHANG);
	if (pipex.pid > 0)
		parent(pipex);
}
