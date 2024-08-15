/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtokenforheredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeltahi <haeltahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:27:24 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/16 02:34:46 by haeltahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*extract_delimiter1(char *content)
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

void	execute_command(const char *command)
{
	int	result;

	result = system(command);
	if (result == -1)
		perror("Failed to execute command");
}

void add_token_herdoc_extend(s_tmp *tmp)
{
	snprintf(tmp->filename, sizeof(tmp->filename), "heredoc_%d.txt", 1);
	tmp->file = fopen(tmp->filename, "w");
	while (1)
	{
		printf("heredoc> ");
		tmp->read_result = getline(&tmp->line_buffer, &tmp->len, stdin);
		tmp->line_buffer[strcspn(tmp->line_buffer, "\n")] = 0;
		if (strcmp(tmp->line_buffer, tmp->delimiter) == 0)
			break ;
		if (strlen(tmp->line_buffer) > 0)
			fprintf(tmp->file, "%s\n", tmp->line_buffer);
	}
	fclose(tmp->file);
	if (strcmp(tmp->command, "cat") == 0)
		snprintf(tmp->command_with_input, sizeof(tmp->command_with_input), "cat %s",
			tmp->filename);
	else
		snprintf(tmp->command_with_input, sizeof(tmp->command_with_input), "%s < %s",
			tmp->command, tmp->filename);
	execute_command(tmp->command_with_input);
	exit(0);
}

void	add_tokenforheredoc(t_token *token_list,
		char *line)
{
	s_tmp tmp;

	tmp.line_buffer = NULL;
	tmp.len = 0;
	tmp.tmp = token_list;
	tmp.delimiter = extract_delimiter1(line);
	if (!tmp.delimiter && fprintf(stderr, "Failed to extract delimiter\n"))
		return ;
	tmp.command = token_list->next->value;
	if (strcmp(tmp.command, "cat") == 0 || strcmp(tmp.command, "grep") == 0)
		add_token_herdoc_extend(&tmp);
else 
		{
            while (1)
			{
				printf("heredoc> ");
				tmp.read = getline(&tmp.line_buffer, &tmp.len, stdin);
				tmp.line_buffer[strcspn(tmp.line_buffer, "\n")] = 0;
				if (strcmp(tmp.line_buffer, tmp.delimiter) == 0)
					break;
            }
		free(tmp.line_buffer), free(tmp.delimiter);
		execute_command(tmp.command);
		exit(0);
	}
}
