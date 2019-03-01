/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 22:31:09 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 16:03:41 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# define SIZE 256

/*
** Data structures to stock the information
*/

typedef struct		s_room
{
	char	*name;
	int		index;
	int		ant;
	int		x;
	int		y;
	int		start;
	int		end;
	int		visited;
	int		weight;
}					t_room;

typedef struct		s_path
{
	int		*path;
	int		weight;
}					t_path;

typedef struct		s_farm
{
	t_room	*room;
	t_path	*path;
	int		**link;
	int		total;
	int		nb_room;
	int		nb_path;
	int		init_start;
	int		init_end;
	int		init_total;
	int		create_matrix;
	int		size;
	int		optionv;
	int		optionc;
	int		first;
	int		last;
	int		count;
	int		path_max;
}					t_farm;

/*
** Functions to get the informations from the stdinput
*/

int					is_nb_info(char *str);
int					is_room_info(char *str, t_farm *farm, int i);
int					check_coor(int x, int y, t_farm *farm, int nb);
int					ft_realloc_room(t_farm farm, int old_nb_room);
int					is_link_info(char *str, t_farm *farm);
int					create_link_matrix(t_farm *farm, char *line);
void				fill_the_matrix(t_farm *farm);
int					is_comment(char *str, t_farm *farm);
void				free_tab(char **tab);
int					check_name(char *name, t_farm *farm, int nb);
void				get_option(int ac, char **av, t_farm farm);
int					check_valid_start_end(t_farm farm);
void				free_farm(t_farm *farm);
void				free_tab(char **tab);
int					invalid_farm(char *line, t_farm *farm);
int					valid_farm(t_farm *farm);

/*
** Algorithms to find the shortests paths and manage the flow
*/

int					bfs(t_farm *farm);
void				enqueue(int vertex, int **queue, t_farm *farm);
int					dequeue(int **queue, t_farm *farm);
int					is_empty(t_farm *farm);
void				put_vertex_visited(int ind, t_farm *farm);
int					check_enqueue(int *queue, int i, t_farm *farm);

/*
** Functions to move the ants, to check the room and to display
*/

int					move_ant(t_room *src, t_room *dst);
int					check_room_free(t_room *room);
int					graph_finished(t_farm *farm);

#endif
