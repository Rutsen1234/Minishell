/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_continue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsimon <rsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:27:24 by rsimon            #+#    #+#             */
/*   Updated: 2024/08/15 22:16:03 by rsimon           ###   ########.fr       */
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

int	should_use_heredoc(const char *command)
{
	return (strcmp(command, "cat") == 0 || strcmp(command, "grep") == 0);
}

void	execute_command(const char *command)
{
	int	result;

	result = system(command);
	if (result == -1)
		perror("Failed to execute command");
}

void	add_token(t_token *token_list, t_token_type type, char *content, int index, char *line)
{
	t_token		*tmp;
	char 		*delimiter;
	char		*command;
	char		*line_buffer;
	size_t		len;
	ssize_t		read;

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
	if (type == HEREDOC)
	{
		delimiter = extract_delimiter(line);
		if (delimiter == NULL)
		{
			fprintf(stderr, "Failed to extract delimiter\n");
			free(tmp->next->value);
			free(tmp->next);
			return ;
		}
		command = token_list->next->value;
		line_buffer = NULL;
		len = 0;
		if (should_use_heredoc(command))
		{
			char filename[256];
			snprintf(filename, sizeof(filename), "heredoc_%d.txt", index);
			FILE *file = fopen(filename, "w");
			if (!file)
			{
				perror("Failed to open file");
				free(delimiter);
				free(tmp->next->value);
				free(tmp->next);
				return ;
			}
			while (1)
			{
				printf("heredoc> ");
				read = getline(&line_buffer, &len, stdin);
				if (read == -1)
				{
					perror("getline failed");
					break ;
				}
				line_buffer[strcspn(line_buffer, "\n")] = 0;
				if (strcmp(line_buffer, delimiter) == 0)
				{
					break ;
				}
				if (strlen(line_buffer) > 0)
				{
					fprintf(file, "%s\n", line_buffer);
				}
			}
			fclose(file);
			char command_with_input[512];
			if (strcmp(command, "cat") == 0)
				snprintf(command_with_input, sizeof(command_with_input), "cat %s", filename);
			else 
				snprintf(command_with_input, sizeof(command_with_input), "%s < %s", command, filename);
			execute_command(command_with_input);
			exit(0);
			remove(filename);
		}
		else 
		{
            while (1)
			{
				printf("heredoc> ");
				read = getline(&line_buffer, &len, stdin);
				if (read == -1)
				{
					perror("getline failed");
					break;
                }
				line_buffer[strcspn(line_buffer, "\n")] = 0;
				if (strcmp(line_buffer, delimiter) == 0)
					break;
            }
		}
		free(line_buffer);
		free(delimiter);
	}
}
