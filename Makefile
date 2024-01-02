.DELETE_ON_ERROR:
.SILENT:

COLOR_GREEN := \033[32m
COLOR_RESET := \033[0m

NAME:=	cub3d

SRCS_DIR:= sources
BUILD_DIR:= build
INC_DIRS= includes

CC:=	clang

CFLAGS=	-Wall -Wextra -Werror

CFLAGS+=	-Wconversion 			\
			-Wdouble-promotion		\
			-Wfloat-equal 			\
			-Wformat=2 				\
			-Winit-self 			\
			-fno-common 			\
			-Wshadow 				\
			-Wundef 				\
			-Wunused-macros 		\
			-Wmissing-prototypes 	\
			-Wmissing-declarations	\
			-O3

ifeq (${shell uname}, Darwin)
	MLX_OBJS:= -I${INC_DIRS}/mlx
	MLX_COMP:= -L${INC_DIRS}/mlx -lmlx -framework OpenGL -framework AppKit
endif

MLX_OBJS:= -I/usr/include -I${INC_DIRS}/mlx_linux
MLX_COMP:= -L${INC_DIRS}/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

EXT:=	.c

MAIN:=	main

SRCS_FILES:=	game/game_destroy		\
				game/game_event			\
				game/game_init			\
				game/render				\
				game/run				\
				libx/libx_event			\
				libx/libx_destroy		\
				libx/libx_exception		\
				libx/libx_init			\
				map/map_init			\
				map/map_destroy			\
				utils/ft_calloc			\
				utils/ft_freef			\
				utils/ft_isalnum		\
				utils/ft_isalpha		\
				utils/ft_isdigit		\
				utils/ft_isspace		\
				utils/ft_join			\
				utils/ft_memcpy			\
				utils/ft_putendl_fd		\
				utils/ft_putstr_fd		\
				utils/ft_strchr			\
				utils/ft_strcmp			\
				utils/ft_strdup			\
				utils/ft_strlen			\
				utils/ft_strncmp		\
				utils/ft_strndup		\
				utils/ft_strnstr		\
				utils/ft_substr

MAKEFILE_NAME:= ${lastword ${MAKEFILE_LIST}}

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${MAIN} ${SRCS_FILES}}}

OBJS_DIR:= ${BUILD_DIR}/objs
OBJS:=	${SRCS:${SRCS_DIR}/%${EXT}=${OBJS_DIR}/%.o}

DEPS_DIR:= ${BUILD_DIR}/deps
DEPS:=	${OBJS:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}

CPPFLAGS= ${addprefix -I,${INC_DIRS}} -MMD -MP -MF ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}

LDFLAGS= ${addprefix -L,${LIB_DIRS}}

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${OBJS} ${MLX_COMP} -o $@
	echo "${COLOR_GREEN}Compilation completed.${COLOR_RESET}"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%${EXT} ${MAKEFILE_NAME}
	mkdir -p ${dir $@}
	mkdir -p ${dir ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}}
	${CC} ${CPPFLAGS} ${CFLAGS} ${MLX_OBJS} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}
	echo "${COLOR_GREEN}Objects cleaned.${COLOR_RESET}"

fclean: clean
	${RM} ${NAME}
	echo "${COLOR_GREEN}Executables cleaned.${COLOR_RESET}"

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}