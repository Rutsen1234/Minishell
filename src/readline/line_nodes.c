t_lines_list *ft_create_line_node(void)
{
    t_lines_list *ret;

    ret = (t_lines_list*)malloc(sizeof(t_lines_list));
    if (!ret)
        return (NULL);
    ret->char_list = NULL;
	ret->origin_char_list = NULL;
	ret->up_or_down = false;
	ret->next = NULL;
	ret->prev = NULL;
	ret->value = 0;
	ret->history = 0;
	return (ret); 
}