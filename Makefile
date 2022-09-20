# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgros <pgros@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 14:58:11 by pgros             #+#    #+#              #
#    Updated: 2022/09/20 11:56:31 by pgros            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

#./include
INC_FILE = pipex.h

INC = $(addprefix ./include/, $(INC_FILE))

#./src
SRC_MAIN = main.c

SRC_PARSER_FILES = parse.c

SRC_UTILS_FILES = content_utils.c \
					parse_utils.c \
					llst_utils.c \
					strtab_utils.c

# SRC_EXECUTE_FILES = 	child_process.c \
# 						find_path.c

SRC_PARSER = $(addprefix parser/, $(SRC_PARSER_FILES))

SRC_UTILS = $(addprefix utils/, $(SRC_UTILS_FILES))

# SRC_EXECUTE = $(addprefix execute/, $(SRC_EXECUTE_FILES))

# SRC = $(addprefix ./src/, $(SRC_MAIN) \
# 						$(SRC_PARSER) \
# 						$(SRC_UTILS))

SRC = $(SRC_MAIN) \
		$(SRC_PARSER) \
		$(SRC_UTILS) \
		# $(SRC_EXECUTE)
						
# SRC    := $(shell find src -type f -name *.c)
#./objs
# OBJ_MAIN = $(SRC_MAIN:.c=.o)

# OBJ_PARSER_FILES = $(SRC_PARSER_FILES:.c=.o)

# OBJ_UTILS_FILES = $(SRC_UTILS_FILES:.c=.o)

# OBJ_PARSER = $(addprefix parser/, $(OBJ_PARSER_FILES))

# OBJ_UTILS = $(addprefix utils/, $(OBJ_UTILS_FILES))

# OBJS = $(addprefix ./objs/, $(OBJ_MAIN) \
# 						$(OBJ_PARSER) \
# 						$(OBJ_UTILS))
						
OBJS = $(addprefix ./objs/, $(SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

DEBUG_FLAGS = -fsanitize=address

LIBNAME = 42

LIBDIR = ./lib42

RM = rm -f

# .c.o = $(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# .c.o = $(CC) $(CFLAGS) -c $< -o $(patsubst ./src/%, ./objs/%, $(<:.c=.o))

# $(OBJS): $(addprefix ./src/, $(SRC))
# 	$(CC) $(CFLAGS) -c -o $@ $<

./objs/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS) $(INC)
	make -C $(LIBDIR)
	$(CC) $(INC) $(OBJS) -o $@ -l$(LIBNAME) -L$(LIBDIR)

all:	$(NAME)

clean:
	make clean -C $(LIBDIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBDIR)
	$(RM) $(NAME)
	
re: fclean clean all

print_objs: $(OBJS)
	echo $(OBJS)

debug: $(OBJS) $(INC)
	make -C $(LIBDIR)
	$(CC) $(DEBUG_FLAGS) $(INC) $(OBJS) -o $(NAME) -l$(LIBNAME) -L$(LIBDIR)

print_src: $(addprefix ./src/, $(SRC))
	echo $(addprefix ./src/, $(SRC))
	
.PHONY : all clean fclean re debug