

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
int ft_heredoc(int *fd, t_redirection *redirect) {
    printf("am i hear?\n\n\n");
    char *delimiter = redirect->file_name;  // Use the file_name field for the delimiter
    char *line = NULL;
    size_t len = 0;

    *fd = open("heredoc_tmp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (*fd < 0)
        return ft_file_err("heredoc_tmp.txt");

    while (1) {
        printf("> ");
        if (getline(&line, &len, stdin) == -1)
            break;
        if (strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
            (line[ft_strlen(delimiter)] == '\n' || line[ft_strlen(delimiter)] == '\0'))
            break;
        write(*fd, line, ft_strlen(line));
    }

    free(line);
    close(*fd);
    *fd = open("heredoc_tmp.txt", O_RDONLY);
    if (*fd < 0)
        return ft_file_err("heredoc_tmp.txt");

    dup2(*fd, STDIN_FILENO);
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
