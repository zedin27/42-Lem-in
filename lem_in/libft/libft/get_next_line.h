/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarthon <lbarthon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:16:22 by lbarthon          #+#    #+#             */
/*   Updated: 2019/01/15 11:34:15 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);

typedef struct		s_buff
{
	int				fd;
	char			*buff;
	struct s_buff	*next;
}					t_buff;

#endif
