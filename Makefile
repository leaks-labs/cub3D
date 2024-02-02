################################################################################
#                                 CONFIG                                       #
################################################################################

.DELETE_ON_ERROR:
.SILENT:

NAME:=	cub3D

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS= includes lib/mlx_opengl

LDLIBS= -lmlx -framework OpenGL -framework Appkit
LIB_DIRS= lib/mlx_opengl
MLX=	lib/mlx_opengl/libmlx.a

ifeq (${shell uname}, Linux)
		LDLIBS= -lmlx_Linux -lXext -lX11 -lm -lz
		LIB_DIRS= lib/mlx_linux /usr/lib
		INC_DIRS= includes lib/mlx_linux /usr/include
		MLX= lib/mlx_linux/libmlx.a
endif

CC:=	clang

CFLAGS=	-Wall -Wextra -Werror

CFLAGS+=	-Wconversion			\
			-Wdouble-promotion		\
			-Wfloat-equal			\
			-Wformat=2				\
			-Winit-self				\
			-fno-common				\
			-Wshadow				\
			-Wundef					\
			-Wunused-macros			\
			-Wwrite-strings			\
			-Wmissing-prototypes	\
			-Wmissing-declarations	\
			-O3

ADDITIONAL_CPPFLAGS=
ADDITIONAL_LDFLAGS=

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

EXT:=	.c

MAIN:=	main

SRCS_FILES:=	game/rendering/draw_environment	\
				game/rendering/draw_wall		\
				game/rendering/drawing			\
				game/rendering/render			\
				game/game_check_grid			\
				game/game_destroy				\
				game/game_event					\
				game/game_init					\
				game/game_mini_map				\
				game/game_movement				\
				game/game_rotation				\
				game/run						\
				libx/libx_destroy				\
				libx/libx_exception				\
				libx/libx_init					\
				libx/libx_key_handler			\
				libx/libx_mouse_handler			\
				libx/libx_new_image				\
				libx/libx_print_screen			\
				map/map_destroy					\
				map/map_exception				\
				map/map_format					\
				map/map_init					\
				map/map_parse					\
				map/map_requirement				\
				map/map_set_requirement			\
				map/map_utils					\
				map/map_verify					\
				utils/ft_calloc					\
				utils/ft_dptrlen				\
				utils/ft_freef					\
				utils/ft_get_next_line			\
				utils/ft_join					\
				utils/ft_memcpy					\
				utils/ft_memset					\
				utils/ft_putendl_fd				\
				utils/ft_putstr_fd				\
				utils/ft_split					\
				utils/ft_strchr					\
				utils/ft_strcmp					\
				utils/ft_strdup					\
				utils/ft_strlcat				\
				utils/ft_strlcpy				\
				utils/ft_strlen					\
				utils/ft_strncmp				\
				utils/ft_strtoi					\
				utils/ft_substr

################################################################################
#                                 VAR FORMATING                                #
################################################################################

MAKEFILE_NAME:= ${lastword ${MAKEFILE_LIST}}

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${MAIN} ${SRCS_FILES}}}

OBJS_DIR:= ${BUILD_DIR}/objs
OBJS:=	${SRCS:${SRCS_DIR}/%${EXT}=${OBJS_DIR}/%.o}

DEPS_DIR:= ${BUILD_DIR}/deps
DEPS:=	${OBJS:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}

CPPFLAGS= ${addprefix -I,${INC_DIRS}} -MMD -MP -MF ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}
CPPFLAGS+= ${ADDITIONAL_CPPFLAGS}

LDFLAGS= ${addprefix -L,${LIB_DIRS}}
LDFLAGS+= ${ADDITIONAL_LDFLAGS}

RM:=	rm -rf

COLOR_GREEN := \033[32m
COLOR_RESET := \033[0m

################################################################################
#                                 MAKEFILE RULES                               #
################################################################################

all: ${NAME}

${NAME}: ${OBJS} ${MLX}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@
	echo "${COLOR_GREEN}Compilation completed.${COLOR_RESET}"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%${EXT} ${MAKEFILE_NAME}
	mkdir -p ${dir $@}
	mkdir -p ${dir ${@:${OBJS_DIR}/%.o=${DEPS_DIR}/%.d}}
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@
    
${MLX}:
	${MAKE} -C ${dir ${MLX}}

clean:
	${RM} ${BUILD_DIR}
	echo "${COLOR_GREEN}Objects cleaned.${COLOR_RESET}"

fclean: clean
	${MAKE} clean -C ${dir ${MLX}}
	${RM} ${NAME}
	echo "${COLOR_GREEN}Executables cleaned.${COLOR_RESET}"

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}
