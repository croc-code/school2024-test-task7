NAME		=	croc-task
SRCS		=	$(wildcard $(SRCS_DIR)/*.cpp)
SRCS_DIR	=	src

HEADER		=	$(wildcard $(HEADER_DIR)/*.h)

HEADER_DIR	=	inc

CC			=	g++

FLAGS		=	-g  -I $(HEADER_DIR) -Wall -Werror -Wextra

RM			=	rm -f

OBJ 		=	$(SRCS:$(SRCS_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIR		=	bin

ARGS		=	commits.txt result.txt
all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ): $(OBJ_DIR)/%.o : $(SRCS_DIR)/%.cpp  $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
run: ${NAME}
	./${NAME} ${ARGS}

.PHONY: all clean fclean re