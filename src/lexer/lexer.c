#include "minishell.h"
#include "../../headers/minishell.h"
	t_token	*first_token(void)
	{
		t_token	*new_token;

		new_token = (t_token *)malloc(sizeof(t_token));
		new_token->value = ft_strdup("NONE");
		new_token->next = NULL;
		new_token->type = NONE;
		new_token->index = 0;
		return (new_token);
	}
 void	create_tokens_list(t_token *tokens_list, char *line)
{
	int	table[5];

	table[3] = 1;
	table[4] = 0;
	table[0] = 0;
	while (line[table[0]])
	{
		table[1] = table[0];
		while (line[table[1]] == ' ' || line[table[1]] == '\t')
			table[1]++;
		if (ft_strrchr("|;><", line[table[1]]) != NULL)
			get_space_pipe_semi_redir(tokens_list, line, &table[1], &table[3]);
		if (ft_strrchr("\t <>;|", line[table[1]]) == NULL
			|| line[table[1]] == '\\')
		{
			table[2] = table[1];
			ft_get_word(tokens_list, line, table);
		}
		table[0] = table[1];
	}
	add_token(tokens_list, NEWLINE, ft_strdup("newline"), table[3],NULL);
}

t_token	*ft_lexer(char *line)
{
	t_token	*tokens_list;

	tokens_list = NULL;
	tokens_list = first_token();
	create_tokens_list(tokens_list, line);
	return (tokens_list);
}

void	ft_destoy_token_list(t_token *tokens_list)
{
		t_token	*tmp;

		tmp = NULL;
		while (tokens_list->type != NEWLINE)
		{
			tmp = tokens_list;
			tokens_list = tokens_list->next;
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			tmp = NULL;
		}
		if (tokens_list->type == NEWLINE)
		{
			free(tokens_list->value);
			tokens_list->value = NULL;
			free(tokens_list);
			tokens_list = NULL;
			write(1, CYAN, ft_strlen(CYAN));
		}
	}
char *extract_delimiter(char *content) {
    char *delimiter_start = strstr(content, "<<");
    if (!delimiter_start) {
        fprintf(stderr, "No heredoc delimiter found\n");
        return NULL;
    }

    delimiter_start += 2; // Skip `<<`

    // Skip any leading whitespace
    while (*delimiter_start == ' ' || *delimiter_start == '\t') {
        delimiter_start++;
    }

    // Extract delimiter and trim trailing whitespace
    char *delimiter = strdup(delimiter_start);
    if (delimiter == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Trim trailing spaces, tabs, and newlines
    delimiter[strcspn(delimiter, " \t\n")] = '\0';
    return delimiter;
}

// Function to check if a command should use heredoc
int should_use_heredoc(const char *command) {
    return (strcmp(command, "cat") == 0 || strcmp(command, "grep") == 0);
}

// Function to execute a command
void execute_command(const char *command) {
    // printf("Executing csdfdsfdsommand: %s\n", command); // Debug output

    int result = system(command);
    if (result == -1) {
        perror("Failed to execute command");
    }
}

void add_token(t_token *token_list, t_token_type type, char *content, int index, char *line) {
    t_token *tmp = token_list;

    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = (t_token *)malloc(sizeof(t_token));
    if (tmp->next == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    tmp->next->index = index;
    tmp->next->type = type;
    tmp->next->value = strdup(content);
    if (tmp->next->value == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tmp->next);
        return;
    }
    tmp->next->next = NULL;

    if (type == HEREDOC) {
        char *delimiter = extract_delimiter(line);
        if (delimiter == NULL) {
            fprintf(stderr, "Failed to extract delimiter\n");
            free(tmp->next->value);
            free(tmp->next);
            return;
        }
        
        char *command = token_list->next->value; // Assumes first token is the command

        char *line_buffer = NULL;
        size_t len = 0;
        ssize_t read;

        if (should_use_heredoc(command)) {
            char filename[256];
            snprintf(filename, sizeof(filename), "heredoc_%d.txt", index); // Unique filename

            FILE *file = fopen(filename, "w");
            if (!file) {
                perror("Failed to open file");
                free(delimiter);
                free(tmp->next->value);
                free(tmp->next);
                return;
            }

            while (1) {
    printf("heredoc> ");
    read = getline(&line_buffer, &len, stdin);
    if (read == -1) {
        perror("getline failed");
        break;
    }

    // Trim newline and check for delimiter match
    line_buffer[strcspn(line_buffer, "\n")] = 0;

    if (strcmp(line_buffer, delimiter) == 0) {
        // exit(0);
        break;
    }

    // Write valid content to the file
    if (strlen(line_buffer) > 0) {
        fprintf(file, "%s\n", line_buffer);
    }
}


            fclose(file);

            // Declare and use command_with_input to store the final command string
            char command_with_input[512];
            if (strcmp(command, "cat") == 0) {
                snprintf(command_with_input, sizeof(command_with_input), "cat %s", filename);
            } else {
                snprintf(command_with_input, sizeof(command_with_input), "%s < %s", command, filename);
            }

            // Execute the command
            execute_command(command_with_input);
            exit(0);
            // Optional: remove the temporary file after execution
            remove(filename);
        } else {
            // If the command does not use heredoc, read and ignore input
            while (1) {
                printf("heredoc> ");
                read = getline(&line_buffer, &len, stdin);
                if (read == -1) {
                    perror("getline failed");
                    break;
                }
                // Trim newline and check for delimiter match
                line_buffer[strcspn(line_buffer, "\n")] = 0;

                if (strcmp(line_buffer, delimiter) == 0) {
                    break;
                }
            }
        }
        free(line_buffer);
        free(delimiter);
    }
}
