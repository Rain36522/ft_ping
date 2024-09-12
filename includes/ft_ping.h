/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:57:00 by pudry             #+#    #+#             */
/*   Updated: 2024/09/04 14:57:00 by pudry            ###   ########.ch       */
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

typedef struct s_argv {
    uint32_t    binip;
    int         icycle;
    int         flagv;
    char        *strip;
} t_argv;

typedef struct s_result {
    double              time;
    int                 id;
    int                 icmptype;
    struct s_result    *next;
} t_result;

extern int      socketfd;
extern t_result *result_ptr;
extern int      send_packet;
extern double   prog_start_time;
extern t_argv   strctargv;



void    ft_exit(char *color, char *str, int i);
void	ft_exit_fd(char *color, char *str, int fd, int i);
void	sig_handler(int sig);

t_argv  ft_parsing(int argc, char **argv);

void	ft_ping(uint32_t binip, int argv, int icycle);
void	ft_recv_ping(int socketfd, t_result *result, int argv, double start_time);

unsigned short  ft_calcul_cksum(void *b, int len);
double	        get_time_ms(void);

t_result	*ft_add_chainlink(t_result *ptr, int id, double time, int	icmptype);
void	    free_list(t_result *ptr);

void    ft_print_stat(t_result *ptr);
