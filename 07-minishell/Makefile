# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguay <aguay@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 08:51:26 by aguay             #+#    #+#              #
#    Updated: 2022/09/13 14:10:40 by aguay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## -----  NAME OF THE PROGRAMM ----- ##
NAME 			= minishell

## ----- CHOOSE COMPILER AND FLAGS ----- ##
CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

## ----- PATH TO FOLDERS ----- ##
SRCS_DIR		= srcs/

OBJ_DIR			= obj/

INCLUDE_DIR		= includes/

LIB_DIR			= $(LIBFT_DIR)lib/

M1LIB_DIR		= $(LIBFT_DIR)m1lib/

PARSING_DIR		= $(SRCS_DIR)parsing

BUILTINS_DIR	= $(SRCS_DIR)builtins

PROMPT_DIR		= $(SRCS_DIR)prompt

MAIN_DIR		= $(SRCS_DIR)main

ENGINE_DIR		= $(SRCS_DIR)engine

SIGNAL_DIR		= $(SRCS_DIR)signals

READLINES_HDIR	= $(INCLUDE_DIR)readline/

## ----- LIBFT PATH ----- ##

LIBFT_DIR		= $(SRCS_DIR)libft/

LIBFT_OBJ		= $(SRCS_DIR)libft/obj/

LIBFT_INC		= $(SRCS_DIR)libft/includes/

## ----- FILES ----- ##
SRCS_FILES			=					\

PARSING_FILES		=					\
			analyser_utils.c			\
			command_parsing.c			\
			entry_analyser.c			\
			expand.c					\
			heredoc.c					\
			expand_norm.c				\
			expand_utils.c				\
			expand_utils2.c				\
			expand_utils3.c				\
			input.c						\
			output.c					\
			parsing_utils.c				\
			parsing.c					\
			path.c						\
			redirection.c				\
			split_entry.c				\
			splittin.c					\

BUILTINS_FILES		=					\
			builtins.c					\
			cd.c						\
			echo.c						\
			env.c						\
			exit.c						\
			export.c					\
			pwd.c						\
			unset.c						\
			status.c					\

PROMPT_FILES		=					\
			prompt_utils.c				\
			prompt.c					\
			

MAIN_FILES			=					\
			command_utils.c				\
			envp.c						\
			ft_create_file.c			\
			ft_freeall.c				\
			ft_realloc.c				\
			ft_revRealloc.c				\
			ft_strdecale.c				\
			ft_strsdup.c				\
			ft_update_envar.c			\
			main.c						\

ENGINE_FILES		=					\
			builtins_engine.c			\
			command_engine.c			\
			engine.c					\
			exit_status.c				\
			fd_setup.c					\
			ft_create_pipe.c			\

SIGNAL_FILES		=					\
			sig_utils.c					\
			handler.c					\
			sig_reset.c					\

INCLUDES_FILES		=					\
			commands.h					\
			minishell.h					\

READLINES_HFILES	=					\
			chardefs.h					\
			history.h					\
			keymaps.h					\
			readline.h					\
			rlconf.h					\
			rlstdc.h					\
			rltypedefs.h				\
			tilde.h						\

## -----  if to compile differently on other os ----- ##
## ifeq ($(shell uname), Linux)
## endif

## ----- ADDPREFIX TO FILES ----- ##

BUILTINS_SRCS	=	$(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))
PROMPT_SRCS		=	$(addprefix $(PROMPT_DIR), $(PROMPT_FILES))
PARSING_SRCS	=	$(addprefix $(PARSING_DIR), $(PARSING_FILES))
MAIN_SRCS		=	$(addprefix $(MAIN_DIR), $(MAIN_FILES))
ENGINE_SRCS		=	$(addprefix $(ENGINE_DIR), $(ENGINE_FILES))
SIGNAL_SRCS		=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_FILES))

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES	=		$(SRCS_FILES:.c=.o) $(PARSING_FILES:.c=.o) $(BUILTINS_FILES:.c=.o) $(PROMPT_FILES:.c=.o) $(MAIN_FILES:.c=.o) $(ENGINE_FILES:.c=.o) $(SIGNAL_FILES:.c=.o)

READLINES_HSRCS	=	$(addprefix $(READLINES_HDIR), $(READLINES_HFILES))
INCLUDES_SRCS	=	$(addprefix $(INCLUDE_DIR), $(INCLUDES_FILES)) $(READLINES_HSRCS)

VPATH			=	$(SRCS_DIR) $(PARSING_DIR) $(BUILTINS_DIR) $(PROMPT_DIR) $(MAIN_DIR) $(ENGINE_DIR) $(INCLUDES_SRCS) $(SIGNAL_DIR)

## ----- .C TO .O CONVERT ----- ##

$(OBJ_DIR)%.o: %.c $(INCLUDES_SRCS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIB_DIR) -I $(LIBFT_INC) -c $< -o $@

#--------------------------------------------------------------#

## ----- TOOLS AND COLORS ----- ##
RM				= rm -rf
NO_PRINT		= --no-print-directory
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m
PINK 			= \033[35m
AQUA 			= \033[36m
GREY 			= \033[37m
UNDERLINE 		= \033[4m
NORMAL 			= \033[0m

LIBFT			= make -C $(LIBFT_DIR)

## ----- ALL ACTION DEPENDENCIES AND RECIPE FOR MAIN PROGRAM ----- ##

all: obj $(NAME)

## Compile with intel architecture is arch = 
ifeq ($(shell arch), i386)
$(NAME): $(OBJ_DIR) $(OBJS)
	$(LIBFT)
	$(CC) $(OBJS) $(LIBFT_DIR)libft.a $(LIB_DIR)libreadline.a $(LIB_DIR)libhistory.a -lcurses -lreadline -o $(NAME)
endif

ifeq ($(shell arch), x86_64)
$(NAME): $(OBJ_DIR) $(OBJS)
	$(LIBFT)
	$(CC) $(OBJS) $(LIBFT_DIR)libft.a $(LIB_DIR)libreadline.a $(LIB_DIR)libhistory.a -lcurses -lreadline -o $(NAME)
endif

ifeq ($(shell arch), arm64)
$(NAME): $(OBJ_DIR) $(OBJS)
	$(LIBFT)
	$(CC) $(OBJS) $(LIBFT_DIR)libft.a $(M1LIB_DIR)libreadline.a $(M1LIB_DIR)libhistory.a -lcurses -lreadline -o $(NAME)
endif

obj:
	@mkdir -p $(OBJ_DIR)

## ----- make options ----- #
debug: CFLAGS += -g
debug:	fclean obj $(NAME)


opti: CFLAGS += -O3
opti: obj $(NAME)

leak: obj $(NAME)
	@valgrind --suppressions=ignore_rdl_leaks.txt --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

setup:
	@rm -rf LICENSE images README.md

library:
	@mv includes/readline readlineHead
	@mv srcs/libft/lib lib
	@mv srcs/libft/m1lib m1lib
	@rm -rf .git images includes srcs .gitignore ignore_rdl_leaks.txt Makefile valgrind_ignore_readline.txt LICENSE README.md 


## ----- CLEAN COMMANDS ----- ##
clean:
	$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBFT_DIR)libft.a
	@rm -rf $(NAME).dSYM*

re: fclean all

.PHONY: all clean fclean re
