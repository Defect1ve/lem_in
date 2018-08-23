/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_alg_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:43:53 by ikotvits          #+#    #+#             */
/*   Updated: 2018/08/23 14:43:55 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*get_way(t_room *end, t_lem_in *lem)
{
	t_room		*room;
	t_relation	*relation;

	room = end;
	lem->queue = NULL;
	queue_add(lem, end->num);
	end->visited = 1;
	while (room && room->num != lem->start)
	{
		relation = lem->relation;
		while (relation && (relation->child != room ||
		relation->parent->visited != 0))
			relation = relation->next;
		if (!relation)
		{
			while (queue_rem(lem))
				;
			return (NULL);
		}
		queue_add(lem, relation->parent->num);
		if (relation->parent->num != lem->start)
			relation->parent->visited = 1;
		room = relation->parent;
	}
	return (lem->queue);
}

int		end_of_way(t_ways *ways, t_lem_in *lem)
{
	if (ways->way == NULL)
	{
		ways = lem->ways;
		while (ways->next && ways->next->next)
			ways = ways->next;
		free(ways->next);
		ways->next = NULL;
		return (1);
	}
	if (ways->way->room->num == lem->end &&
	ways->way->next->room->num == lem->start)
		return (1);
	return (0);
}

void	add_ways(t_lem_in *lem, t_room *end)
{
	t_ways		*ways;

	while (1)
	{
		if (!lem->ways)
		{
			lem->ways = (t_ways *)malloc(sizeof(t_ways));
			ways = lem->ways;
		}
		else
		{
			ways = lem->ways;
			while (ways->next)
				ways = ways->next;
			ways->next = (t_ways *)malloc(sizeof(t_ways));
			ways = ways->next;
		}
		ways->next = NULL;
		ways->way = get_way(end, lem);
		if (end_of_way(ways, lem))
			return ;
	}
}
