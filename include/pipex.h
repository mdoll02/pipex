/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:35:19 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/03 15:30:52 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // perror | strerror
# include <sys/wait.h>

void	pipex(int fd1, int fd2, char **arvg, char **envp);
void	parent(int fd2, int *end, char *cmd2, char **envp);
char	*get_path(char *cmd, char **envp);
void	child(int fd1, int *end, char *cmd1, char **envp);

#endif