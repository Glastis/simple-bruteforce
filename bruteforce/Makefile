SRC=			./main.c \
			./utilities.c \

OBJ=			 $(SRC:.c=.o)

NAME=			 a.out

CFLAGS=			-Wall -Wextra -Werror -g3 

LIBS=			-lcrypto

all:			$(NAME)

$(NAME):		$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)

fclean:			clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
