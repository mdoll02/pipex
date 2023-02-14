/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:45:07 by mdoll             #+#    #+#             */
/*   Updated: 2023/02/14 14:44:32 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex_bonus.h"

static int	ft_count_char(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ' && s[i])
				i++;
			count++;
		}
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
				i++;
			if (s[i + 1] != '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static void	ft_count(char *s, size_t *i_, size_t *len_)
{
	size_t	i;
	size_t	len;

	i = *i_;
	len = *len_;
	while (s[i] == ' ' && s[i])
		i++;
	len = i;
	if (s[len] == 39)
	{
		len++;
		while (s[len] != 39 && s[len] != '\0')
			len++;
		i++;
	}
	else
	{
		while (s[len] != ' ' && s[len] != '\0')
			len++;
	}
	*len_ = len;
	*i_ = i;
}

static char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**mod_split(char *cmd)
{
	size_t			i;
	size_t			len;
	char			**sp_string;
	int				index;

	index = 0;
	i = 0;
	if (cmd == NULL)
		return (NULL);
	sp_string = malloc (sizeof(char *) * (ft_count_char(cmd) + 2));
	if (sp_string == NULL)
		return (NULL);
	while (index < (ft_count_char(cmd) + 1))
	{
		ft_count(cmd, &i, &len);
		sp_string[index] = ft_substr(cmd, i, len - i);
		if (!sp_string[index])
			return (ft_free(sp_string));
		index++;
		i = len;
	}
	sp_string[index] = NULL;
	return (sp_string);
}

char	**check_for_special(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			count++;
		if (cmd[i] == 34)
			cmd[i] = 39;
		i++;
	}
	if (count % 2 != 0)
		error("syntax error");
	return (mod_split(cmd));
}
