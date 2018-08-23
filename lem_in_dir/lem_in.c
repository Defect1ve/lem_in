/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:46:48 by ikotvits          #+#    #+#             */
/*   Updated: 2018/07/19 12:46:49 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	link_check(char *line, t_lem_in *lem, int *i, int *j)
{
	char	*start;
	char	*end;
	char	*delim;
	t_room	*room;

	if (!(delim = ft_strchr(line, '-')))
		algorithm(lem);
	start = ft_strsub(line, 0, delim - line);
	end = ft_strsub(line, delim - line + 1, ft_strlen(delim + 1));
	room = lem->room;
	while (room)
	{
		if (ft_strequ(start, room->name))
			*i = room->num;
		if (ft_strequ(end, room->name))
			*j = room->num;
		room = room->next;
	}
	ft_strdel(&start);
	ft_strdel(&end);
	if (*i == -1 || *j == -1 || *i == *j)
		algorithm(lem);
}

void	get_link(t_lem_in *lem, char *line)
{
	int	i;
	int	j;

	if (!(lem->link))
	{
		lem->link = (char **)malloc(sizeof(char *) * lem->size);
		i = -1;
		while (++i < lem->size)
		{
			lem->link[i] = (char *)malloc(sizeof(char) * lem->size);
			j = -1;
			while (++j < lem->size)
				lem->link[i][j] = 0;
		}
	}
	i = -1;
	j = -1;
	link_check(line, lem, &i, &j);
	lem->link[i][j] = 1;
	lem->link[j][i] = 1;
}

void	get_line(t_lem_in *lem, char *line)
{
	int			i;

	if (line[0] && line[0] == '#')
		(line[1] && line[1] == '#') ? get_command(lem, line) : 0;
	else if (lem->ants == -1)
	{
		i = -1;
		(ft_strlen(line) == 0) ? error("Empty file") : 0;
		((lem->ants = ft_atoi(line)) < 1) ?
		error("Invalid number of ants =(") : 0;
		while (line[++i])
			(line[i] > '9' || line[i] < '0') ?
			error("Invalid number of ants =(") : 0;
	}
	else if (strchr(line, ' ') && !lem->link)
		get_room(lem, line);
	else if (strchr(line, ' '))
		algorithm(lem);
	else if (lem->position == '\0')
		get_link(lem, line);
	else
		error("Invalid usage of start/end");
}

int		main(void)
{
	t_lem_in	*lem;
	char		*line;

	lem = (t_lem_in *)malloc(sizeof(t_lem_in));
	lem->room = NULL;
	lem->link = NULL;
	lem->size = 0;
	lem->ants = -1;
	lem->start = -1;
	lem->end = -1;
	lem->position = '\0';
	while (get_next_line(0, &line))
	{
		get_line(lem, line);
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	algorithm(lem);
	return (0);
}
