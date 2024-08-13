

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

#include "../../headers/minishell.h"
#include "../../headers/execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int ft_open_and_redirect(int *fd, char *file_name, int flags, int std_fd) {
    *fd = open(file_name, flags, 0644);
    if (*fd < 0)
        return ft_file_err(file_name);
    dup2(*fd, std_fd);
    close(*fd);
    return 0;
}
int ft_great_than(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_CREAT | O_TRUNC | O_WRONLY, STDOUT_FILENO);
}
int ft_less_than(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_RDONLY, STDIN_FILENO);
}
int ft_double_great(int *fd, t_redirection *redirect) {
    return ft_open_and_redirect(fd, redirect->file_name, O_CREAT | O_APPEND | O_WRONLY, STDOUT_FILENO);
}
int ft_redirection(t_mini *mini, t_redirection *redirect) {
    while (redirect != NULL) {
        // printf("dfsdfsd\n");
        if (redirect->type == RE_GREAT && ft_great_than(&mini->red_fd[1], redirect))
            return 1;
        if (redirect->type == RE_LESS && ft_less_than(&mini->red_fd[0], redirect))
        {
            printf("r u here\n");
            return 1;
        }
        if (redirect->type == RE_DOUBLE_GREAT && ft_double_great(&mini->red_fd[1], redirect))
            return 1;
        redirect = redirect->next;
    }
    return 0;
}