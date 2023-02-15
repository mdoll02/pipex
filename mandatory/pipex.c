/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/15 15:50:10 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error("Invalid number of arguments");
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	pipex.fd_outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.fd_outfile == -1)
		error_msg(pipex.argv[4]);
	pipex.fd_infile = open(argv[1], O_RDONLY);
	if (pipex.fd_infile == -1)
	{
		write(pipex.fd_outfile, "       0\n", 9);
		error_msg(pipex.argv[1]);
	}
	pipex.env_paths = get_env_paths(envp);
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

void	error(char *str)
{
	perror(str);
	exit(1);
}

void	error_msg(char *str)
{
	write(STDERR_FILENO, "pipex: ", 7);
	perror(str);
	exit(0);
}

char	*get_env_paths(char **envp)
{
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}
