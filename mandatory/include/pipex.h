/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:35:19 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/15 15:52:00 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		end[2];
	pid_t	pid;
	char	**argv;
	char	**envp;
	int		argc;
	char	*env_paths;
}		t_pipex;

void	ft_pipex(t_pipex pipex);
void	parent(t_pipex pipex);
char	*get_path(char *cmd, char *envp_paths);
void	child(t_pipex pipex);
void	error(char *str);
void	error_msg(char *str);
void	execute(char *cmd, t_pipex pipex);
char	*get_env_paths(char **envp);

char	**check_for_special(char *cmd);

#endif