void ft_signal_handler(int sig) {
    if (sig == SIGINT) {
        write(STDOUT_FILENO, "\n", 1);
    } else if (sig == SIGQUIT) {
        write(STDOUT_FILENO, "^\Quit (core dumped)\n", 20);
    }
}
