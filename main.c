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

void print_tokens(t_token *tokens, int tokens_count)
{
	int j;
	
	j = 0;
	while (j < tokens_count)
	{
		printf("str: %s, type: %s\n", tokens[j].str, tokens[j].type);
		j++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;
	char	**strs;
	int		tokens_count;
	(void) argc;
	(void) argv;

	while (1)
	{
		input = readline("\033[0;034m PONCHIKI_MINISHELL:  \033[0;000m");
		add_history(input);
		tokens_count = ft_words_count(input, ' ');
		strs = ft_split(input);
		if (!input)
			exit(printf("No input received.\n"));
		tokens = tokenisation(strs, tokens_count);
		free(strs);
		free(input);
		check_for_invalid_input(tokens, tokens_count);
		dollar_sign(tokens, tokens_count, env);
		print_tokens(tokens, tokens_count);
	}
	return (0);
}
