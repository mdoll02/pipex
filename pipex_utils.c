/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:50:02 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/03 15:47:03 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i], ':');
	i = 0;
	while (paths[i++] != NULL)
		printf("%s\n", paths[i]);
	printf("Command: %s\n", cmd);
	return (NULL);
}

void	child(int fd1, int *end, char *cmd1, char **envp)
{
	ft_printf("child\t");
	dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(fd1);
	get_path(cmd1, envp);
}

void	parent(int fd2, int *end, char *cmd2, char **envp)
{
	ft_printf("parent\t");
	dup2(end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(end[1]);
	close(fd2);
	get_path(cmd2, envp);
}
