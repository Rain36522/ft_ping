
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
}

int	ft_echo_reply(struct icmphdr *icmpheader, t_result *result, int len, struct iphdr *iphdr)
{
	unsigned int    stop;
    uint32_t        start;
    int             sequence;
    struct in_addr  addr;
    char            ip[15];


    stop = ft_get_time_us();
    start = ntohl(icmpheader->un.echo.sequence);
    sequence = ntohs(icmpheader->un.echo.sequence);
	addr.s_addr = iphdr->saddr;
    inet_ntop(AF_INET, &addr, ip, sizeof(ip));
    printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%2.f ms\n", len, ip, sequence, iphdr->ttl)
}

static void ft_read_msg(t_result *result, char *buffer, int len)
{
	struct icmphdr	*icmpheader;
	struct iphdr	*iphdr;
	int				type;

	iphdr = (struct iphdr *)buffer;
	icmpheader = (struct icmphdr *)(buffer + (iphdr->ihl * 4));
	type = icmpheader->type;
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
		printf("%sEcho request!%s", YELLOW, RESETN);
	else if (type == 0)
	{
		printf("%sEcho reply!%s", GREEN, RESETN);
		return (ft_echo_reply(icmpheader, &result, len, iphdr));
	}
	else
		printf("%sUnknow echo request!%s", ORANGE, RESETN);
	return (0);
}

void	ft_recv_ping(int socketfd, t_result *result, int argv)
{
	char				buffer[1024];
	struct msghdr		msg;
	struct iovec		iov;
	struct sockaddr_in	src_addr;
	struct timeval		stop_time;
	struct timeval		start_time;
    int                 len;

	iov.iov_base = buffer;
	iov.iov_len = sizeof(buffer);

	msg.msg_name = &src_addr;
	msg.msg_namelen = sizeof(src_addr);
	msg.msg_iov = &iov;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	while (!len)
		printf("Waiting for messae!\n");
		len = recvmsg(socketfd, &msg, 0);
		if (len < 0)
			fprintf(stderr, "%sEroor while reading request!%s", ORANGE, RESETN);
		else if (len > 0)
			ft_read_msg(result, buffer, len);
}