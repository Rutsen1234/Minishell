

char *ft_get_input(t_readline readline, int *status, struct termios old_term)
{
    t_lines_list *current;

    current = ft_init_history(&character, &newline_break);
    read(readline->term_fd, &character, 6);

    if (current && (character == D_KEY_DOWN || character== D_KEY_UP))
        current = ft_handle_history_buttons(character, readline, current);
}