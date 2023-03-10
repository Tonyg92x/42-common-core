NAME = cub3d

NAME_B = cub3d_bonus

FLAGS = -Wall -Werror -Wextra -O3

SRCS = 	main/main.c					\
		main/main_init.c			\
		main/utils.c				\
		main/movement.c				\
		main/game_hooks.c			\
		main/rotation.c				\
		main/movement_utils.c		\
		utils/get_next_line.c		\
		utils/get_next_line_utils.c	\
		utils/dblink/dblink_utils.c	\
		utils/dblink/dblink.c		\
		parsing/verif.c				\
		parsing/verif_wall.c		\
		parsing/mapInit.c			\
		parsing/parsing.c			\
		parsing/map.c				\
		parsing/map_second.c		\
		parsing/map_third.c			\
		parsing/orientation.c		\
		parsing/resize_map.c		\
		parsing/parsing_utils.c		\
		parsing/mapInit_utils.c		\
		render/graphic_operator.c	\
		render/graphic_operator2.c	\
		render/raycaster.c 			\
		render/raycaster_utils.c	\
		render/raycaster_utils2.c	\
		render/fisheye.c			\
		render/draw.c				\
		render/render_texture.c		\

SRCS_B =  	main/main.c				\
		main/main_init.c			\
		main/utils.c				\
		main/movement.c				\
		main/rotation.c				\
		main/movement_utils.c		\
		utils/get_next_line.c		\
		utils/get_next_line_utils.c	\
		utils/dblink/dblink_utils.c	\
		utils/dblink/dblink.c		\
		parsing/verif.c				\
		parsing/verif_wall.c		\
		parsing/mapInit.c			\
		parsing/map_second.c		\
		parsing/map_third.c			\
		parsing/parsing.c			\
		parsing/map.c				\
		parsing/orientation.c		\
		parsing/resize_map.c		\
		parsing/parsing_utils.c		\
		parsing/mapInit_utils.c		\
		render/graphic_operator.c	\
		render/graphic_operator2.c	\
		render/raycaster.c 			\
		render/raycaster_utils.c	\
		render/raycaster_utils2.c	\
		render/fisheye.c			\
		render/draw.c				\
		render/render_texture.c		\
		bonus/game_hooks_bonus.c	\
		bonus/render_map.c			\

HEADER = ./Include/cube.h

FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit

LIBS =  ./utils/libft/libft.a ./utils/MLX/libmlx42.a  ./utils/MLX/glfw/lib-x86_64/libglfw3.a

.c.o:
	@gcc  ${FLAGS}  -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}

OBJS_B = ${SRCS_B:.c=.o}

MAP = ./map/valid_map1.cub

CC = gcc

OS := $(shell uname -s)

all: ${NAME}
${NAME}:${OBJS}
		@$(MAKE) -C ./utils/libft
		@$(MAKE) -s -C ./utils/MLX

ifeq ($(OS),Darwin)
		@${CC} ${FLAGS} ${OBJS} ${LIBS} ${FRAMEWORK} -o ${NAME}
endif

ifeq ($(OS),Linux)
		@${CC} ${FLAGS} ${OBJS} ./utils/MLX/libmlx42.a ./utils/libft/libft.a -lglfw -lrt -ldl -lm -o  ${NAME}
endif

clean:
		@${RM} ${OBJS}
		@${RM} ${OBJS_B}

fclean: clean
	make -C ./utils/libft clean
	rm -rf cub3d
	rm -rf cub3d_bonus

git:
	@git add ${SRCS} ${HEADER} Makefile

val:
	valgrind --track-origins=yes --leak-check=full ./$(NAME) ./map/valid_map1.cub

run: all
	./${NAME} ./map/valid_map1.cub

norm:
	norminette ${SRCS}

bun: all

leak: all
	@echo "\033[92mTEST 1 \n \033[0m"
	@leaks --atExit --  ./${NAME} ./map/valid_map1.cub

bonus: ${OBJS_B}
	@$(MAKE) -C ./utils/libft
	@$(MAKE) -s -C ./utils/MLX

ifeq ($(OS),Darwin)
		@${CC} ${FLAGS} ${OBJS_B} ${LIBS} ${FRAMEWORK} -o ${NAME_B}
endif

ifeq ($(OS),Linux)
		@${CC} ${FLAGS} ${OBJS} ./utils/MLX/libmlx42.a ./utils/libft/libft.a -lglfw -lm -o ${NAME_B}
endif

re: fclean all

.PHONY: clean fclean re all
