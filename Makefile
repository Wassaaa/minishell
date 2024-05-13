# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 14:15:32 by aklein            #+#    #+#              #
#    Updated: 2024/05/13 23:01:29 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
DB_FLAGS		=	-g #-fsanitize=leak
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES)
CC_FULL			=	$(CC) $(CC_STRICT) $(DB_FLAGS) $(HEADERS)

################################################################################
# LIBFT
################################################################################
LIBFT			=	./libft/libft.a
LIBFT_DIR		=	./libft
LIBFT_INCLUDES	=	./libft/include

################################################################################
# READLINE
################################################################################
READLINE		=	-lreadline

################################################################################
# MANDATORY
################################################################################
NAME			=	minishell
INCLUDES		=	./include
M_HEADERS		=	$(INCLUDES)/minishell.h \
					$(INCLUDES)/tokenizer.h
OBJ_DIR			=	./obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
SRC_DIR			=	./src
SRCS			=	minishell.c \
					tokenizer/tokenizer.c \
					tokenizer/token_list.c \
					tokenizer/token_utils.c \
					tokenizer/token_utils2.c \
					tokenizer/token_utils3.c \
					init.c \
					# parsing.c 


################################################################################
# RULES
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(READLINE) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(M_HEADERS)
	mkdir -p $(@D)
	$(CC_FULL) -c $< -o $@

$(LIBFT): libft_force
	make -C $(LIBFT_DIR)

libft_force:
	@true

clean:
	rm -rf $(NAME).dSYM/ obj/
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

################################################################################
# NORM
################################################################################
norm:
	norminette . $(LIBFT_DIR) | grep -v "OK!" || true

norm2:
	norminette . $(LIBFT_DIR)

################################################################################
# PHONY
################################################################################
.PHONY: all bonus re clean fclean libft_force db