/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:55:41 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 19:18:26 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**empty_array(void)
{
	char	**new;

	new = (char **)malloc(2 * sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup("");
	if (!new[0])
		return (free(new), NULL);
	new[1] = NULL;
	return (new);
}

int	empty_array_check(char *s)
{
	int		i;
	size_t	chr;

	i = 0;
	chr = 0;
	if (!*s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == ' ')
			chr++;
		i++;
	}
	if (chr == ft_strlen(s))
		return (1);
	return (0);
}
