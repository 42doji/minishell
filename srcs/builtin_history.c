#include "../includes/minishell.h"

void	print_history(void)
{
	HIST_ENTRY	**the_list;
	int			i;

	the_list = history_list();
	if (the_list)
	{
		i = 0;
		while (the_list[i])
		{
			printf("%d\t%s\n", i, the_list[i]->line);
			i++;
		}
	}
	else
		printf("No history\n");
}