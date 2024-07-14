/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/13 21:14:02 by hrigrigo         ###   ########.fr       */
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

void check_for_valid_files(t_minishell *minishell)
{
	if (minishell->infile < 0)
	{
		write(2, minishell->infile_name, ft_strlen(minishell->infile_name));
		err(minishell, ": No such file or directory\n");
	}
	if (minishell->outfile < 0)
	{
		write(2, minishell->outfile_name, ft_strlen(minishell->outfile_name));
		err(minishell, ": No such file or directory\n");
	}
}

void exec_cmd(t_minishell *minishell)
{
	while (minishell->index < minishell->tokens_count)
	{
		minishell->infile = 0;
		minishell->outfile = 1;
		minishell->if_here_doc = 0;
		minishell->cmd = NULL;
		init_redirs(minishell);
		check_for_valid_files(minishell);
		if (count_cmd_args(minishell) == 0)
			return ;
		run_commands(minishell);
		if (minishell->index < minishell->tokens_count
			&& !ft_strcmp(minishell->tokens[minishell->index].type, "pipe"))
		{
			minishell->pipe_index++;
			minishell->index++;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *input;

	(void) argc;
	(void) argv;
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
	minishell->env = env;
	minishell->envm = init_env(minishell);
	minishell->cmd_dirs = init_dirs(minishell);
	while (1)
	{
		input = readline("\033[0;034mPONCHIKI_MINISHELL:  \033[0;000m");
		add_history(input);
		init_cmd_line(minishell, input);
		exec_cmd(minishell);
		close_fd(minishell);
		waiting_childs(minishell);
	}
	return (0);
}
