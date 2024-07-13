/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/13 12:49:03 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens, int tokens_count)
{
	int	j;

	j = 0;
	while (j < tokens_count)
	{
		printf("str: %s, type: %s\n", tokens[j].str, tokens[j].type);
		j++;
	}
}

char	*ft_strstr_alt(char *str, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (*to_find == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == 0)
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*s3;
	int		i;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (s1_size + s2_size + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i++] = '/';
	while (s2[i - s1_size - 1])
	{
		s3[i] = s2[i - s1_size - 1];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char **init_dirs(t_minishell *minishell)
{
	int		i;
	char	**dirs;

	i = 0;
	while (minishell -> env[i])
	{
		if (ft_strstr_alt(minishell -> env[i], "PATH="))
			break ;
		i++;
	}
	dirs = ft_split(minishell -> env[i] + 5, ':');
	if (!dirs)
		err(minishell->tokens, minishell->tokens_count, "split_err\n");
	return (dirs);
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
		input = readline("\033[0;034mPONCHIKI_MINISHELL:  \033[0;000m");
		add_history(input);
		tokens_count = ft_words_count_tokens(input, ' ');
		strs = ft_split_tokens(input);
		if (!input)
			exit(printf("No input received.\n"));
		tokens = tokenisation(strs, tokens_count);
		free(strs);
		free(input);
		check_for_invalid_input(tokens, tokens_count);
		dollar_sign(tokens, tokens_count, env);
		remove_quotes(tokens, tokens_count);
	// print_tokens(tokens, tokens_count);
		t_minishell *minishell;

		minishell = malloc(sizeof(t_minishell));
		if (!minishell)
			return (1);
		minishell->tokens = tokens;
		minishell->tokens_count = tokens_count;
		minishell->env = env;
		// t_env *envm = init_env(minishell);
		// while (envm)
		// {
		// 	printf("key: %s     value: %s \n", envm->key, envm->value);
		// 	envm = envm->next;
		// }
		minishell->cmd_dirs = init_dirs(minishell);
		minishell->pipe_count = pipe_count(minishell);
		minishell->pipe_index = 0;
		minishell->index = 0;
		init_fd(minishell);
		builtin(minishell);
		while (minishell->index < minishell->tokens_count)
		{
			minishell->infile = 0;
			minishell->outfile = 1;
			minishell->if_here_doc = 0;
			run_commands(minishell);
			if (minishell->index < minishell->tokens_count && !ft_strcmp(minishell->tokens[minishell->index].type, "pipe"))
			{
				minishell->pipe_index++;
				minishell->index++;
			}
		}
		int i = 0;
		while (i < minishell->pipe_count)
		{
			close(minishell->fd[i][0]);
			close(minishell->fd[i][1]);
			i++;
		}
				int k = 0;
		while (k < minishell->pipe_count + 1)
		{
			waitpid(-1, NULL, 0); // AVELACNEL STATUSI STUGUM(2RD ARGUMENT)
			k++;
		}
	}
	return (0);
}
