/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:56:33 by pudry             #+#    #+#             */
/*   Updated: 2024/05/28 16:34:13 by pudry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short  ft_calcul_cksum(void *b, int len)
{
    unsigned short  *buffer;
    unsigned int    sum = 0;

    buffer = b;
    while (len > 1)
    {
        sum += *buffer;
        buffer ++;
        len -=2;
        if (sum & 0xFFFF0000)
            sum = (sum & 0xFFFF) + (sum >> 16);
    }
    if (len == 1)
        sum += *(unsigned char *)buffer;
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return ~sum;
}
