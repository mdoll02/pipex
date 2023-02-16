/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:35:19 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/16 11:12:55 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // perror | strerror
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid;
	char	**argv;
	char	**envp;
	int		argc;
	char	*env_paths;
}		t_pipex;

void	ft_pipex(t_pipex pipex, int cmd_count);
void	execute(char *cmd, t_pipex pipex);

void	open_files(t_pipex *pipex, char **argv, int argc);

char	*get_path(char *cmd, char *envp_paths);
char	*get_env_paths(char **envp);

void	error(char *str);
void	error_msg(char *str);

char	**check_for_special(char *cmd);
int		count_quotes(int *i, char *str);

#endif