
#include "ft_ping.h"

int	ft_type3(int icode)
{
	printf("%sDestination unreachable! : %s", YELLOW, BOLD);
	if (icode == 0)
		ft_putstr_fd("network", 1);
	else if (icode == 1)
		ft_putstr_fd("host", 1);
	else if (icode == 2)
		ft_putstr_fd("protocol", 1);
	else if (icode == 3)
		ft_putstr_fd("port", 1);
	else if (icode == 4)
		ft_putstr_fd("fragmentation", 1);
	else if (icode == 5)
		ft_putstr_fd("source route", 1);
	else if (icode == 6)
		ft_putstr_fd("network unknow", 1);
	else if (icode == 7)
		ft_putstr_fd("host unknow", 1);
	else if (icode == 8)
		ft_putstr_fd("host isolation", 1);
	else if (icode == 9)
		ft_putstr_fd("network prohibited", 1);
	else if (icode == 10)
		ft_putstr_fd("host prohibited", 1);
	else if (icode == 11)
		ft_putstr_fd("network administratively prohibited", 1);
	else if (icode == 12)
		ft_putstr_fd("host administrativly prohibited", 1);
	printf("!%s", RESETN);
	return (0);
}

int	ft_echo_reply(struct icmphdr *icmpheader, t_result *result, int len, struct iphdr *iphdr, double start)
{
    int             sequence;
    struct in_addr  addr;
    char            ip[15];

	(void) result;

    sequence = ntohs(icmpheader->un.echo.sequence);
	addr.s_addr = iphdr->saddr;
    inet_ntop(AF_INET, &addr, ip, sizeof(ip));
    printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", len, ip, sequence, iphdr->ttl, get_time_ms() - start);
	return (1);
}

static int ft_read_msg(t_result *result, char *buffer, int len, int argv, double start_time)
{
	struct icmphdr	*icmpheader;
	struct iphdr	*iphdr;
	int				type;

	iphdr = (struct iphdr *)buffer;
	icmpheader = (struct icmphdr *)(buffer + (iphdr->ihl * 4));
	type = icmpheader->type;
	result_ptr = ft_add_chainlink(result_ptr, ntohs(icmpheader->un.echo.sequence), get_time_ms() - start_time, type);
	if (type == 3)
		ft_type3(icmpheader->code);
	else if (type == 4)
		printf("%sSource quench%s", YELLOW, RESETN);
	else if (type == 5)
		printf("%sRedirection%s", YELLOW, RESETN);
	else if (type == 11)
		printf("%sTime exceeded%s", YELLOW, RESETN);
	else if (type == 12)
		printf("%sParametre problem%s", YELLOW, RESETN);
	else if (type == 8)
	{
		if (argv)
			printf("%sEcho request!%s", YELLOW, RESETN);
		return (0);
	}
	else if (type == 0)
		return (ft_echo_reply(icmpheader, result, len, iphdr, start_time));
	else
		printf("%sUnknow echo request!%s", ORANGE, RESETN);
	return (0);
}

void	ft_recv_ping(int socketfd, t_result *result, int argv, double start_time)
{
	char				buffer[4096];
	struct msghdr		msg;
	struct iovec		iov;
	struct sockaddr_in	src_addr;
	int					read_result;
    int                 len;

	ft_bzero(&buffer, sizeof(buffer));
    ft_bzero(&iov, sizeof(iov));
    ft_bzero(&msg, sizeof(msg));

    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);
    msg.msg_name = &src_addr;
    msg.msg_namelen = sizeof(src_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
	msg.msg_flags = 0;
	len = 0;
	read_result = 0;
	while (len == 0 || read_result == 0)
	{
		len = recvmsg(socketfd, &msg, 0);
		if (len < 0)
			fprintf(stderr, "%sError while reading request!%s", ORANGE, RESETN);
		else if (len > 0)
			read_result = ft_read_msg(result, buffer, len, argv, start_time);
	}
}