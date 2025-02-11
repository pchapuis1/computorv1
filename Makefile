NAME        	= computor

NAME_BONUS		= computor_bonus

CC          	= c++

RM          	= rm -rf

FLAGS       	= -Wall -Wextra -Werror -std=c++98 -Iinclude

OBJDIR      	= .objs

OBJDIR_BONUS 	= .objs_bonus

SRCDIR			= src

SRCDIR_BONUS	= src_bonus

SRCS			= main PolynomialSolver

SRCS_BONUS      = main_bonus PolynomialSolver_bonus

INCDIR      	= include

OBJS        	= $(addprefix $(OBJDIR)/, $(SRCS:=.o))

OBJS_BONUS		= $(addprefix $(OBJDIR_BONUS)/, $(SRCS_BONUS:=.o))

HEADERS     	= PolynomialSolver.hpp

HEADERS_BONUS	= PolynomialSolverBonus.hpp

all:        $(OBJDIR) $(NAME)

$(OBJDIR):
			mkdir $(OBJDIR)

$(NAME):    $(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/, $(HEADERS))
			$(CC) $(FLAGS) -c $< -o $@

bonus:		$(OBJDIR_BONUS) $(NAME_BONUS)

$(OBJDIR_BONUS):
			mkdir $(OBJDIR_BONUS)

$(NAME_BONUS):    $(OBJS_BONUS)
			$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.cpp $(addprefix $(INCDIR)/, $(HEADERS_BONUS))
			$(CC) $(FLAGS) -c $< -o $@

clean:
			$(RM) $(OBJDIR)
			$(RM) $(OBJDIR_BONUS)

fclean:     clean
			$(RM) $(NAME)
			$(RM) $(NAME_BONUS)

re:         fclean all

.PHONY:     all clean fclean re
