/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:44:56 by pudry             #+#    #+#             */
/*   Updated: 2024/08/07 11:44:56 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ping.h"

int	socketfd;

static struct sockaddr_in  ft_init_packet(uint32_t ipTarget, struct icmp *icmpHeader)
{
	struct sockaddr_in  destaddr;

	ft_bzero(&destaddr, sizeof(destaddr));
	destaddr.sin_family = AF_INET;
	destaddr.sin_port = 0;
	icmpHeader->icmp_type = ICMP_ECHO;
	icmpHeader->icmp_code = 0;
	icmpHeader->icmp_id = getpid();
	icmpHeader->icmp_seq = 1;    
	return (destaddr);
}


static void ft_gen_packet(struct icmp *icmpHeader, char *packet)
{
	unsigned int	timestamp;

	timestamp = ft_get_time_us();
	icmpHeader->icmp_dun.id_ts.its_otime = htonl(timestamp);
	icmpHeader->icmp_cksum = 0;
	ft_memcpy(packet, icmpHeader, sizeof(struct icmp));
	icmpHeader->icmp_cksum = ft_calcul_cksum((unsigned short *)packet, sizeof(struct icmp));
	ft_memcpy(packet, icmpHeader, sizeof(struct icmp));
}

t_result	ft_loop_ping(int icycle, struct sockaddr_in destaddr, struct icmp icmpHeader, int argv)
{
	int			data;
	char		packet[64];
	t_result	result;

	(void)result;
	while (icmpHeader.icmp_seq <= icycle)
	{
		printf("<======================================== %d ========================================>\n", icmpHeader.icmp_seq);
		ft_bzero(&result, sizeof(result));
		ft_bzero(&packet, sizeof(packet));
		ft_gen_packet(&icmpHeader, packet);
		data = sendto(socketfd, packet, sizeof(packet), 0, (struct sockaddr *)&destaddr, sizeof(destaddr));
		if (data <= 0)
			printf("Error sending request ...\n");
		else
			ft_recv_ping(socketfd, &result);
		sleep(1);
		icmpHeader.icmp_seq ++;
	}
	return (result);
}


void	ft_ping(uint32_t binip, int argv, int icycle)
{
	struct sockaddr_in	destaddr;
	struct icmp			icmpHeader;

	ft_bzero(&icmpHeader, sizeof(icmpHeader));
	destaddr = ft_init_packet(binip, &icmpHeader);
	socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (socketfd < 0)
		ft_error(1, "Error opening socket\n");
	ft_loop_ping(icycle, destaddr, icmpHeader, argv);
	// ft_print_result(results);
}