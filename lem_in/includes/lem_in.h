/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 22:31:09 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/25 22:26:26 by tcherret         ###   ########.fr       */
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
}					t_room;

typedef struct		s_farm
{
	t_room	*room;
	int		**link;
	int		total;
	int		nb_room;
	int		init_start;
	int		init_end;
	int		init_total;
	int		order;
	int		create_matrix;
	int		size;
	int		optionv;
	int		optionc;
	int		first;
	int		last;
}					t_farm;


/*
** Functions to get the informations from the stdinput
*/

int					is_nb_info(char *str);
int					is_room_info(char *str, t_farm *farm, int i);
int					ft_realloc_room(t_farm farm, int old_nb_room);
int					is_link_info(char *str, t_farm *farm);
int					create_link_matrix(t_farm *farm, char *line);
void				fill_the_matrix(t_farm *farm);
int					is_comment(char *str, t_farm *farm);
int					is_comment1(char *str);
void				free_tab(char **tab);
int					check_name(char *name, t_farm *farm, int nb);
void				get_option(int ac, char **av, t_farm farm);

/*
** Algorithms to find the shortests paths and manage the flow
*/

int					bfs(t_farm *farm);

/*
** Functions to move the ants and to check the room and the link
*/

#endif 
