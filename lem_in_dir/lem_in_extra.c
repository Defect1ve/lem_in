/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:34:45 by ikotvits          #+#    #+#             */
/*   Updated: 2018/08/23 14:34:46 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_command(t_lem_in *lem, char *line)
{
	if (!ft_strcmp(line, "##start"))
	{
		if ((lem->start != -1 || lem->position != '\0') && !lem->link)
			error("Too much starts", lem);
		else if (lem->start != -1 || lem->position != '\0')
			algorithm(lem);
		lem->position = 's';
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if ((lem->end != -1 || lem->position != '\0') && !lem->link)
			error("Too much ends", lem);
		else if (lem->end != -1 || lem->position != '\0')
			algorithm(lem);
		lem->position = 'f';
	}
}

void	error(char *str, t_lem_in *lem)
{
	(lem->err) ? ft_printf("%s\n", str) : ft_printf("ERROR\n");
	exit(0);
}

void	room_check(char *line, t_room *room, t_lem_in *lem)
{
	int		spaces;
	t_room	*temp;

	spaces = 0;
	temp = lem->room;
	line = ft_strchr(line, ' ');
	while (*line)
	{
		(*line == ' ') ? spaces++ : 0;
		((*line < 48 || *line > 57) && *line != ' ' && ((*line != '-' &&
		*line != '+') || *(line - 1) != ' ')) ? error("Coord fail", lem) : 0;
		line++;
	}
	while (temp && temp != room)
	{
		if ((temp->x == room->x && temp->y == room->y)
		|| !(ft_strcmp(temp->name, room->name)))
			error("Invalid room", lem);
		temp = temp->next;
	}
	if (spaces != 2 || room->name[0] == 'L' ||
	room->name[0] == '#' || ft_strchr(room->name, '-'))
		error("Invalid room", lem);
	lem->size++;
}

void	get_room_extra(t_lem_in *lem, t_room *room, char *line)
{
	room->visited = 0;
	room->ant = 0;
	if (lem->position == 's' || lem->position == 'f')
	{
		if (lem->position == 's')
			lem->start = room->num;
		else if (lem->position == 'f')
			lem->end = room->num;
		lem->position = '\0';
	}
	if ((room->x == 0 && *(ft_strchr(line, ' ') + 1) != '0') ||
	(room->y == 0 && *(ft_strrchr(line, ' ') + 1) != '0') ||
	(room->x != 0 && *(ft_strchr(line, ' ') + 1) == '0') ||
	(room->y != 0 && *(ft_strrchr(line, ' ') + 1) == '0') ||
	ft_strchr(line, '-'))
		error("Invalid coord", lem);
}

void	get_room(t_lem_in *lem, char *line)
{
	t_room	*room;

	if (ft_strlen(line) == 0)
		error("Empty line!", lem);
	if (!(lem->room))
	{
		lem->room = (t_room *)malloc(sizeof(t_room));
		room = lem->room;
	}
	else
	{
		room = lem->room;
		while (room->next)
			room = room->next;
		room->next = (t_room *)malloc(sizeof(t_room));
		room = room->next;
	}
	room->next = NULL;
	room->name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	room->x = ft_atoi(ft_strchr(line, ' '));
	room->y = ft_atoi(ft_strrchr(line, ' '));
	room->num = lem->size;
	get_room_extra(lem, room, line);
	room_check(line, room, lem);
}
