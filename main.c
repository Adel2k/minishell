#include "minishell.h"

int main() {
    char *input;
	while (1)
	{
		input = readline("MINISHELL  ");
		printf("%s\n", input);
		if (input)
		{
			if (!strcmp(input, "prc"))
				break ;
			free(input);
		}
		else
			printf("No input received.\n");
	}
    return 0;
}
