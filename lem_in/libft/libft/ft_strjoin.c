/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:50:40 by tcherret          #+#    #+#             */
/*   Updated: 2019/01/15 14:38:01 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	size_t		len;
	char		*new;

	if (s1 == NULL | s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char *)malloc(sizeof(*new) * (len + 1))))
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	return (new);
}
