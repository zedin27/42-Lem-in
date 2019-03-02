/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:18:34 by ayguillo          #+#    #+#             */
/*   Updated: 2019/01/09 17:29:28 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static int	check(long res, long neg)
{
	if ((res > 2147483647 && neg == 1) || (res > 2147483648 && neg == -1))
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	long	res;
	int		i;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + ((str[i] - '0'));
		i++;
	}
	if (check(res, neg) == -1)
		exit(0);
	return (res * neg);
}
