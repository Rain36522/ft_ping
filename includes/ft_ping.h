/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:12:28 by pudry             #+#    #+#             */
/*   Updated: 2024/07/12 12:12:35 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <signal.h>
#include "../libft/includes/libft.h"

#define RESET   " \033[0m"
#define RESETN  "\033[0m\n"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"
#define ORANGE  "\033[38;5;208m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"
#define	HBLUE	"\033[48;5;17m"
#define HRED	"\033[41m"
#define BOLD	"\033[1m"
#define NOBOLD	"\033[0m"
#define DEBUG printf("\033[31m %s, %d, %s", __FILE__, __LINE__, "\033[0m\n");


extern int socketfd;

typedef struct s_argv {
    uint32_t    binip;
    int         icycle;
    int         flagv;
} t_argv;

typedef struct s_result {
    double          mint;
    double          maxt;
    double          averaget;
    unsigned int    reponse;
} t_result;

typedef struct s_pingData {
    unsigned int    time;
    char            addr_ip[16];
    int             sequence;
    int             ttl;
};

void    ft_exit(char *color, char *str, int i);
void	ft_exit_fd(char *color, char *str, int fd, int i);

t_argv  ft_parsing(int argc, char **argv);

void    ft_ping(int quantity, char *ipTarget);
void    ft_recv_ping(int sockfd, struct s_result *results);

unsigned short  ft_calcul_cksum(void *b, int len);
unsigned int    ft_get_time_us(void);

