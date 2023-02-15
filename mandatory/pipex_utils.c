/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/15 12:51:56 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	execute(char *cmd, t_pipex pipex)
{
	char	*env_path;
	char	**cmd_arr;

	cmd_arr = check_for_special(cmd);
	env_path = get_path(cmd_arr[0], pipex.envp);
	if (!env_path)
	{
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	if (execve(env_path, cmd_arr, pipex.envp) < 0)
		error("execve");
	free(env_path);
	free(cmd_arr);
}

void	child(t_pipex pipex)
{
	pipex.fd_infile = open(pipex.argv[1], O_RDONLY);
	if (pipex.fd_infile == -1)
		error (pipex.argv[1]);
	dup2(pipex.fd_infile, STDIN_FILENO);
	dup2(pipex.end[1], STDOUT_FILENO);
	close(pipex.end[0]);
	close(pipex.fd_infile);
	execute(pipex.argv[2], pipex);
}

void	parent(t_pipex pipex)
{
	pipex.fd_outfile = open(pipex.argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.fd_outfile == -1)
		error (pipex.argv[4]);
	dup2(pipex.end[0], STDIN_FILENO);
	dup2(pipex.fd_outfile, STDOUT_FILENO);
	close(pipex.end[1]);
	close(pipex.fd_outfile);
	execute(pipex.argv[pipex.argc - 2], pipex);
}

void	error(char *str)
{
	perror(str);
	exit(1);
}
