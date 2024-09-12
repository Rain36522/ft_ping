/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:16:54 by pudry             #+#    #+#             */
/*   Updated: 2024/08/28 17:06:25 by pudry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned int    ft_get_time_us(void)
{
	struct timeval      tv;
	static long unsigned int   sec_offset;

	gettimeofday(&tv, NULL);
	if (!sec_offset)
		sec_offset = (long unsigned int)tv.tv_sec;
	return (tv.tv_sec - sec_offset + tv.tv_usec);
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