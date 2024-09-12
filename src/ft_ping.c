/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:30:56 by pudry             #+#    #+#             */
/*   Updated: 2024/09/04 14:30:56 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ping.h"

static struct sockaddr_in  ft_init_packet(uint32_t ipTarget, struct icmp *icmpHeader)
{
	struct sockaddr_in  destaddr;

	ft_bzero(&destaddr, sizeof(destaddr));
	destaddr.sin_family = AF_INET;
	destaddr.sin_port = 0;
	destaddr.sin_addr.s_addr = ipTarget;
	icmpHeader->icmp_type = ICMP_ECHO;
	icmpHeader->icmp_code = 0;
	icmpHeader->icmp_id = getpid();
	icmpHeader->icmp_seq = 1;
	return (destaddr);
}


static void ft_gen_packet(struct icmp *icmpHeader, char *packet)
{
	icmpHeader->icmp_cksum = 0;
	ft_memcpy(packet, icmpHeader, sizeof(struct icmp));
	icmpHeader->icmp_cksum = ft_calcul_cksum((unsigned short *)packet, sizeof(struct icmp));
	ft_memcpy(packet, icmpHeader, sizeof(struct icmp));
}

t_result	ft_loop_ping(int icycle, struct sockaddr_in destaddr, struct icmp icmpHeader, int argv)
{
	int			data;
	int			sequence;
	char		packet[64];
	double		start_time;
	t_result	result;

	(void)result;
	printf("Icycle = %d\n", icycle);
	sequence = 1;
	while (sequence <= icycle)
	{
		icmpHeader.icmp_seq = htons(sequence);
		ft_bzero(&result, sizeof(result));
		ft_bzero(&packet, sizeof(packet));
		ft_gen_packet(&icmpHeader, packet);
		start_time = get_time_ms();
		data = sendto(socketfd, packet, sizeof(packet), 0, (struct sockaddr *)&destaddr, sizeof(destaddr));
		send_packet ++;
		if (data <= 0)
			fprintf(stderr, "Error sending request ...\n");
		else
			ft_recv_ping(socketfd, &result, argv, start_time);
		usleep(300000);
		sequence ++;
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
		ft_exit(RED, "Error opening socket\n", 1);
	ft_loop_ping(icycle, destaddr, icmpHeader, argv);
	close(socketfd);
}