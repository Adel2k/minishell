/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:59 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/07 13:15:00 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenisation(char **args, int count)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(count * sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tokens[i].str = args[i];
		tokens[i].type = find_type(args[i], tokens, i);
		i++;
	}
	return (tokens);
}

char	*find_type(char *str, t_token *tokens, int i)
{
	if (!ft_strcmp(str, "|"))
		return ("pipe");
	if (!ft_strcmp(str, "<"))
		return ("in_redir");
	if (!ft_strcmp(str, ">"))
		return ("out_redir");
	if (!ft_strcmp(str, "<<"))
		return ("heredoc");
	if (!ft_strcmp(str, ">>"))
		return ("append_redir");
	if (i > 0)
	{
		if (!ft_strcmp(tokens[i - 1].type, "in_redir"))
			return ("in_file");
		if (!ft_strcmp(tokens[i - 1].type, "out_redir"))
			return ("out_file");
		if (!ft_strcmp(tokens[i - 1].type, "append_redir"))
			return ("append_file");
		if (!ft_strcmp(tokens[i - 1].type, "heredoc"))
			return ("limiter");
	}
	return ("word");
}

void	err(t_token *tokens, int count, char *message)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(tokens[j].str);
		j++;
	}
	free(tokens);
	exit(printf("%s", message));
}

void	check_for_invalid_input(t_token *tokens, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (!ft_strcmp(tokens[i].type, "in_redir") && (i + 1 == count
				|| (i < count && ft_strcmp(tokens[i + 1].type, "in_file"))))
			err(tokens, count, "there is in_redir but no in_file\n");
		if (!ft_strcmp(tokens[i].type, "out_redir") && (i + 1 == count
				|| (i < count && ft_strcmp(tokens[i + 1].type, "out_file"))))
			err(tokens, count, "there is out_redir but no out_file\n");
		if (!ft_strcmp(tokens[i].type, "append_redir") && (i + 1 == count
				|| (i < count && ft_strcmp(tokens[i + 1].type, "append_file"))))
			err(tokens, count, "there is append_redir but no append_file\n");
		if (!ft_strcmp(tokens[i].type, "heredoc") && (i + 1 == count
				|| (i < count && ft_strcmp(tokens[i + 1].type, "limiter"))))
			err(tokens, count, "there is heredoc but no limiter\n");
		if (!ft_strcmp(tokens[i].type, "pipe") && (i + 1 == count
				|| i == 0 || !ft_strcmp(tokens[i + 1].type, "word")))
			err(tokens, count, "there is pipe w/out commands\n");
	}
}

void	remove_quotes(t_token *tokens, int count)
{
	int	i;
	int	flag;
	int j;


	i = 0;
	while (i < count)
	{
		j = 0;
		flag = 0;
		while (tokens[i].str[j])
		{
			if (tokens[i].str[j] == 39)
			{
				flag = 1;
				break ;
			}
			if (tokens[i].str[j] == '"')
			{
				flag = 2;
				break ;
			}
		}
		i++;
	}
}