/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:07 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 03:35:13 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens, int count)
{
	int	j;

	if (!tokens)
		return ;
	j = 0;
	while (j < count)
	{
		free(tokens[j].str);
		j++;
	}
	free(tokens);
}

void	free_cmd(char **command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

void	free_dirs(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell -> cmd_dirs[i])
	{
		free(minishell->cmd_dirs[i]);
		i++;
	}
	free(minishell->cmd_dirs);
}
