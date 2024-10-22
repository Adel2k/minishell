/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:14:53 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/26 14:07:50 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	exec_cmd(t_minishell *minishell)
{
	while (minishell->index < minishell->tokens_count)
	{
		minishell->infile = 0;
		minishell->outfile = 1;
		minishell->if_here_doc = 0;
		minishell->is_builtin = 0;
		minishell->cmd = NULL;
		init_redirs(minishell);
		minishell->cmd = cmd_args(minishell);
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

void	loop_for_lines2(t_minishell *minishell)
{
	minishell->cmd_dirs = init_dirs(minishell);
	exec_cmd(minishell);
	close_fd(minishell);
	waiting_childs(minishell);
	free_dirs(minishell);
	free_tokens(minishell->tokens, minishell->tokens_count);
	if (minishell->pipe_count > 0)
		free(minishell->fd);
	if (minishell->if_here_doc)
		free(minishell->here_doc);
}

void	loop_for_lines(t_minishell *minishell, char *input)
{
	while (input)
	{
		signals();
		input = readline("\033[38;5;43mPONCHIKI_MINISHELL: \033[0;000m");
		add_history(input);
		if (!input)
			break ;
		minishell->cmd = NULL;
		minishell->cmd_dirs = NULL;
		minishell->tokens = NULL;
		minishell->if_here_doc = 0;
		if (init_cmd_line(minishell, input) < 0)
		{
			input = "";
			free_tokens(minishell->tokens, minishell->tokens_count);
			if (minishell->pipe_count > 0)
				free(minishell->fd);
			if (minishell->if_here_doc)
				free(minishell->here_doc);
			continue ;
		}
		loop_for_lines2(minishell);
		free(input);
	}
	printf("exit\n");
}

void	print_logo(void)
{
	printf("\e[38;5;43m%s\n%s\n%s\n%s\n%s\n%s\n\e[0m", \
	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ", \
	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ", \
	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ", \
	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ", \
	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗", \
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝");
	printf("\e[0m\n");
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*input;

	(void) argc;
	(void) argv;
	input = "";
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
	minishell->env = env;
	minishell->envm = init_env(env);
	print_logo();
	loop_for_lines(minishell, input);
	return (0);
}
