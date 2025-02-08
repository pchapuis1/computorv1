NAME		= computor

CC			= c++

RM 			= rm -rf

FLAGS		= -Wall -Wextra -Werror -std=c++98

all:		${NAME}

${NAME}: 	main.cpp
			${CC} ${FLAGS} main.cpp -o ${NAME}

clean:
			${RM}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re