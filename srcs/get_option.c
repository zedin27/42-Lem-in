/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:16:19 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/22 17:32:01 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	get_option(int ac, char **av, t_farm farm)
{
	farm.optionv = 0;
	farm.optionc = 0;
	if (ac > 3)
		return ;
	if (av[1] && av[2])
	{
		if (ft_strcmp(av[1], "-v") == 0 || ft_strcmp(av[2], "-v") == 0)
			farm.optionv = 1;
		if (ft_strcmp(av[1], "-c") == 0 || ft_strcmp(av[2], "-c") == 0)
			farm.optionc = 1;
	}
}
