/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:05:38 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/11 11:32:35 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

// int	check_args(char **argv, int argc)
// {
// 	if (ft_strncmp("here_doc", argv[1], 9) == 0)
// 	{
// 		return (6);
// 	}
// 	return (argc);
// }

void	handel_fd(t_pipex pipex)
{
	// if (ft_strncmp("here_doc", pipex.argv[1], 9) == 0)
	// {
	// 	pipex.limiter = pipex.argv[2];
	// 	here_doc(pipex);
	// }
	pipex.fd_infile = open(pipex.argv[1], O_RDONLY);
	if (pipex.fd_infile == -1)
		error (pipex.argv[1]);
	pipex.fd_outfile = open(pipex.argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.fd_outfile == -1)
		error (pipex.argv[4]);
}

// void	here_doc(t_pipex pipex)
// {
// 	char	*tmp;	

// 	pipex.fd_infile = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	if (pipex.fd_infile == -1)
// 		error ("error while creating tmp for here doc");
// 	while (1)
// 	{
// 		write(STDOUT_FILENO, "pipe heredoc> ", 14);
// 		tmp = get_next_line(STDIN_FILENO);
// 		if (!tmp)
// 			error("error while reading line from heredoc");
// 		write(pipex.fd_infile, tmp, ft_strlen(tmp));
// 		if (ft_strncmp(pipex.limiter, tmp, ft_strlen(pipex.limiter)) == 0)
// 			break ;
// 		free(tmp);
// 	}
// 	free(tmp);
// 	close(pipex.fd_infile);
// }
