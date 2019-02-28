/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:09:26 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 11:33:32 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#include <stdlib.h> //to delete

static int		invalid_farm(char *line)
{
	ft_printf("The farm is not valid!\n");
	if (line != NULL)
		ft_strdel(&line);
	return (-1);
}

static void		free_farm(t_farm farm)
{
	int i;

	i = 0;
	while (i < farm.nb_room)
	{
		free(farm.room[i].name);
		free(farm.link[i]);
		i++;
	}
	free(farm.link);
	free(farm.room);
}

static int		check_valid(t_farm farm)
{
	//ft_printf("start = %d et end = %d\n", farm.init_start, farm.init_end);
	if (farm.init_start == 2 && farm.init_end == 2)
		return (1);
	free_farm(farm);
	return (-1);
}

static void		init_farm(t_farm *farm, int *i, char **line)
{
	*i = 0;
	*line = NULL;
	farm->init_total = 0;
	farm->init_start = 0;
	farm->init_end = 0;
	farm->size = SIZE;
	farm->create_matrix = 0;
	farm->nb_room = 0;
	farm->count = 0;
}

int		main(int ac, char **av)
{
	t_farm	farm;
	char	*line;
	int		i;

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
			create_link_matrix(&farm, line);
		}
		else if (is_comment(line, &farm) != 1)
		{
			ft_printf("line error = %s\n", line);
			return (invalid_farm(line));
		}
		ft_strdel(&line);
	}
	if (check_valid(farm) == -1)
	{
		ft_printf("test");
		return (invalid_farm(NULL));
	}
	ft_printf("\n");
	farm.init_total = 0;
	while (bfs(&farm) == 1)
		i++;
	farm.init_total = i;
		//return (invalid_farm(NULL));
	// moving and max flow algo and display function
	//system("leaks lem_in"); // to delete
	free_farm(farm);
	ft_printf("This is a valid farm, well done pal!\n"); // testing // to delete
	return (0);
}
