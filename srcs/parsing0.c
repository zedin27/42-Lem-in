/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:52:28 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 15:41:51 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		init_value(t_farm *farm, char **tab, int i)
{
	farm->room[i].name = ft_strdup(tab[0]); // to free
	farm->room[i].x = ft_atoi(tab[1]);
	farm->room[i].y = ft_atoi(tab[2]);
	farm->room[i].ant = 0;
	farm->room[i].visited = 0;
	farm->room[i].weight = 0;
}

static int		give_value_farm(t_farm *farm, char **tab, int i)
{
	if (check_name(tab[0], farm, i) == 1
			|| check_coor(ft_atoi(tab[1]), ft_atoi(tab[2]), farm, i) == 1)
		return (-1);
	init_value(farm, tab, i);
	if (farm->init_start == 1)
	{
		farm->room[i].start = 1;
		farm->room[i].ant = farm->total;
		farm->init_start = 2;
		farm->room[i].visited = 1;
	}
	else
		farm->room[i].start = 0;
	if (farm->init_end == 1)
	{
		farm->room[i].end = 1;
		farm->init_end = 2;
	}
	else
		farm->room[i].end = 0;
	return (0);
}

int				is_room_info(char *str, t_farm *farm, int i)
{
	char	**tab;
	int		j;

	if (i == (*farm).size - 1)
		if (ft_realloc_room(*farm, i) == -1)
			return (-1);
	j = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[j] != NULL)
		j++;
	if (j == 3 && ft_atoi(tab[1]) >= 0 && ft_atoi(tab[2]) >= 0)
	{
		if (give_value_farm(farm, tab, i) == -1)
			return (-1);
		j = -1;
		while (tab[++j] != NULL)
			free(tab[j]);
		free(tab);
		return (1);
	}
	j = -1;
	while (tab[++j] != NULL)
		free(tab[j]);
	free(tab);
	return (0);
}

int				is_comment(char *str, t_farm *farm)
{
	if (str[0] == '#' && str[1] == '#')
	{
		if (ft_strcmp(str, "##start") == 0 && farm->init_start == 0)
			farm->init_start = 1;
		else if (ft_strcmp(str, "##end") == 0 && farm->init_end == 0)
			farm->init_end = 1;
		else if ((ft_strcmp(str, "##start") == 0 && farm->init_start >= 1) ||
				(ft_strcmp(str, "##end") == 0 && farm->init_end >= 1))
			return (-1);
		return (1);
	}
	return (0);
}
