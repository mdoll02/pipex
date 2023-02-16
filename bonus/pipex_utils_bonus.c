/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/16 12:39:34 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

char	*get_path(char *cmd, char *envp_paths)
{
	int		i;
	char	**path_parts;
	char	*cmd_path;

	i = -1;
	path_parts = ft_split(envp_paths, ':');
	while (path_parts[++i])
	{
		path_parts[i] = ft_strjoin(path_parts[i], "/");
		cmd_path = ft_strjoin(path_parts[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	i = -1;
	while (path_parts[++i])
		free(path_parts[i]);
	free(path_parts);
	return (NULL);
}

void	execute(char *cmd, t_pipex pipex)
{
	char	*path_part;
	char	**cmd_arr;

	cmd_arr = check_for_special(cmd);
	path_part = get_path(cmd_arr[0], pipex.env_paths);
	if (!path_part)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path_part, cmd_arr, pipex.envp) < 0)
		error("execve");
	free(path_part);
	free(cmd_arr);
}

void	error(char *str)
{
	perror(str);
	exit(1);
}

void	error_msg(char *str, int fd)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
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
