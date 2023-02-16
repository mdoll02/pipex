/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:02:08 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/16 10:12:41 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

int	count_quotes(int *i, char *str)
{
	int	count;

	count = 0;
	if (str[(*i)] == 34)
	{
		(*i)++;
		while (str[(*i)] != 34 && str[(*i)])
			(*i)++;
		if (str[(*i) + 1] != '\0')
			count++;
	}
	if (str[(*i)] == 39)
	{
		(*i)++;
		while (str[(*i)] != 39 && str[(*i)])
			(*i)++;
		if (str[(*i) + 1] != '\0')
			count++;
	}
	return (count);
}
