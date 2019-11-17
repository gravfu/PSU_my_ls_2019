##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	gcc

FLAGS		=	-Werror -Wall -Wextra

SRC		=	main.c \
			directory.c \
			my_ls_l.c \
			my_advanced_sort_word_array.c \
			my_ls_l_print.c \
			my_ls_t.c \
			my_ls_r.c \
			my_ls_std.c \
			error.c

OBJ     	=       $(SRC:.c=.o)

NAME    	=       my_ls

INCLUDE 	=       ./include

LIB_FOLDER      =       ./lib/my

LIB_NAME        =       my

TEST		=	evalexpr.c \
			tests/test_evalexpr.c

TEST_FLAG	=	--coverage -lcriterion

TEST_NAME	=	unit_tests

all:		$(NAME)

$(NAME):	$(OBJ)
		make -C $(LIB_FOLDER)
		$(CC) -o $(NAME) $(OBJ) -I$(INCLUDE) -L$(LIB_FOLDER) -l$(LIB_NAME) $(FLAGS)

clean:
		rm -f $(OBJ)
		cd $(LIB_FOLDER) && make clean
		rm -f *~
		rm -f *#

fclean:		clean
		cd $(LIB_FOLDER) && make fclean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -f *.gcda
		rm -f *.gcno

tests_run:	all
		$(CC) $(FLAGS) -o $(TEST_NAME) $(TEST) $(TEST_FLAG) -I$(INCLUDE) -L$(LIB_FOLDER) -l$(LIB_NAME) && ./$(TEST_NAME)

re:		fclean all
		cd $(LIB_FOLDER) && make re

auteur:
		echo $(USER) > auteur

.PHONY: 	all clean fclean re tests_run
