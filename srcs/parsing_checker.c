/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:05:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 15:49:53 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				check_name(char *name, t_farm *farm, int nb)
{
	int		i;

	i = 0;
	while (i < nb && farm->room[i].name)
	{
		if (ft_strcmp(name, farm->room[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int				check_coor(int x, int y, t_farm *farm, int nb)
{
	int i;

	i = 0;
	while (i < nb && farm->room[i].x && farm->room[i].y)
	{
		if (x == farm->room[i].x && y == farm->room[i].y)
			return (1);
		i++;
	}
	return (0);
}

int				check_valid_start_end(t_farm farm)
{
	if (farm.init_start == 2 && farm.init_end == 2)
		return (1);
	free_farm(&farm);
	return (-1);
}

int				invalid_farm(char *line, t_farm *farm)
{
	free_farm(farm);
	ft_printf("line error = %s\n", line); // to delete
	ft_printf("The farm is not valid!\n");
	if (line != NULL)
		ft_strdel(&line);
	return (-1);
}

int				valid_farm(t_farm *farm)
{
	free_farm(farm);
	return (0);
}
