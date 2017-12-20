/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpop <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:03:33 by gpop              #+#    #+#             */
/*   Updated: 2017/12/21 00:14:09 by gpop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFF_SIZE 2409
# define MAX_FD 1024

typedef	struct		s_chunk
{
	char			*str;
	int				len;
	int				has_eof;
	struct s_chunk	*next;
}					t_chunk;

typedef struct		s_lt_tools
{
	char			*buf;
	int				ret;
	int				found;
	t_chunk			*chunk;
}					t_lt_tools;

typedef struct		s_gnl_tools
{
	int				len;
	int				tr_return;
	t_chunk			*l_cnk;
}					t_gnl_tools;

int					get_next_line(int const fd, char **line);

#endif
