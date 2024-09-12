/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:00:37 by pudry             #+#    #+#             */
/*   Updated: 2024/09/04 15:01:49 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

double	get_time_ms(void)
{
	struct timeval		time;
	unsigned long long	ltime;

	gettimeofday(&time, NULL);
	ltime = time.tv_sec * 1000000 + time.tv_usec;
	return (ltime / 1000.0);
}

void	sig_handler(int sig)
{
	if (sig != 2)
		return;
	write(1, "\n", 1);
	ft_print_stat(result_ptr);
	close(socketfd);
	exit(0);
}

void	ft_exit(char *color, char *str, int i)
{
	ft_putstr_fd(color, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESETN, 2);
	exit(i);
}

void	ft_exit_fd(char *color, char *str, int fd, int i)
{
	ft_putstr_fd(color, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESETN, 2);
	close(fd);
	exit(i);
}