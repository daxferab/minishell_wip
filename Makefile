#GENERAL VARIABLES

MAKEFLAGS := --no-print-directory

RM := rm -rf
MKDIR := mkdir -p

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address

#INCLUDE

SRC_DIR := src/
OBJ_DIR := obj/
INC_DIR := include/
HEADER := $(INC_DIR)/$(NAME).h

LIBFT_PATH := libft/
LIBFT := $(LIBFT_PATH)libft.a
LIBFT_FLAG := -L $(LIBFT_PATH) -l ft

#FILES

DIRECTORIES :=	\
				builtins\
				control\
				env\
				execution\
				parse\

SOURCES :=	\
			minishell.c\
			$(addprefix builtins/,\
				cmd_cd.c\
				cmd_echo.c\
				cmd_env.c\
				cmd_exit.c\
				cmd_export.c\
				cmd_pwd.c\
				cmd_unset.c\
			)\
			$(addprefix control/,\
				debug.c\
				free.c\
			)\
			$(addprefix env/,\
				env_list.c\
				env_utils.c\
			)\
			$(addprefix execution/,\
				input_handler.c\
			)\
			$(addprefix parse/,\
				add_token.c\
				clear_input.c\
				get_variable.c\
				parse_pipeline.c\
				read_line.c\
				syntax.c\
				token_type.c\
				tokenize.c\
			)\

OBJECTS := $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))
SOURCES := $(addprefix $(SRC_DIR), $(SOURCES))

#COLOURS

RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m

RESET := \033[0m

#RULES

.PHONY: a all
a: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAG) -l readline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(addprefix $(OBJ_DIR),$(DIRECTORIES))

.PHONY: c clean
c: clean
clean: msg_clean_start
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) msg_clean_end

.PHONY: f fclean
f: fclean
fclean: msg_fclean_start
	$(RM) $(OBJ_DIR) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) msg_fclean_end

.PHONY: re
re: fclean all

#EXTRA RULES

.PHONY: e exec
e: exec
exec: all
	./$(NAME)

.PHONY: d debug
d: debug
debug: all
	./$(NAME) debug

.PHONY: n norminette normi
n: norminette
norminette:
	@echo "norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_PATH) | grep Error\n"
	@if norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_PATH) | grep -q "Error"; then echo "$(RED)$$(norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_PATH) | grep "Error" | sed -z 's/\nError/\n\$(YELLOW)  Error/g' | sed -z 's/\n/\n\$(RED)/g')$(RESET)"; else echo "$(GREEN)Everything OK!$(RESET)"; fi
normi:
	@if norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_PATH) | grep -q "Error"; then echo "\n$(RED)$$(norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_PATH) | grep "Error" | grep -v -e "TOO_MANY_FUNCS" -e "WRONG_SCOPE_COMMENT" -e "EMPTY_LINE_FUNCTION" -e "LINE_TOO_LONG" -e "TOO_MANY_LINES" -e "CONSECUTIVE_NEWLINES" -e "INVALID_HEADER" | sed -z 's/\nError/\n\$(YELLOW)  Error/g' | sed -z 's/\n/\n\$(RED)/g')$(RESET)"; else echo "$(GREEN)Run full norminette!$(RESET)"; fi

#MESSAGES

.PHONY: msg_clean_start msg_clean_end msg_fclean_start msg_fclean_end

msg_clean_start:
	@echo "$(YELLOW)Cleaning minishell objects$(RED)"

msg_clean_end:
	@echo "$(GREEN)Minishell objects cleaned$(RESET)"

msg_fclean_start:
	@echo "$(YELLOW)Cleaning minishell$(RED)"

msg_fclean_end:
	@echo "$(GREEN)Minishell cleaned$(RESET)"