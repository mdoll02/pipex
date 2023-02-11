/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:35:19 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/11 12:11:30 by mdoll            ###   ########.fr       */
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
	int		end[2];
	pid_t	pid;
	char	**argv;
	char	**envp;
	int		argc;
	char	*limiter;
}		t_pipex;

void	ft_pipex(t_pipex pipex, int cmd_count);
void	parent(t_pipex pipex);
char	*get_path(char *cmd, char **envp);
void	child(t_pipex pipex, int cmd_count);
void	error(char *str);
void	execute(char *cmd, t_pipex pipex);
int		check_args(char **argv, int argc);
void	handel_fd(t_pipex pipex);
void	here_doc(t_pipex pipex);

#endif