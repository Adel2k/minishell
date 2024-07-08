#include "minishell.h"

void	free_tokens(t_token *tokens, char *s, int i)
{
	free(tokens[i].str);
	free(s);
}
