/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:09:26 by tcherret          #+#    #+#             */
/*   Updated: 2019/03/01 11:05:04 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		find_path_max(t_farm *farm)
{
	int i;

	ft_printf("\n");
	while (farm->room[farm->count].start != 1)
		farm->count++;
	i = -1;
	while (++i < farm->nb_room)
		if (farm->link[farm->count][i] == 1)
			farm->path_max++;
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
	farm->path_max = 0;
	if (!(farm->room = malloc(sizeof(t_room) * SIZE)))
		return ;
}

static int		initialization_matrix(t_farm *farm)
{
	int j;

	j = -1;
	if (!(farm->link = malloc(sizeof(int*) * farm->nb_room)))
		return (-1);
	while (++j < farm->nb_room)
		if (!(farm->link[j] = malloc(sizeof(int) * farm->nb_room)))
			return (-1);
	fill_the_matrix(farm);
	farm->create_matrix = 1;
	return (0);
}

static int		do_the_work(t_farm *farm, int *i, char **line)
{
	ft_printf("%s\n", *line);
	if (is_nb_info(*line) == 1 && ft_atoi(*line) > 0 && farm->init_total == 0)
	{
		farm->total = ft_atoi(*line);
		farm->init_total = 1;
	}
	else if (is_room_info(*line, farm, *i) == 1 && farm->init_total == 1)
	{
		farm->room[*i].index = *i;
		(*i)++;
		farm->nb_room++;
	}
	else if (is_link_info(*line, farm) == 1)
	{
		if (farm->create_matrix == 0)
			if (initialization_matrix(farm) == -1)
				return (-1);
		if (create_link_matrix(farm, *line) == -1)
			return (invalid_farm(NULL, farm));
	}
	else if (is_comment(*line, farm) != 1)
		return (invalid_farm(*line, farm));
	ft_strdel(line);
	return (0);
}

int				main(int ac, char **av)
{
	t_farm	farm;
	char	*line;
	int		i;

	init_farm(&farm, &i, &line);
	if (ac > 1)
		get_option(ac, av, farm);
	while (get_next_line(0, &line) > 0)
		if (do_the_work(&farm, &i, &line) == -1)
			return (invalid_farm(NULL, &farm));
	if (check_valid_start_end(farm) == -1)
		return (invalid_farm(NULL, &farm));
	find_path_max(&farm);
	if (!(farm.path = malloc(sizeof(t_path) * farm.path_max)))
		return (-1);
	while (bfs(&farm) == 1)
		farm.nb_path++;
	if (farm.nb_path == 0)
		return (invalid_farm(NULL, &farm));
	//moving_ant(&farm); //moving ants and display function
	//system("leaks lem_in"); // to delete
	return (valid_farm(&farm));
}
