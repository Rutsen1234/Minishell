t_lines_list *ft_init_history(long *character, int *newline_break)//adding history to the histiry list
{
    t_lines *current;
    static bool init_history = false;

    current = ft_create_line_node(); //creating a node to hold history information
    *character =0;

    if (init_history == false) //it's the first time
    {
        g_vars->history = NULL;
        init_history = true;
    }
    current->next = g_vars.history;
    if(g_vars.history)
        g_vars.history->prev = current;
    g_vars.history = current;
    *newline_break = 1;
    return (current);
}

t_lines_list *ft_handle_history_buttons(long character, t_readline readline, t_lines_list *current)
{
    if (current && character == D_KEY_UP)
        current = ft_up_in_history(&readline, &current);
    else if (current && character == D_KEY_DOWN)
        current = ft_down_in_history(&readline, &current);
    return(current);
}