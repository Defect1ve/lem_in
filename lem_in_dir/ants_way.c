/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:40:03 by ikotvits          #+#    #+#             */
/*   Updated: 2018/08/20 15:40:05 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ways_len(t_lem_in *lem)
{
	t_ways	*ways;
	t_queue *way;
	int		length;
	int		sum;

	ways = lem->ways;
	sum = 0;
	while (ways)
	{
		length = -1;
		way = ways->way;
		while (way)
		{
			length++;
			way = way->next;
		}
		ways->len = length;
		sum += length;
		ways = ways->next;
	}
	return (sum);
}

void	ants_way_extra(t_ways *ways, int steps, int *ant, t_lem_in *lem)
{
	t_queue	*way;

	ways = lem->ways;
	while (ways)
	{
		way = ways->way;
		while (way && way->next)
		{
			if (way->next->room->ant)
			{
				way->room->ant = way->next->room->ant;
				ft_printf("L%d-%s ", way->room->ant, way->room->name);
				way->next->room->ant = 0;
			}
			if (!way->next->next)
				break ;
			way = way->next;
		}
		while (ways->len <= steps && *ant <= lem->ants &&
		(way->room->ant == 0 || way->room->num == lem->end))
			ft_printf("L%d-%s ", (way->room->ant = (*ant)++), way->room->name);
		ways = ways->next;
	}
	ft_printf("\n");
	(way->room->num == lem->end) ? exit(0) : 0;
}

void	print_input(t_lem_in *lem)
{
	t_input	*in;

	in = lem->input;
	while (in)
	{
		ft_printf("%s\n", in->str);
		in = in->next;
	}
	ft_printf("\n");
}

void	ants_way(t_lem_in *lem)
{
	int		steps;
	int		length;
	int		c_ways;
	int		ant;
	t_ways	*ways;

	steps = 0;
	c_ways = 0;
	ant = 1;
	print_input(lem);
	(lem->way) ? print_ways(lem) : 0;
	ways = lem->ways;
	while (ways)
	{
		c_ways++;
		ways = ways->next;
	}
	length = ways_len(lem);
	steps = ((long)length + (long)lem->ants - 1) / (long)c_ways;
	if (lem->color)
		ft_printf("\e[38;5;%dm", lem->ants % 200 + 20);
	while (steps)
		ants_way_extra(ways, steps--, &ant, lem);
	exit(0);
}
