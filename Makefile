# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:03:38 by vdelafos          #+#    #+#              #
#    Updated: 2023/05/03 18:40:37 by vdelafos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	game/game_loop.c \
			game/player_move.c \
			game/handle_keyboard.c \
			parsing/parsing.c \
			parsing/init_structures.c \
			parsing/read_map_info.c \
			parsing/analyse_lines.c \
			parsing/find_player_pos.c \
			parsing/check_map.c \
			parsing/convert_colors.c \
			parsing/create_texture_map_screen.c \
			raycasting/raycasting.c \
			raycasting/get_diag_dist.c \
			raycasting/get_ray_dist.c \
			raycasting/display_textures.c \
			raycasting/cast_ray.c \
			raycasting/check_wall.c \
			utils/utils.c \
			utils/draw_shapes.c \
			utils/pixel_put_to_image.c 
			

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

MLX		=	-Lmlx -lmlx -framework OpenGL -framework AppKit -O3

RM		=	rm -rf

NAME	=	Cub3D

LIBFT	=	Libft/libft.a

MLX_AR	=	mlx/libmlx.a

GREEN	= \033[32m

YELLOW	= \033[33m

WHITE	= \033[37m

#rules

all : $(NAME)

.c.o:	
		@echo "${WHITE}Compiling object $<"
		@${CC} ${CFLAGS} -Imlx -c $< -o ${<:.c=.o}
		@tput cuu1 && tput dl1

$(NAME) : $(MLX_AR) $(LIBFT) $(OBJS)
			@echo "${GREEN}MLX OK"
			@echo "${GREEN}Libft OK"
			@echo "${GREEN}Objects OK"
			@echo "${WHITE}Compiling Cub3D..."
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX} -o ${NAME}
			@tput cuu1 && tput dl1
			@echo "${GREEN}Cub3D OK${WHITE}"

$(LIBFT) :
			@echo "${WHITE}Compiling Libft..."
			@tput cuu1 && tput dl1
			@make -s -C Libft

$(MLX_AR) :
			@echo "${WHITE}Compiling MLX..."
			@tput cuu1 && tput dl1
			@make -s -C mlx

clean :
	@echo "${WHITE}Cleaning objects..."
	@tput cuu1 && tput dl1
	@$(RM) $(OBJS)
	@echo "${YELLOW}Objects cleaned"
	@echo "${WHITE}Cleaning Libft..."
	@tput cuu1 && tput dl1
	@make fclean -C Libft 
	@echo "${YELLOW}Libft cleaned${WHITE}"
	@echo "${WHITE}Cleaning MLX..."
	@tput cuu1 && tput dl1
	@make clean -C mlx 
	@echo "${YELLOW}MLX cleaned${WHITE}"


fclean : clean
		@echo "${WHITE}Cleaning Cub3D"
		@tput cuu1 && tput dl1
		@$(RM) $(NAME)
		@echo "${YELLOW}Cub3D Cleaned${WHITE}"

re : fclean all
