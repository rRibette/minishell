####################### SETUP ##########################

CC = cc

RM = rm -rf

NAME = minishell

LIBFT = libft.a

####################### FLAGS ##########################

CFLAGS = -Wall -Wextra -Werror -g3

READ_FLAG = -lreadline

####################### DIRECTORIES ####################

INC_DIR = -Iincludes/

LIBFT_DIR = libft/

####################### PATH ###########################

SRC_PATH = src/

BUILTINS_PATH = $(SRC_PATH)builtins/

DEBUG_PATH = $(SRC_PATH)debug/

ENV_PATH = $(SRC_PATH)env/

ERROR_FREE = $(SRC_PATH)error_free/

MAIN_PATH = $(SRC_PATH)main/

PARSING_PATH = $(SRC_PATH)parsing/

UTILS_PATH = $(SRC_PATH)utils/

EXEC_PATH = $(SRC_PATH)exec/

OBJ_PATH = obj/

LDFLAGS = -lreadline

####################### SRC & OBJ ######################

SRCS =  $(ENV_PATH)get_path.c \
		$(ENV_PATH)env_utils.c \
		$(ENV_PATH)env_utils2.c \
\
		$(ERROR_FREE)free.c \
		$(ERROR_FREE)free_2.c \
		$(ERROR_FREE)error_msg.c \
		$(ERROR_FREE)error_msg_2.c \
\
		$(DEBUG_PATH)print.c \
\
		$(PARSING_PATH)tokenize.c \
		$(PARSING_PATH)tokenize_utils.c \
		$(PARSING_PATH)token.c \
		$(PARSING_PATH)token_utils.c \
		$(PARSING_PATH)varsubst.c \
		$(PARSING_PATH)varsubst_utils.c \
		$(PARSING_PATH)varsubst_itoa.c \
		$(PARSING_PATH)parsing.c \
		$(PARSING_PATH)redir.c \
		$(PARSING_PATH)syntax.c \
		$(PARSING_PATH)categorize.c \
		$(PARSING_PATH)cmdarg.c \
		$(PARSING_PATH)cmdarg_split.c \
		$(PARSING_PATH)cmdarg_utils.c \
		$(PARSING_PATH)chartab.c \
		$(PARSING_PATH)free_parsing.c \
		$(PARSING_PATH)print_parsing.c \
		$(PARSING_PATH)free_token.c \
		$(PARSING_PATH)ft_strjoinsep.c \
		$(PARSING_PATH)assignment.c \
\
		$(UTILS_PATH)init.c \
		$(UTILS_PATH)create_list_env.c \
		$(UTILS_PATH)create_list_cmd.c \
		$(UTILS_PATH)utils.c \
\
		$(EXEC_PATH)create_process.c \
		$(EXEC_PATH)create_process_2.c \
		$(EXEC_PATH)open_close.c \
		$(EXEC_PATH)redirections.c \
		$(EXEC_PATH)redirection_2.c \
		$(EXEC_PATH)update_shlvl.c \
		$(EXEC_PATH)signals.c \
		$(EXEC_PATH)signals_2.c \
		$(EXEC_PATH)signals_3.c \
		$(EXEC_PATH)waitpid.c \
		$(EXEC_PATH)heredoc.c \
\
		$(BUILTINS_PATH)pwd.c \
		$(BUILTINS_PATH)check_builtins.c \
		$(BUILTINS_PATH)exit.c \
		$(BUILTINS_PATH)cd.c \
		$(BUILTINS_PATH)export.c \
		$(BUILTINS_PATH)export_2.c \
		$(BUILTINS_PATH)env.c \
		$(BUILTINS_PATH)builtins_utils.c \
		$(BUILTINS_PATH)unset.c \
		$(BUILTINS_PATH)ft_echo.c

OBJS = ${SRCS:.c=.o}

####################### RULES ##########################

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(LIBFT)
	@$(RM) $(MAIN_PATH)main.o

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

tclean : clean
	@$(RM) test parsingtest.o

re: fclean all

####################### COMPILATION ####################

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR) -I$(LIBFT_DIR)

$(NAME): $(MAIN_PATH)main.o $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(READ_FLAG) $(LIBFT) $(INC_DIR)

test : parsingtest.o $(OBJS)
	$(MAKE) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(INC_DIR) -I$(LIBFT_DIR) $(LIBFT) $(READ_FLAG) -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)$(LIBFT) .

.PHONY: all clean fclean re tclean
