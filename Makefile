# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ahorling <ahorling@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/20 16:42:04 by ahorling      #+#    #+#                  #
#    Updated: 2022/10/14 21:04:25 by ahorling      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

############## COLOUR CODES ##########

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

############## CONSTANTS #############

NAME := fractol
CC := gcc
CFLAGS := -Wall -Wextra -Werror

############### SOURCES ##############

SOURCES 	:=	main.c\
				Mandelbrot.c\
				Julia.c\
				Ship.c\
				hooks.c\
				shared.c\
				colours.c\
				zoom.c\

LIBRARIES	:=	./libraries/libft/libft.a\
				./libraries/MLX42/libmlx42.a\
				
HEADERS		:=	-I ./includes -I $(MLX)/include/MLX42 -I $(LIBFT)/includes			
SOURCE_DIR 	:=	./sources
INCLUDE_DIR	:= 	./includes
OBJECT_DIR	:=	./objects
MLX			:=	./libraries/MLX42
LIBFT		:=	./libraries/libft
OBJECTS 	:= 	$(addprefix $(OBJECT_DIR)/, $(SOURCES:.c=.o))

############### MESSAGES ########

MESSAGE		:=	"Making $(NAME)"
MESSAGE_FIN	:=	"MAKE COMPLETE, NO ERRORS"
MESSAGE_RM	:=	"OBJECTS CLEANED"
MESSAGE_FRM	:=	"EVERYTHING CLEANED"
MESSAGE_LIB	:=	"LIBRARIES READY"

############### RUNNING ##############

all: libraries $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(LIBRARIES) -o $@ $^ $(HEADERS) -L$(shell brew --prefix glfw)/lib -lglfw
	@echo "$(GREEN)$(BOLD)$(MESSAGE_FIN)$(RESET)"

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< -O3

run:
	make && ./$(NAME)

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C $(MLX)
	@echo "$(RED)$(MESSAGE_RM)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@if [ -d "$(OBJECT_DIR)" ]; then rm -d $(OBJECT_DIR); fi
	@echo "$(RED)$(MESSAGE_FRM)$(RESET)"

libraries:
	@$(MAKE) -s -C $(LIBFT)
	@$(MAKE) -s -C $(MLX)
	@echo "$(GREEN)$(MESSAGE_LIB)$(RESET)"

re: fclean all

.PHONY: all clean fclean re libraries
