#include "ft_ping.h"

void    ft_print_help()
{
    printf("./ft_ping IP_ADDRESSS FLAG VALUE\n");
    printf("-c      Stop after sending count ECHO_REQUEST packets\n");
    printf("-v      Verbose output\n");
    exit(0);
}

int main(int argc, char **argv)
{
    int     quantity;
    t_argv  strctargv;

    // signal(SIGINT, fonction);
    if (argc == 2 && !ft_strcmp(argv[1], "--help"))
        ft_print_help();
    strctargv = ft_parsing(argc, argv);
    ft_ping(strctargv.binip, strctargv.flagv, strctargv.icycle);
    return (0);
}