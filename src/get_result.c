
#include "ft_ping.h"

static double  ft_get_min(t_result *ptr)
{
	double  min_value = 1000000;

	while (ptr)
	{
		if (ptr->time < min_value)
			min_value = ptr->time;
		ptr = ptr->next;
	}
	return (min_value);
}

static double  ft_get_max(t_result *ptr)
{
	double  max_value = -1;

	while (ptr)
	{
		if (ptr->time > max_value)
			max_value = ptr->time;
		ptr = ptr->next;
	}
	return(max_value);
}

static double  ft_get_avarage(t_result *ptr)
{
	int     i;
	double  tmp;

	i = 0;
	tmp = 0;
	if (!ptr)
		return (0);
	while (ptr)
	{
		i ++;
		tmp += ptr->time;
		ptr = ptr->next;
	}
	return (tmp / i);
}

static double  ft_get_mdev(t_result *ptr, double avrg)
{
	int     i;
	double  tmp;

	if (!ptr)
		return (0);
	tmp = 0;
	while (ptr)
	{
		i ++;
		if (ptr->time < avrg)
			tmp -= ptr->time - avrg;
		else
			tmp += ptr->time - avrg;
		ptr = ptr->next;
	}
	return (tmp / i);
}

static unsigned int ft_get_lost(t_result *ptr)
{
	int j;

	j = 0;
	if (!ptr)
		return (100);
	while (ptr)
	{
		if (ptr->icmptype != 8 && ptr->icmptype != 0)
			j ++;
		ptr = ptr->next;
	}
	return ((100 * j) / send_packet);
}

static unsigned int    get_list_size(t_result *ptr, int argv)
{
	unsigned int    i;

	while (ptr)
	{
		if (ptr->icmptype == 0 && argv)
			i ++;
		else if (ptr->icmptype != 0)
			i ++;
		ptr = ptr->next;
	}
	return (i);
}

void    ft_print_stat(t_result *ptr)
{
	double  avrg;

	avrg = ft_get_avarage(ptr);
	printf("--- %s ping statistics ---\n", strctargv.strip);
	printf("%d packets transmitted, %d received, %d", send_packet, get_list_size(ptr, strctargv.flagv), ft_get_lost(ptr));
	printf("%% packet loss, time %.0fms\n", get_time_ms() - prog_start_time);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", \
	ft_get_min(ptr), avrg,ft_get_max(ptr), ft_get_mdev(ptr, avrg));
	free_list(ptr);
}