/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:58:47 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/26 13:01:16 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//caracteres antes de dejar de procesar la palabra del dolar, ejemplo: $hola/tmp
//solo $hola se debe procesar
int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

void	swap_word(char *word, char **s, char *init, int i)
{
	int		k;
	char	tmp[900];

	if (!strcmp("$", word) && init[1])
		word++;
	while ((*s)[++i] != *init)
		tmp[i] = (*s)[i];
	k = -1;
	while (word && word[++k])
	{
		if (word[k] == ' ')
			tmp[i++] = '^';
		else
			tmp[i++] = word[k];
	}
	init++;
	while (*init && is_valid_char(*init))
		init++;
	while (*init)
		tmp[i++] = *init++;
	tmp[i] = '\0';
	free(*s);
	*s = ft_strdup(tmp);
}

char	*get_word(char *sinit, t_hash *env)
{
	int		i;
	char	tmp[800];
	char	*key;
	char	*word;

	i = 1;
	while (sinit[i] != '\0' && is_valid_char(sinit[i]))
	{
		tmp[i - 1] = sinit[i];
		i++;
	}
	if (i == 1 || !strcmp(sinit, "$\""))
		return (ft_strdup("$"));
	tmp[i - 1] = '\0';
	key = extract_key(tmp);
	word = lookup_hash(env, key);
	free(key);
	if (word)
		return (word);
	return (ft_strdup(""));
}

void	manage_dolar(char **s, t_hash *env)
{
	int		i;
	char	*word;
	Stack	quoteStack;
	int		sn;
	int		dn;

	word = NULL;
	i = 0;
	initStack(&quoteStack);
	sn = 0;
	dn = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\\')
			i += 2;
		else if ((*s)[i] == '\'' && (isEmpty(&quoteStack)))
		{
			push(&quoteStack, '\'');
			sn++;
		}
		else if ((*s)[i] == '\'' && (!isEmpty(&quoteStack)) && peek(&quoteStack) != '\'')
		{
			if (sn == 0)
			{
				push(&quoteStack, '\'');
				sn++;
			}
			else if (sn == 1)
			{
				pop(&quoteStack);
				pop(&quoteStack);
				sn--;
				dn--;
			}
		}
		else if ((*s)[i] == '\'' && (!isEmpty(&quoteStack)) && peek(&quoteStack) == '\'')
		{
			pop(&quoteStack);
			sn--;
		}
		else if ((*s)[i] == '"' && (isEmpty(&quoteStack) || peek(&quoteStack) != '"'))
		{
			if (dn == 0)
			{	
				push(&quoteStack, '"');
				dn++;
			}
			else if (dn == 1)
			{
				pop(&quoteStack);
				pop(&quoteStack);
				dn--;
				sn--;
			}
		}
		else if ((*s)[i] == '"' && (!isEmpty(&quoteStack)) && peek(&quoteStack) == '"')
		{
			pop(&quoteStack);
			dn--;
		}
		if ((*s)[i] == '$' && (isEmpty(&quoteStack) || (peek(&quoteStack) == '"' && \
			((sn == 0 && dn == 0) || (sn == 0 && dn == 1))) || (peek(&quoteStack) == '\'' && sn == 1 && dn == 1)))
		{
			word = get_word((*s) + i, env);
			swap_word(word, s, (*s) + i, -1);
			if (!strcmp(word, "") || !strcmp(word, "$"))
				free(word);
		}
		if ((*s)[i] == '\0')
			break ;
		i++;
	}
}

void	expand_dolar(char **av, t_hash *env)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (strchr(av[i], '$'))
			manage_dolar(&av[i], env);
		i++;
	}
}
