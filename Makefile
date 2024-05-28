# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 15:33:10 by aaleksee          #+#    #+#              #
#    Updated: 2024/05/01 15:33:12 by aaleksee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = 	ft_printf.c \
		ft_printf_utils_str_nbr.c \
		ft_printf_utils_p_x.c \
		ft_printf_utils_flags.c

BSRC = 	ft_printf_bonus.c \
		ft_printf_utils_bonus_str_nbr.c \
		ft_printf_utils_bonus_p_x.c \
		ft_printf_utils_bonus_flags.c

LIBFTPATH = ./Libft
OSRC = $(SRC:.c=.o)
BOSRC = $(BSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OSRC)
	make -C $(LIBFTPATH)
	cp $(LIBFTPATH)/libft.a .
	mv libft.a $(NAME)
	ar -r $(NAME) $(OSRC)

bonus: $(NAME) $(BOSRC)
	ar -r $(NAME) $(BOSRC)

executable: $(NAME)
	$(CC) $(CFLAGS) -o test $(NAME)

test: executable
	./test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OSRC)
	rm -f $(BOSRC)
	make clean -C $(LIBFTPATH)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all bonus clean fclean re