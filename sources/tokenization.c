/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:59 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/25 18:27:23 by hrigrigo         ###   ########.fr       */
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
		err_message("syntax error near unexpected token `<\'\n", "", "");
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
		err_message("syntax error near unexpected token `", tokens[i + 1].str, "\'\n");
		g_exit_status = 2;
		return (-1);
	}
	return (1);
}

int	if_invalid_input(t_token *tokens, int count, int i)
{
	while (++i < count)
	{
		if ((i + 1 == count) && (!ft_strcmp(tokens[i].type, "in_redir")
				|| !ft_strcmp(tokens[i].type, "out_redir")
				|| !ft_strcmp(tokens[i].type, "append_redir")
				|| !ft_strcmp(tokens[i].type, "heredoc")))
		{
			err_message("syntax error near unexpected token `newline\'\n", "", "");
			g_exit_status = 2;
			return (-1);
		}
		if (check_next(tokens, i) < 0)
		{
			g_exit_status = 2;
			return (-1);
		}
		if (!ft_strcmp(tokens[i].type, "pipe") && (i + 1 == count || i == 0 || ft_strcmp(tokens[i + 1].type, "pipe") == 0))
		{
			err_message("syntax error near unexpected token `|\'\n", "", "");
			g_exit_status = 2;
			return (-1);
		}
	}
	return (1);
}
