#include "ft_ping.h"

int         socketfd;
t_result    *result_ptr = NULL;
int         send_packet = 0;
double   	prog_start_time;
t_argv      strctargv;

void    ft_print_help()
{
	printf("./ft_ping IP_ADDRESSS FLAG VALUE\n");
	printf("-c      Stop after sending count ECHO_REQUEST packets\n");
	printf("-v      Verbose output\n");
	exit(0);
}

static void    setup_signal()
{
    struct sigaction sa;

    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1)
        ft_exit(RED, "Error setting up signal handler!", 1);
}


int main(int argc, char **argv)
{
	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
		ft_print_help();
	else if (getuid() != 0)
		ft_exit(ORANGE, "The program must be run as root!\n", 1);
	ft_bzero(&strctargv, sizeof(strctargv));
	strctargv = ft_parsing(argc, argv);
	prog_start_time = get_time_ms();
	setup_signal();
	ft_ping(strctargv.binip, strctargv.flagv, strctargv.icycle);
	ft_print_stat(result_ptr);
	return (0);
}