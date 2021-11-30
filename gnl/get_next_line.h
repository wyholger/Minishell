#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_line(char *str);
int		ft_check_str(char *str);
char	*ft_new_line(char *str);
char	*ft_new_tmp(char *str);
int		ft_check_tmp(char *str);
char	*get_next_line(int fd);
int		ft_len_to_n(char *str);

#endif
