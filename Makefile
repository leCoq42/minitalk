# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mhaan <mhaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/17 11:52:43 by mhaan         #+#    #+#                  #
#    Updated: 2023/03/17 11:57:43 by mhaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#GENERAL VARIABLES
NAME_SERVER := server
NAME_CLIENT := client

RM := /bin/rm -rf

#COMPILATION VARIABLES
CFLAGS ?= -Wall -Wextra -Werror
AR := ar -crs

#DIRS AND FILES
INC_DIRS	:=	./includes ./libft_ext/includes
INCLUDES	:=	$(foreach D,$(INC_DIRS),-I$(D))
INC_FILES	:=	./includes/mini_talk.h

SRC_DIR		:=	./src

SERVER_C	:=	mt_server.c
CLIENT_C	:=	mt_client.c

OBJ_DIR		:=	./obj
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(SERVER_C:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(CLIENT_C:.c=.o))

#DEPENDENCIES:
LIBFT_DIR := ./libft_ext
LIBFT_AR := $(LIBFT_DIR)/libft_ext.a

#RECIPES:
all:	$(NAME_SERVER) $(NAME_CLIENT)

clean:
		@$(RM) $(OBJ_DIR)
		@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
		@$(RM) $(NAME_SERVER)
		@$(RM) $(NAME_CLIENT)
		@$(RM) $(LIBFT_AR)

re:
		@$(MAKE) fclean
		@$(MAKE) all

bonus:	$(BONUS)

#RULES:
$(NAME): $(OBJS) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBFT_AR)

$(LIBFT_AR):
		@$(MAKE) -C $(LIBFT_DIR) -j

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

#OTHER:
.PHONY:
		all clean fclean re bonus