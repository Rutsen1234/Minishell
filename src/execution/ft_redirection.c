

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

#include "../../headers/minishell.h"
#include "../../headers/execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// Function to open a file and redirect input/output
int ft_open_and_redirect(int *fd, char *file_name, int flags, int std_fd) {
    *fd = open(file_name, flags, 0644);
    if (*fd < 0)
        return ft_file_err(file_name);
    dup2(*fd, std_fd);
    close(*fd);
    return 0;
}

// Function to handle '>' redirection (stdout)
int ft_great_than(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_CREAT | O_TRUNC | O_WRONLY, STDOUT_FILENO);
}

// Function to handle '<' redirection (stdin)
int ft_less_than(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_RDONLY, STDIN_FILENO);
}

// Function to handle '>>' redirection (stdout append)
int ft_double_great(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_CREAT | O_APPEND | O_WRONLY, STDOUT_FILENO);
}

// Function to handle heredoc redirection
#include "../../headers/minishell.h"
#include "../../headers/execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to handle heredoc redirection
int ft_heredoc(int *fd, t_redirection *redirect) {
    char *delimiter = redirect->file_name;  // Use the file_name field for the delimiter
    char *line = NULL;
    size_t len = 0;

    *fd = open("heredoc_tmp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (*fd < 0) {
        perror("Error opening heredoc_tmp.txt for writing");
        return -1;
    }

    while (1) {
        printf("> ");
        if (getline(&line, &len, stdin) == -1) {
            perror("Error reading line");
            break;
        }

        // Check if the line matches the delimiter
        size_t delimiter_len = strlen(delimiter);
        if (strncmp(line, delimiter, delimiter_len) == 0 &&
            (line[delimiter_len] == '\n' || line[delimiter_len] == '\0')) {
            break;
        }

        // Write the line to the file
        if (write(*fd, line, strlen(line)) == -1) {
            perror("Error writing to heredoc_tmp.txt");
            free(line);
            close(*fd);
            return -1;
        }
    }

    free(line);
    close(*fd);

    // Reopen the file for reading
    *fd = open("heredoc_tmp.txt", O_RDONLY);
    if (*fd < 0) {
        perror("Error opening heredoc_tmp.txt for reading");
        return -1;
    }

    // Redirect stdin to the file
    if (dup2(*fd, STDIN_FILENO) == -1) {
        perror("Error duplicating file descriptor");
        close(*fd);
        return -1;
    }
    close(*fd);

    return 0;
}

// Function to handle all types of redirection including heredoc
int ft_redirection(t_mini *mini, t_redirection *redirect) {
    while (redirect != NULL) {
        if (redirect->type == RE_GREAT && ft_great_than(&mini->red_fd[1], redirect))
            return 1;
        if (redirect->type == RE_LESS && ft_less_than(&mini->red_fd[0], redirect))
            return 1;
        if (redirect->type == RE_DOUBLE_GREAT && ft_double_great(&mini->red_fd[1], redirect))
            return 1;
        if (redirect->type == RE_HEREDOC && ft_heredoc(&mini->red_fd[0], redirect))
            return 1;
        redirect = redirect->next;
    }
    return 0;
}