NAME			=	containers_test

RM				=	rm -rf
CC				=	g++
OPTFLAGS		=	-g -fsanitize=address
FLAGS			=	-std=c++98 -Wall -Wextra -Werror -pedantic -MMD -MP

#Include file's
INCS_FILES		=	Stack.hpp

#Source file's
SOURCE_FILES	=	main.cpp

#Doxygen config file
DOXYGEN_CONFIG	=	../docs/doxygenConf

#Finish include
INC_PATH		=	../project/
INC_NAME		=	$(INCS_FILES)
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))

#Finish source
SRCS_PATH		=	./
SRCS_NAME		=	$(SOURCE_FILES)
SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))
#Finish objs
OBJS_PATH		=	./objs/
OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS_NAME:.cpp=.o))

all: ${NAME}

$(NAME): $(OBJS_PATH) $(OBJS)
	@$(CC) $(FLAGS) $(OPTFLAGS) -I$(INC_PATH) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "built $(NAME) finish"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp $(INC)
	@$(CC) $(FLAGS) $(OPTFLAGS) -I$(INC_PATH) -c $< -o $@
	@echo "Compiling: $<"

$(OBJS_PATH):
	@mkdir -p ${OBJS_PATH}

doxygen:
	@doxygen $(DOXYGEN_CONFIG) 2> /dev/null 1> /dev/null
	@echo "generate documentation with doxygen finish"

clean:
	@echo "Cleaning: $(OBJS_PATH)"
	@$(RM) $(OBJS_PATH)

fclean:		clean
	@echo "Cleaning: $(NAME)"
	@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re doxygen
