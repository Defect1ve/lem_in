/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:58:16 by ikotvits          #+#    #+#             */
/*   Updated: 2018/07/25 14:58:17 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	queue_add(t_lem_in *lem, int j)
{
	t_room	*room;
	t_queue *queue;

	if (!lem->queue)
	{
		lem->queue = (t_queue *)malloc(sizeof(t_queue));
		queue = lem->queue;
	}
	else
	{
		queue = lem->queue;
		while (queue->next)
			queue = queue->next;
		queue->next = (t_queue *)malloc(sizeof(t_queue));
		queue = queue->next;
	}
	queue->next = NULL;
	room = lem->room;
	while (room)
	{
		if (room->num == j)
			queue->room = room;
		room = room->next;
	}
}

t_room	*queue_rem(t_lem_in *lem)
{
	t_queue	*tmp;

	tmp = lem->queue;
	lem->queue = lem->queue->next;
	free(tmp);
	if (lem->queue == NULL)
		return (NULL);
	return (lem->queue->room);
}

void	parent_add(t_lem_in *lem, int i, int j)
{
	t_relation	*relation;
	t_room		*room;

	if (!lem->relation)
	{
		lem->relation = (t_relation *)malloc(sizeof(t_relation));
		relation = lem->relation;
	}
	else
	{
		relation = lem->relation;
		while (relation->next)
			relation = relation->next;
		relation->next = (t_relation *)malloc(sizeof(t_relation));
		relation = relation->next;
	}
	relation->next = NULL;
	room = lem->room;
	while (room)
	{
		(room->num == i) ? relation->parent = room : 0;
		(room->num == j) ? relation->child = room : 0;
		room = room->next;
	}
}

void	algorithm_extra(t_lem_in *lem, t_room *room)
{
	int i;
	int j;

	while (room)
	{
		i = room->num;
		j = -1;
		while (++j < lem->size)
		{
			if (lem->link[i][j] == 1 || lem->link[j][i] == 1)
			{
				parent_add(lem, i, j);
				parent_add(lem, j, i);
				queue_add(lem, j);
				lem->link[i][j] = 2;
				lem->link[j][i] = 2;
			}
		}
		room = queue_rem(lem);
	}
}

void	algorithm(t_lem_in *lem)
{
	t_room	*room;
	t_room	*end;

	if (!lem->link)
		error("No links");
	if (lem->start == -1 || lem->end == -1)
		error("No start or end");
	lem->queue = NULL;
	lem->ways = NULL;
	lem->relation = NULL;
	room = lem->room;
	while (room->num != lem->start)
		room = room->next;
	queue_add(lem, lem->start);
	algorithm_extra(lem, room);
	end = lem->room;
	while (end->num != lem->end)
		end = end->next;
	add_ways(lem, end);
	if (!lem->ways || !lem->ways->way || lem->ways->way->next == NULL)
		error("No possible solution");
	ants_way(lem);
}
