/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/16 09:54:04 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

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

void	child(t_pipex pipex)
{
	dup2(pipex.fd_infile, STDIN_FILENO);
	dup2(pipex.end[1], STDOUT_FILENO);
	close(pipex.end[0]);
	close(pipex.fd_infile);
	execute(pipex.argv[2], pipex);
}

void	parent(t_pipex pipex)
{
	dup2(pipex.end[0], STDIN_FILENO);
	dup2(pipex.fd_outfile, STDOUT_FILENO);
	close(pipex.end[1]);
	close(pipex.fd_outfile);
	execute(pipex.argv[pipex.argc - 2], pipex);
}
