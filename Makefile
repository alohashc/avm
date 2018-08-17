NAME := avm

SRC := main.cpp Lexer.cpp Parser.cpp OperandFactory.cpp AvmExcept.cpp

OBJ := $(SRC:%.cpp=%.o)

CXXFLAGS := -std=c++11 -c -Wall -Wextra -Werror -I include

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<  -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all
