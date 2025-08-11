/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:19:43 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/11 10:19:44 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	quote_check(char c)
{
	if (c == '\'')
		return (-1);
	return (1);
}

static int	count_words(char const *s)
{
	int	words;
	int	i;
	int	q;

	words = 0;
	i = 0;
	q = -1;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\'')
			q *= quote_check(s[i++]);
		else
		{
			words++;
			while (s[i] && (q != -1 || s[i] != ' '))
			{
				if (s[i++] == '\'')
					q *= -1;
			}
		}
	}
	return (words);
}

static int	count_char(char const *s, int *i)
{
	int	chrs;
	int	q;

	chrs = 0;
	q = -1;
	while (s[*i])
	{
		if (s[*i] == ' ' || s[*i] == '\'')
			q *= quote_check(s[(*i)++]);
		else
		{
			while (s[*i] && (q != -1 || s[*i] != ' '))
			{
				if (s[(*i)++] == '\'')
					q *= -1;
				else
					chrs++;
			}
			return (chrs);
		}
	}
	return (0);
}

static void	fill_str(char **str, char const *s, int *i)
{
	int	q;
	int	j;

	q = -1;
	j = 0;
	while (s[*i])
	{
		if (s[*i] == ' ' || s[*i] == '\'')
			q *= quote_check(s[(*i)++]);
		else
		{
			while (s[*i] && (q != -1 || s[*i] != ' '))
			{
				if (s[*i] == '\'')
					q *= -1;
				else
					(*str)[j++] = s[*i];
				(*i)++;
			}
			(*str)[j] = '\0';
			return ;
		}
	}
}

char	**px_split(char const *s)
{
	int		i;
	int		i1;
	int		i2;
	int		words;
	char	**split;

	words = count_words(s);
	split = (char **)malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i <= words)
		split[i++] = NULL;
	i = 0;
	i1 = 0;
	i2 = 0;
	while (words--)
	{
		split[i] = malloc((count_char(s, &i1) + 1) * sizeof(char));
		if (!split[i])
			return (free_array(split), NULL);
		fill_str(&split[i++], s, &i2);
	}
	return (split);
}
