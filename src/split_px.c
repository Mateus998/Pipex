/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_px.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:48:26 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/24 18:34:29 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char switch_c(char c, char temp)
{
    if (c == '\'')
        return (temp);
    return ('\'');
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;
    char temp;

	words = 0;
	i = 0;
    temp = c;
	while (s[i])
	{
        if (s[i] == '\'')
            c = switch_c(c, temp);
		if (s[i] != c && s[i])
		{
			words++;
			while (s[i] && s[i] != c && s[i] != '\'')
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	**free_split(char **split, size_t j)
{
	while (j > 0)
	{
		j--;
		free(split[j]);
	}
	free(split);
	return (NULL);
}

static char	*word(char const *s, char c, size_t i)
{
	size_t	word;
	char	*pword;
	size_t	start;

	word = 0;
	start = i;
	while (s[i] && s[i] != c)
	{
		word++;
		i++;
	}
	pword = (char *)malloc((word + 1) * sizeof(char));
	if (pword == NULL)
		return (NULL);
	ft_strlcpy(pword, &s[start], word + 1);
	return (pword);
}

static char	**split_fill(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = word(s, c, i);
			if (split[j] == NULL)
				return (free_split(split, j));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}

char	**split_px(char const *s, char c)
{
	char	**split;

	if (s != NULL)
	{
		split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
		if (split == NULL)
			return (NULL);
		split = split_fill(split, s, c);
	}
	else
	{
		return (NULL);
	}
	return (split);
}

int main()
{
    printf("%i words\n", count_words("grep 'line 1'", ' '));
}