


void ft_move_cursor_and_clear(t_cursor cursor)
{
    char *move_cursor;

    move_cursor = tgetstr("cm", NULL); //get capapbility to move cursor
    ft_putstr(tgoto(move_cursor, cursor,col_position-1, cursor.line_position-1),1); //use togoto to move cursor 
    ft_putstr(tgetstr("cd", NULL),1); //clear display before showing command
}
void set_terminal (struct termios *termios, struct termios *old, int fd)
{
    tcgetattr(fd, old);          // Get and save current terminal attributes in 'old'
    tcgetattr(fd, termios);      // Get current terminal attributes in 'termios'
    termios->c_lflag &= ~(ECHO | ICANON | ISIG);  // Modify 'termios' to disable echo, canonical mode, and signals
    tcsetattr(fd, TCSANOW, termios);  // Apply the modified 'termios' attributes immediately
}


void ft_init_readline(t_readline *readline)/* Initializes terminal-related settings in the t_readline structure. */
{
    int load;

    readline->term_type = getenv("TERM");
    if (readline->term_type == NULL)
    {
        readline->term_type="xterm-256color";
    }
    load = tgetent(NULL, readline->term_type);
    if (!load)
    {
        ft_putstr_fd(" couldn't find or access terminal capabilities for the specified terminal type\n",1);
    }
    readline->path = ttyname(1); //gets the path name of current terminal
    readline->term_fd= open(readline->path, O_RDWR);
    if (!isatty(readline->term_fd)) 
        ft_putstr_fd("Cannot access terminal for input and output\n", 1);
    readline->column_count= tgetnum("co");
    readline->line_count = tgetnum("li");
    readline->cursor.col_position = 0;
    readline->cursor.line_position = 0;
    readline->line=NULL;
}


void ft_get_cursor_position(int *x, int *y)
{
    static char s[20];
    int i =0;
    int first=0;

    write(0, "\033[6n", 4);
    read(0,s,19);
    while (s[i])
    {
        if (first==0 && ft_isdigit(s[i]))
        {
            *x=ft_atoi(s+i);
            while(s[i]!=';')
                i++;
            first=1;
        }
        else if(first==1 && ft_isdigit(s[i]))
        {
            *y= ft_atoi(s+i);
            first=2;
        }
        i++;
    }
}