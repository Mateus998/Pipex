/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_px.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:40:50 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/23 17:41:58 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static t_gnl	*get_node(t_gnl **head, int fd)
{
	t_gnl	*node;

	node = *head;
	while (node && node->fd != fd)
		node = node->next;
	if (!node)
	{
		node = malloc(sizeof(t_gnl));
		if (!node)
			return (NULL);
		node->fd = fd;
		node->content = NULL;
		node->next = *head;
		*head = node;
	}
	return (node);
}

static int	read_to_buffer(int fd, char **content)
{
	char	*read_buff;
	int		file_status;

	if (ft_strlchr_gnl(*content, '\n') >= 0)
		return (1);
	read_buff = malloc(BUFFER_SIZE + 1);
	if (!read_buff)
		return (-1);
	file_status = 1;
	while (file_status > 0 && ft_strlchr_gnl(*content, '\n') < 0)
	{
		file_status = read(fd, read_buff, BUFFER_SIZE);
		if (file_status > 0)
		{
			read_buff[file_status] = '\0';
			file_status = ft_strjoin_gnl(content, read_buff);
		}
	}
	free(read_buff);
	return (file_status);
}

static char	*free_node(t_gnl **list, t_gnl *delnode)
{
	t_gnl	*node;

	if (!list || !delnode || !(*list))
		return (NULL);
	if (delnode == *list)
		*list = delnode->next;
	else
	{
		node = *list;
		while (node && node->next != delnode)
			node = node->next;
		if (node)
			node->next = delnode->next;
	}
	if (delnode->content)
		free(delnode->content);
	free(delnode);
	return (NULL);
}

static int	extract_line(char **line, char *content, int file_status)
{
	int	line_size;

	if (!content || !line || file_status < 0)
		return (file_status);
	if (file_status == 0 && !content)
		return (file_status);
	line_size = ft_strlchr_gnl(content, '\n') + 1;
	if (line_size > 0)
		*line = ft_substr_gnl(content, 0, line_size);
	else
		*line = ft_strdup_gnl(content);
	if (!(*line))
		return (-1);
	return (1);
}

char	*get_next_line_px(int fd, char *limiter)
{
	static t_gnl	*head;
	t_gnl			*node;
	char			*line;
	int				file_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&head, fd);
	if (!node)
		return (NULL);
	file_status = read_to_buffer(fd, &(node->content));
	line = NULL;
	file_status = extract_line(&line, node->content, file_status);
	file_status = update_content(&(node->content), file_status);
	if (file_status < 0)
		return (free_node(&head, node));
	if (file_status == 0)
		free_node(&head, node);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		free_node(&head, node);
	return (line);
}
