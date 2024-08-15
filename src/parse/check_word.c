/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:13:09 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/13 15:13:14 by rsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_bachslashes(char *word, int *index, int back_slash)
{
	while (word[*index] == 92)
	{
		back_slash++;
		(*index)++;
	}
	return (back_slash);
}

int	ft_get_first_double_quotes(char *word, int *index, int *back_slash)
{
	int	quote;

	quote = 0;
	if (*index != 0 && word[*index - 1] != 92)
		quote += 2;
	else
	{
		if (*back_slash % 2 == 0)
			quote += 2;
	}
	(*index)++;
	*back_slash = 0;
	return (quote);
}

int	ft_get_first_single_quotes(char *word, int *index, int *back_slash)
{
	int	quote;

	quote = 0;
	if (word[*index - 1] != 92)
	{
		quote += 1;
	}
	else
	{
		if (*back_slash % 2 == 0)
		{
			quote += 1;
		}
	}
	(*index)++;
	*back_slash = 0;
	return (quote);
}

void	ft_get_close_double_quotes(char *word, int *index, int *back_slash,
																	int *quote)
{
	if (word[*index - 1] != 92)
		*quote -= 2;
	else
	{
		if (*back_slash % 2 == 0)
			*quote -= 2;
	}
	*back_slash = 0;
	(*index)++;
}

void	ft_get_close_single_quotes(int *index, int *back_slash,
																	int *quote)
{
	(*index)++;
	*quote -= 1;
	*back_slash = 0;
}
