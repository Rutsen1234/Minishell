/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_continue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:27:24 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/16 01:46:36 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*extract_delimiter(char *content)
{
	char	*delimiter_start;
	char	*delimiter;

	delimiter_start = strstr(content, "<<");
	if (!delimiter_start)
	{
		fprintf(stderr, "No heredoc delimiter found\n");
		return (NULL);
	}
	delimiter_start += 2;
	while (*delimiter_start == ' ' || *delimiter_start == '\t')
	{
		delimiter_start++;
	}
	delimiter = strdup(delimiter_start);
	if (delimiter == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (NULL);
	}
	delimiter[strcspn(delimiter, " \t\n")] = '\0';
	return (delimiter);
}

void	add_token(t_token *token_list, t_token_type type, char *content,
		int index)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_token *)malloc(sizeof(t_token));
	if (tmp->next == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return ;
	}
	tmp->next->index = index;
	tmp->next->type = type;
	tmp->next->value = strdup(content);
	if (tmp->next->value == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		free(tmp->next);
		return ;
	}
	tmp->next->next = NULL;
}
