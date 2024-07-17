#include <termios.h>

int micro_readline(char **line, int *status)
{
    t_readline readline;
    struct termios termios;
    struct termios old_termios;

    ft_init_readline(&readline);
    set_terminal(&termios, &old_termios,readline.term_fd);
    ft_get_cursor_position(&readline.cursor.line_position, &readline.cursor.col_position)
    *line = ft_get_input(readline, status, old_termios);

}

t_lines_list *ft_up_in_history(t_readline *readline, t_lines_list **history)
{
    ft_move_cursor_and_clear(readline->cursor);
    if((*history)->next)  // meaning we pressed up twice
    {
        *history =( *history)->next;
        if (*history)
        {
            (*history)->up_or_down = true;
            ft_print_char_list((*history)->char_list);
        }
    }
    else
    {
        if(history) // pressed one time up
        {
            (*history)->up_or_down = true;
            if((*history)->char_list)
                ft_print_char_list((*history)->char_list);
        }
    }
    return(*history);
}


t_lines_list	*ft_down_in_history(t_readline *readline,
				t_lines_list **history)
{
	ft_move_cursor_and_clear(readline->cursor);
	if ((*history))
	{
		if ((*history)->prev != NULL)
		{
			*history = (*history)->prev;
			(*history)->up_or_down = true;
		}
		ft_print_char_list((*history)->char_list);
	}
	return (*history);
}

