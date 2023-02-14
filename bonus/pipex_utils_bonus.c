/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/13 12:15:51 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

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

	cmd_arr = ft_split(cmd, ' ');
	env_path = get_path(cmd_arr[0], pipex.envp);
	if (!env_path)
		error("command not found");
	if (execve(env_path, cmd_arr, pipex.envp) < 0)
		error("execve");
}

void	error(char *str)
{
	perror(str);
	exit(1);
}
