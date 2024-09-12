/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:11:36 by pudry             #+#    #+#             */
/*   Updated: 2024/08/05 18:11:36 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"



static void	ft_check_ip_char(char *ip)
{
	int	j = 0;
	int	k = 0;
	int	wrong_pos = 0;

	if (ip[0] == '.' || ip[ft_strlen(ip) - 1] =='.')
		wrong_pos = 1;

	for (size_t i = 0; i < ft_strlen(ip) && !wrong_pos; i ++)
	{
		if (ip[i] == '.')
		{
			k ++;
			if (j == 0 || j > 3)
				wrong_pos = 1;
			j = 0;
		}
		else if (!ft_isdigit(ip[i]))
			ft_exit(RED, "Wrong character in ip address!", 1);
		else
			j++;
	}
	if (wrong_pos || j > 3 || k != 3)
		ft_exit(RED, "Wrong quantity or position for \".\"in ip address!", 1);
}

static void	ft_check_ip(char *ip)
{
	char    **a;
	int     ierror;
	if (ft_strlen(ip) < 7 || ft_strlen(ip) > 15)
		ft_exit(RED, "Wrong len for ip address!", 1);

	ft_check_ip_char(ip);

	if (!(a = ft_split(ip, '.')))
		ft_exit(RED, "Error alocating memory", 12);
	for (size_t i = 0; a[i] && !ierror; i ++)
	{
		if ((ft_atoi(a[i])) > 255)
			ierror = 1;
	}
	for (size_t i = 0; a[i]; i ++)
		free(a[i]);
	free(a);
	if (ierror)
		ft_exit(RED, "Ip address as a to big value!", 1);
	printf("%sIp address is valide!%s", GREEN, RESETN);
}

int ft_is_ip(char *ip)
{
	while (*ip)
	{
		if (!ft_strchr("0123456789.", *ip))
			return (0);
	}
	return (1);
}

static void	ft_resolve_name_addr(uint32_t *binip, char *name)
{
	struct addrinfo hints;
	struct addrinfo	*res;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_protocol = SOCK_STREAM;

	if (getaddrinfo(name, NULL, &hints, &res))
		ft_exit(RED, "Error while resolving adresse name!", 1);
	if (!res)
		ft_exit(RED, "Unknow argument!", 1);
	binip = res->ai_addr;
	freeaddrinfo(res);
}

t_argv  ft_parsing(int argc, char **argv)
{
	int     c = 0;
	int     ip = 0;
	t_argv  arg;

	ft_bzero(&arg, sizeof(t_argv));
	if (argc < 3 || argc > 6)
		ft_exit(RED, "Wrong argument quantity!", 1);
	for (int i = 1; i < argc; i ++)
	{
		if (!ft_strcmp(argv[i], "-v") && !arg.flagv)
			arg.flagv = 0;
		else if (!ft_strcmp(argv[i], "-c") && !c)
			c = i;
		else if (ft_isInt(argv[i]) && !arg.icycle)
			arg.icycle = i;
		else if (!ip)
		{
			if (ft_is_ip(argv[i]))
			{
				ft_check_ip(argv[i]);
				if (inet_pton(AF_INET, argv[ip], &arg.binip) <= 0)
					ft_exit(RED, "Error while converting ip in binary!", 1);
			}
			else
				ft_resolve_name_addr(&arg.binip, argv[i]);
			ip = 1;
		}
		else
			ft_exit(RED, "Unknow argument!", 1);
	}
	if (!(arg.icycle && c))
		ft_exit(RED, "Unknow argument! Try ./ft_ping --help", 1);
	if (!ip)
		ft_exit(RED, "Ip adresse is missing!", 1);
	return (arg);    
}
