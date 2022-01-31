#include "libft.h"

int		ft_search_word_in_str_on_end(char *str, char *word)
{
	int i;
	int len_str;
	int len_word;

	i = 0;
	if (!str || !word)
		return (1);
	len_str = (int)ft_strlen(str);
	len_word = (int)ft_strlen(word);
	if (len_word == 0 || len_str == 0 || len_word > len_str)
		return (1);
	i = len_str - 1;
	while (i >= 0 && (len_word -1) >= 0 && str[i] == word[len_word - 1])
	{
		i--;
		len_word--;
	}
	if (len_word == 0)
		return (0);
	return (1);
}
