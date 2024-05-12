NAME = ircserv
FILES = main.cpp $(wildcard src/*.cpp)
RM = rm -rf
CXX = c++ 
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
OBJ = $(FILES:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all