/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:26:59 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/01 13:37:44 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

int	main(int argc, char **argv)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of Parameters.\n", STDERR_FILENO);
		ft_putstr_fd("Write: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
		return (-1);
	}
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror ("error while opening infile");
		exit(-1);
	}
	fd_outfile = open(argv[4], O_RDONLY);
	if (fd_outfile == -1)
	{
		perror ("error while opening outfile");
		exit(-1);
	}
	return (0);
}
