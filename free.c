/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:07 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/09 15:53:09 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens, char *s, int i)
{
	free(tokens[i].str);
	free(s);
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
