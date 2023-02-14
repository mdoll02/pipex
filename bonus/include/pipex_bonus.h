/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:35:19 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/14 14:43:37 by mdoll            ###   ########.fr       */
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
	char	*limiter;
}		t_pipex;

void	ft_pipex(t_pipex pipex, int cmd_count);
char	*get_path(char *cmd, char **envp);
void	error(char *str);
void	execute(char *cmd, t_pipex pipex);
int		check_args(char **argv, int argc);
void	handel_fd(t_pipex pipex);
char	**check_for_special(char *cmd);

#endif