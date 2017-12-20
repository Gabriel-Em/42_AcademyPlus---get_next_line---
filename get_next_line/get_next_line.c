/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpop <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:03:55 by gpop              #+#    #+#             */
/*   Updated: 2017/12/21 01:09:30 by gpop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_line_length(t_chunk **chunks, int *treated_return,
	t_chunk **l_chunk)
{
	int		len;
	int		i;
	t_chunk	*chunk;

	chunk = *chunks;
	len = 0;
	while (chunk)
	{
		i = 0;
		while (i < chunk->len && chunk->str[i] != '\n')
		{
			len++;
			i++;
		}
		if (chunk != *chunks && i == 0)
			*treated_return = 0;
		*l_chunk = chunk;
		if (i != chunk->len || chunk->has_eof)
			return (len);
		else
			chunk = chunk->next;
	}
	l_chunk = NULL;
	return (-1);
}

static t_chunk	*add_chunk(t_chunk **chunks, char *str, int len, int has_eof)
{
	t_chunk *tmp;
	t_chunk *new_chunk;

	new_chunk = (t_chunk*)malloc(sizeof(t_chunk));
	new_chunk->str = str;
	new_chunk->len = len;
	new_chunk->has_eof = has_eof;
	new_chunk->next = NULL;
	if (*chunks == NULL)
	{
		*chunks = new_chunk;
	}
	else
	{
		tmp = *chunks;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_chunk;
	}
	return (new_chunk);
}

static int		look_through(int fd, t_chunk **chunks)
{
	t_lt_tools	lt;

	lt.found = 0;
	lt.ret = 23;
	lt.chunk = *chunks;
	while (!lt.found && lt.ret)
	{
		lt.buf = ft_strnew(BUFF_SIZE);
		lt.ret = read(fd, lt.buf, BUFF_SIZE);
		if (lt.ret > 0)
		{
			if (ft_strchr(lt.buf, '\n'))
				lt.found = 1;
			lt.chunk = add_chunk(chunks, lt.buf, lt.ret, 0);
		}
		else
		{
			ft_strdel(&(lt.buf));
			if (lt.ret == -1)
				return (0);
			if (lt.chunk != NULL)
				lt.chunk->has_eof = 1;
		}
	}
	return (1);
}

static void		chunks_to_line(t_chunk **chunks, char **line, int len)
{
	t_chunk *chunk;

	*line = ft_strnew(len);
	while (len >= 0 && *chunks)
		if (len >= (*chunks)->len)
		{
			ft_strncat(*line, (*chunks)->str, (*chunks)->len);
			len -= (*chunks)->len;
			if (len == 0)
				len = -1;
			ft_strdel(&((*chunks)->str));
			chunk = *chunks;
			*chunks = (*chunks)->next;
			free(chunk);
		}
		else
		{
			ft_strncat(*line, (*chunks)->str, len);
			(*chunks)->str = ft_strshorten((*chunks)->str, len + 1,
			(*chunks)->len - len - 1);
			(*chunks)->len = (*chunks)->len - len - 1;
			len = -1;
		}
}

int				get_next_line(int const fd, char **line)
{
	static t_chunk	*chunks[MAX_FD];
	t_gnl_tools		gnl;

	if (fd < 0 || fd > 1023 || line == NULL)
		return (-1);
	gnl.l_cnk = NULL;
	gnl.tr_return = 1;
	gnl.len = get_line_length(&chunks[fd], &(gnl.tr_return), &(gnl.l_cnk));
	if (gnl.len == -1)
	{
		if (!look_through(fd, &chunks[fd]))
			return (-1);
		gnl.len = get_line_length(&chunks[fd], &(gnl.tr_return), &(gnl.l_cnk));
		if (gnl.len == -1)
			return (0);
	}
	if (!gnl.tr_return)
	{
		gnl.l_cnk->str = ft_strshorten(gnl.l_cnk->str, 1, gnl.l_cnk->len - 1);
		gnl.l_cnk->len = gnl.l_cnk->len - 1;
	}
	chunks_to_line(&chunks[fd], line, gnl.len);
	if (chunks[fd] != NULL)
		return (1);
	return (ft_strlen(*line) != 0);
}
