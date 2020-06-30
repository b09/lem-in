#include "../libft/inc/libft.h"
#include <stdio.h>

int		main(void)
{
	char *str;

	while (gnl_with_newline(0, &str))
	{
		printf("%s\n", str);
		ft_memdel((void*)&str);
	}
	if (str)
	{
		printf("%s\n", str);
		ft_memdel((void*)&str);
	}
	system("leaks ./a.out < main.c");
	return (0);
}