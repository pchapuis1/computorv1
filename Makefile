NAME        = computor

CC          = c++
RM          = rm -rf

FLAGS       = -Wall -Wextra -Werror -std=c++98 -Iinclude

OBJDIR      = .objs
SRCDIR      = src
INCDIR      = include

FILES       = main PolynomialSolver

SRC         = $(addprefix $(SRCDIR)/, $(FILES:=.cpp))
OBJS        = $(addprefix $(OBJDIR)/, $(FILES:=.o))

HEADERS     = PolynomialSolver.hpp

all:        $(OBJDIR) $(NAME)

$(OBJDIR):
			mkdir $(OBJDIR)

$(NAME):    $(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/, $(HEADERS))
			$(CC) $(FLAGS) -c $< -o $@

clean:
			$(RM) $(OBJDIR)

fclean:     clean
			$(RM) $(NAME)

re:         fclean all

.PHONY:     all clean fclean re
