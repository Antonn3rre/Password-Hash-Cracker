NAME = hash_cracker

CC = c++
FGLAGS = -Wall -Wextra -Werror
LIBS = -lcrypto
RM = rm -rf

SRCS = main.cpp Config.cpp
OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
