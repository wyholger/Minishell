#include "../../include/minishell.h"


void ft_parser(t_data *data)
{
	int check;
	
	check = 0;
	check = ft_check_all_string(data);
	if (check == 0)
	{
		ft_pars_token(data);
		ft_treatmen_token(data);
		ft_filling_info(data);
		//info_print_content(&data->info);
	}
		
   else
	   printf("Syntax Error\n");  
	ft_lstclear(&data->token);


	
	
}


