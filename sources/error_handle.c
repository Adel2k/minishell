#include "minishell.h"

void	malloc_check(void *str)
{
	if (!str)
		error_handle();
}
void	error_handle(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}