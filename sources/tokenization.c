/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:59 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/24 18:08:48 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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

int	check_next(t_token *tokens, int i)
{
	if (!ft_strcmp(tokens[i].type, "heredoc")
		&& !ft_strcmp(tokens[i + 1].type, "heredoc"))
	{
		write(2, "syntax error near unexpected token `<\'\n", 39);
		return (-1);
	}
	if ((!ft_strcmp(tokens[i].type, "in_redir")
			&& ft_strcmp(tokens[i + 1].type, "in_file"))
		|| (!ft_strcmp(tokens[i].type, "out_redir")
			&& ft_strcmp(tokens[i + 1].type, "out_file"))
		|| (!ft_strcmp(tokens[i].type, "append_redir")
			&& ft_strcmp(tokens[i + 1].type, "append_file"))
		|| (!ft_strcmp(tokens[i].type, "heredoc")
			&& ft_strcmp(tokens[i + 1].type, "limiter")
			&& ft_strcmp(tokens[i + 1].type, "inredir")))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, tokens[i + 1].str, ft_strlen(tokens[i + 1].str));
		write(2, "\'\n", 2);
		g_exit_status = 2;
		return (-1);
	}
	return (1);
}

int	check_for_invalid_input(t_token *tokens, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if ((i + 1 == count) && (!ft_strcmp(tokens[i].type, "in_redir")
				|| !ft_strcmp(tokens[i].type, "out_redir")
				|| !ft_strcmp(tokens[i].type, "append_redir")
				|| !ft_strcmp(tokens[i].type, "heredoc")))
		{
			write(2, "syntax error near unexpected token `newline\'\n", 45);
			g_exit_status = 2;
			return (-1);
		}
		if (check_next(tokens, i) < 0)
		{
			g_exit_status = 2;
			return (-1);
		}
		if (!ft_strcmp(tokens[i].type, "pipe") && (i + 1 == count || i == 0))
		{
			write(2, "syntax error near unexpected token `|\'\n", 40);
			g_exit_status = 2;
			return (-1);
		}
	}
	return (1);
}
