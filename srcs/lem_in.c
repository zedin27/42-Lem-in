/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:09:26 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 13:39:14 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#include <stdlib.h> //to delete

static int		invalid_farm(char *line)
{
	//free_farm(farm);
	ft_printf("line error = %s\n", line); // to delete
	ft_printf("The farm is not valid!\n");
	if (line != NULL)
		ft_strdel(&line);
	return (-1);
}

static void		free_farm(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->nb_room)
	{
		free(farm->room[i].name);
		free(farm->link[i]);
		i++;
	}
	i = 0;
	while (i < farm->nb_path)
	{
		free(farm->path[i].path);
		i++;
	}
	free(farm->path);
	free(farm->link);
	free(farm->room);
}

static int		check_valid(t_farm farm)
{
	if (farm.init_start == 2 && farm.init_end == 2)
		return (1);
	free_farm(&farm);
	return (-1);
}

static void		init_farm(t_farm *farm, int *i, char **line)
{
	*i = 0;
	*line = NULL;
	farm->room = NULL;
	farm->path = NULL;
	farm->init_total = 0;
	farm->init_start = 0;
	farm->init_end = 0;
	farm->size = SIZE;
	farm->create_matrix = 0;
	farm->nb_room = 0;
	farm->nb_path = 0;
	farm->count = 0;
}

int		main(int ac, char **av)
{
	t_farm	farm;
	char	*line;
	int		i;
	int		j;

	init_farm(&farm, &i, &line);
	if (!(farm.room = malloc(sizeof(t_room) * SIZE)))
		return (-1);
	if (ac > 1)
		get_option(ac, av, farm);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (is_nb_info(line) == 1 && ft_atoi(line) > 0 && farm.init_total == 0)
		{
			farm.total = ft_atoi(line);
			farm.init_total = 1;
		}
		else if (is_room_info(line, &farm, i) == 1 && farm.init_total == 1)
		{
			farm.room[i].index = i;
			i++;
			farm.nb_room++;
		}
		else if (is_link_info(line, &farm) == 1)
		{
			if (farm.create_matrix == 0)
			{
				if (!(farm.link = malloc(sizeof(int*) * farm.nb_room)))
					return (-1);
				i = -1;
				while (++i < farm.nb_room)
					if (!(farm.link[i] = malloc(sizeof(int) * farm.nb_room)))
						return (-1);
				fill_the_matrix(&farm);
				farm.create_matrix = 1;
			}
			if (create_link_matrix(&farm, line) == -1)
				return (invalid_farm(NULL));
		}
		else if (is_comment(line, &farm) != 1)
			return (invalid_farm(line));
		ft_strdel(&line);
	}
	if (check_valid(farm) == -1)
		return (invalid_farm(NULL));
	ft_printf("\n");
	while (farm.room[farm.count].start != 1)
		farm.count++;
	i = -1;
	j = 0;
	while (++i < farm.nb_room)
		if (farm.link[farm.count][i] == 1)
			j++;
	if (!(farm.path = malloc(sizeof(t_path) * j)))
		return (-1);
	while (bfs(&farm) == 1)
		farm.nb_path++;
	if (farm.nb_path == 0)
		return (invalid_farm(NULL));
	//moving and max flow algo and display function
	//system("leaks lem_in"); // to delete
	free_farm(&farm);
	return (0);
}
