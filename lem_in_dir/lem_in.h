/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:49:02 by ikotvits          #+#    #+#             */
/*   Updated: 2018/07/19 12:49:03 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

typedef struct			s_room
{
	char				*name;
	int					num;
	int					x;
	int					y;
	int					ant;
	short				visited;
	struct s_room		*next;
}						t_room;

typedef	struct			s_queue
{
	t_room				*room;
	struct s_queue		*next;
}						t_queue;

typedef	struct			s_ways
{
	t_queue				*way;
	int					len;
	struct s_ways		*next;
}						t_ways;

typedef struct			s_relation
{
	t_room				*parent;
	t_room				*child;
	struct s_relation	*next;
}						t_relation;

typedef struct			s_input
{
	char				*str;
	struct s_input		*next;
}						t_input;

typedef	struct			s_lem_in
{
	t_room				*room;
	t_input				*input;
	t_queue				*queue;
	t_relation			*relation;
	t_ways				*ways;
	int					start;
	int					end;
	char				**link;
	int					size;
	int					ants;
	char				color;
	char				way;
	char				position;
}						t_lem_in;

void					algorithm(t_lem_in *lem);
void					error(char *str);
void					ants_way(t_lem_in *lem);
void					get_command(t_lem_in *lem, char *line);
void					get_room(t_lem_in *lem, char *line);
void					add_ways(t_lem_in *lem, t_room *end);
void					queue_add(t_lem_in *lem, int j);
t_room					*queue_rem(t_lem_in *lem);
void					parent_add(t_lem_in *lem, int i, int j);
void					print_ways(t_lem_in *lem);
void					get_flags(t_lem_in *lem, int ac, char **av);

#endif
