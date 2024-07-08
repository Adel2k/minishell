/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/07 13:14:55 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;
	char	**strs;
	int		i;
	int		tokens_count;
	(void) argc;
	(void) argv;

	while (1)
	{
		input = readline("MINISHELL  ");
		add_history(input);
		tokens_count = ft_words_count(input, ' ');
		strs = ft_split(input);
		i = 0;
		while (strs[i])
		{
			printf("%s\n", strs[i]);
			i++;
		}
		if (input)
		{
			if (!strcmp(input, "prc"))
				break ;
			free(input);
		}
		else
			printf("No input received.\n");
		tokens = tokenisation(strs, tokens_count);
		free(strs);
		check_for_invalid_input(tokens, tokens_count);
		dollar_sign(tokens, tokens_count, env);
		int j = 0;
		while (j < tokens_count)
		{
			printf("str: %s, type: %s\n", tokens[j].str, tokens[j].type);
			j++;
		}
	}
	return (0);
}
