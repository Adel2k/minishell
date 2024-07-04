#include "minishell.h"

int main()
{
    char *input;
	while (1)
	{
		input = readline("MINISHELL  ");
		char **str = ft_split(input);
		int i = 0;
        while (str[i])
        {
            printf("%s\n", str[i]);
            i++;
        }
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
