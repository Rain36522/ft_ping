
#include "ft_ping.h"

void	free_list(t_result *ptr)
{
	t_result	*ptr2;

	while (ptr)
	{
		ptr2 = ptr->next;
		free(ptr);
		ptr = ptr2;
	}
}


t_result	*ft_add_chainlink(t_result *ptr, int id, double time, int	icmptype)
{
	t_result    *chainlink;
	t_result	*mem_ptr;

	chainlink = (t_result *)malloc(sizeof(chainlink));
	if (!chainlink)
	{
		free_list(ptr);
		ft_exit(RED, "Error alocating memory", 12);
	}
	ft_bzero(chainlink, sizeof(t_result));
	chainlink->id = id;
	chainlink->time = time;
	chainlink->icmptype = icmptype;
	if (!ptr)
		return (chainlink);
	mem_ptr = ptr;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = chainlink;
	return (mem_ptr);
}
