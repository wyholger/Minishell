SRCS		=	src/main.c

SRCS_LIBFT	=	libft/ft_atoi.c			libft/ft_isdigit.c		libft/ft_memmove.c		libft/ft_strlen.c\
				libft/ft_bzero.c		libft/ft_isprint.c		libft/ft_memset.c		libft/ft_strncmp.c\
				libft/ft_calloc.c		libft/ft_memccpy.c		libft/ft_strchr.c		libft/ft_strnstr.c\
				libft/ft_isalnum.c		libft/ft_memchr.c		libft/ft_strdup.c		libft/ft_strrchr.c\
				libft/ft_isalpha.c		libft/ft_memcmp.c		libft/ft_strlcat.c		libft/ft_tolower.c\
				libft/ft_isascii.c		libft/ft_memcpy.c		libft/ft_strlcpy.c		libft/ft_toupper.c\
				libft/ft_substr.c		libft/ft_strjoin.c		libft/ft_strtrim.c		libft/ft_itoa.c\
				libft/ft_split.c		libft/ft_strmapi.c		libft/ft_putchar_fd.c	libft/ft_putstr_fd.c\
				libft/ft_putendl_fd.c	libft/ft_putnbr_fd.c	libft/get_next_line.c 	libft/ft_atoi_base.c\
				libft/ft_lstnew.c		libft/ft_lstadd_front.c	libft/ft_lstsize.c		libft/ft_lstlast.c\
				libft/ft_lstadd_back.c	libft/ft_lstdelone.c	libft/ft_lstclear.c		libft/ft_lstiter.c\
				libft/ft_lstprint_content.c

OBJS_LIBFT	=	${SRCS_LIBFT:.c=.o}

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

NAME		=	minishell

HDR			=	include/minishell.h

HDR_LIBFT	= libft/libft.h

all: $(NAME) $(OBJS) $(HDR)

$(NAME):	$(OBJS) $(OBJS_LIBFT)
		make -C libft
		$(CC) $(FLAGS)  -Llibft -lft  $(SRCS) libft/libft.a -o $(NAME)

%.o: %.c $(HDR) $(HDR_LIBFT)
		$(CC) $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./libft

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) fclean -C ./libft

re:		fclean all clean