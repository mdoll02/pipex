/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/06 14:16:01 by mdoll            ###   ########.fr       */
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
		if (!paths[i])
			error("strjoin error");
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			error("strjoin error");
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

void	execute(char *cmd, char **envp)
{
	char	*env_path;
	char	**cmd_arr;

	cmd_arr = ft_split(cmd, ' ');
	env_path = get_path(cmd_arr[0], envp);
	fprintf(stderr, "env path for:%s = %s\n", cmd, env_path);
	execve(env_path, cmd_arr, envp);
}

void	child(int fd1, int *end, char *cmd1, char **envp)
{
	dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd1);
	execute(cmd1, envp);
}

void	parent(int fd2, int *end, char *cmd2, char **envp)
{
	dup2(end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(end[1]);
	close(fd2);
	execute(cmd2, envp);
}

void	error(char *str)
{
	perror(str);
	exit(-1);
}
