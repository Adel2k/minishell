/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/16 02:26:41 by hrigrigo         ###   ########.fr       */
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

void exec_cmd(t_minishell *minishell)
{
	while (minishell->index < minishell->tokens_count)
	{
		minishell->infile = 0;
		minishell->outfile = 1;
		minishell->if_here_doc = 0;
		minishell->cmd = NULL;
		init_redirs(minishell);
		run_commands(minishell);
		if (minishell->index < minishell->tokens_count
			&& !ft_strcmp(minishell->tokens[minishell->index].type, "pipe"))
		{
			minishell->pipe_index++;
			minishell->index++;
		}
		free_cmd(minishell->cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *input;

	(void) argc;
	(void) argv;
	minishell = malloc(sizeof(t_minishell));
	//printf("minishell malloced\n");
	if (!minishell)
		return (1);
	minishell->env = env;
	minishell->envm = init_env(minishell);
	minishell->cmd_dirs = init_dirs(minishell);
	while (1)
	{
		input = readline("\033[0;034mPONCHIKI_MINISHELL:  \033[0;000m");
		//printf("input malloced\n");
		add_history(input);
		if (init_cmd_line(minishell, input) < 0)
		{
			free_tokens(minishell->tokens, minishell->tokens_count);
			free_cmd(minishell->cmd);
			if (minishell->pipe_count > 0)
			{
				free(minishell->fd);
				//printf("minishell->fd freed\n");	
			}
			if (minishell->if_here_doc)
			{
				free(minishell->here_doc);
				//printf("minishell->heredoc freed\n");	
			}
			continue ;
		}
		exec_cmd(minishell);
		close_fd(minishell);
		waiting_childs(minishell);
		free_tokens(minishell->tokens, minishell->tokens_count);
		if (minishell->pipe_count > 0)
		{
			free(minishell->fd);
			//printf("minishell->fd freed\n");	
		}
		if (minishell->if_here_doc)
		{
			free(minishell->here_doc);
			//printf("minishell->heredoc freed\n");	
		}
		system("leaks minishell");
	}
	int i = 0;
	while (minishell -> cmd_dirs[i])
	{
		free(minishell->cmd_dirs[i]);
		i++;
	}
	free(minishell->cmd_dirs);
	//printf("minishell->cmd_dirs malloced\n");
	return (0);
}
