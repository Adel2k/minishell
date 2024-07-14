#include "minishell.h"

int	open_infile(char *file_name)
{
	int		infile_fd;

	infile_fd = open(file_name, O_RDONLY);
	if (infile_fd < 0)
	{
		write(2, file_name, ft_strlen(file_name));
		write(2, ": No such file or directory\n", 28);
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
		write(2, file_name, ft_strlen(file_name));
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}
	return (outfile_fd);
}

void init_redirs(t_minishell *minishell)
{
	int i;

	i = minishell->index;
	while (i < minishell->tokens_count
		&& ft_strcmp(minishell->tokens[i].type, "pipe") != 0)
	{
		if (ft_strcmp(minishell->tokens[i].type, "in_file") == 0)
		{
			minishell->infile_name = minishell->tokens[i].str;
			minishell->infile = open_infile(minishell->tokens[i].str);
		}
		if (ft_strcmp(minishell->tokens[i].type, "out_file") == 0)
		{
			minishell->outfile_name = minishell->tokens[i].str;
			minishell->outfile = open_outfile(minishell->tokens[i].str, 0);
		}
		if (ft_strcmp(minishell->tokens[i].type, "append_file") == 0)
		{
			minishell->outfile_name = minishell->tokens[i].str;
			minishell->outfile = open_outfile(minishell->tokens[i].str, 1);
		}
		if (ft_strcmp(minishell->tokens[i].type, "limiter") == 0)
			minishell->if_here_doc = here_doc(minishell->tokens[i].str, minishell);
		i++;
	}
}

void redirs(t_minishell *minishell)
{
	in_redir(minishell);
	out_redir(minishell);
	if (minishell->if_here_doc)
	{
		if (dup2((*minishell -> here_doc)[0], 0) == -1)
		{
			close((*minishell -> here_doc)[0]);
			close((*minishell -> here_doc)[1]);
			err(minishell, "dup2 error\n", "");
		}
		close((*minishell -> here_doc)[0]);
		close((*minishell->here_doc)[1]);
	}

}

void in_redir(t_minishell *minishell)
{
	if (minishell->infile > 0)
	{
		if (dup2(minishell->infile, 0) == -1)
		{
			close(minishell->infile);
			err(minishell, "dup2 error\n", "");
		}
		close(minishell->infile);
	}
}
void out_redir(t_minishell *minishell)
{
	if (minishell->outfile > 1)
	{
		if (dup2(minishell->outfile, 1) == -1)
		{
			close(minishell->outfile);
			err(minishell, "dup2 error\n", "");
		}
		close(minishell->outfile);
	}
}
