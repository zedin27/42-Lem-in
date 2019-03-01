/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:54:59 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 14:08:07 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				is_nb_info(char *str)
{
	char	**tab;
	int		j;

	j = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[j] != NULL)
		j++;
	if (j == 1 && ft_atoi(tab[0]) > 0)
	{
		free_tab(tab);
		return (1);
	}
	free_tab(tab);
	return (0);
}

int				is_link_info(char *str, t_farm *farm)
{
	char	**tab;
	int		j;

	tab = ft_strsplit(str, '-');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] != NULL)
	{
		j = -1;
		while (tab[++j] != NULL)
			free(tab[j]);
		free(tab);
		return (-1);
	}
	j = -1;
	if (check_name(tab[0], farm, farm->nb_room) == 1
			&& check_name(tab[1], farm, farm->nb_room) == 1)
	{
		while (tab[++j] != NULL)
			free(tab[j]);
		free(tab);
		return (1);
	}
	while (tab[++j] != NULL)
		free(tab[j]);
	free(tab);
	return (0);
}

void			fill_the_matrix(t_farm *farm)
{
	int i;
	int j;

	i = 0;
	while (i < farm->nb_room)
	{
		j = 0;
		while (j < farm->nb_room)
		{
			farm->link[i][j] = 0;
			j++;
		}
		i++;
	}
}

int				create_link_matrix(t_farm *farm, char *line)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	tab = ft_strsplit(line, '-');
	k = 0;
	while (k < farm->nb_room && ft_strcmp(farm->room[k].name, tab[0]) != 0)
		k++;
	i = farm->room[k].index;
	k = 0;
	while (k < farm->nb_room && ft_strcmp(farm->room[k].name, tab[1]) != 0)
		k++;
	j = farm->room[k].index;
	if (i == j || farm->link[i][j] == 1)
		return (-1);
	farm->link[i][j] = 1;
	farm->link[j][i] = 1;
	k = -1;
	while (tab[++k] != NULL)
		free(tab[k]);
	free(tab);
	return (0);
}
