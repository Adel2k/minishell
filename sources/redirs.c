/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:49:54 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/21 18:13:31 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *file_name)
{
	int		infile_fd;

	infile_fd = open(file_name, O_RDONLY);
	if (infile_fd < 0)
	{
		err_message("minishell: ", file_name, ": No such file or directory\n");
		return (-1);
	}
	return (infile_fd);
}

int	open_outfile(char *file_name, int i)
{
	int		outfile_fd;

	if (i == 0)
		outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outfile_fd = open(file_name, O_APPEND | O_WRONLY, 0777);
	if (outfile_fd < 0)
	{
		err_message("minishell: ", file_name, ": No such file or directory\n");
		return (-1);
	}
	return (outfile_fd);
}

void	redirs(t_minishell *minishell)
{
	in_redir(minishell);
	out_redir(minishell);
	if (minishell->if_here_doc)
	{
		if (dup2((*minishell -> here_doc)[0], 0) == -1)
		{
			close((*minishell -> here_doc)[0]);
			close((*minishell -> here_doc)[1]);
			err_message("minishell: ", "dup2 error\n", "");
		}
		close((*minishell -> here_doc)[0]);
		close((*minishell->here_doc)[1]);
	}
}

void	in_redir(t_minishell *minishell)
{
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, 0) == -1)
		{
			close(minishell->infile);
			err_message("minishell: ", "dup2 error\n", "");
		}
		close(minishell->infile);
	}
}

void	out_redir(t_minishell *minishell)
{
	if (minishell->outfile > 1)
	{
		if (dup2(minishell->outfile, 1) == -1)
		{
			close(minishell->outfile);
			err_message("minishell: ", "dup2 error\n", "");
		}
		close(minishell->outfile);
	}
}
