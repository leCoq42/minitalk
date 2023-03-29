# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mhaan <mhaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/17 11:52:43 by mhaan         #+#    #+#                  #
#    Updated: 2023/03/29 17:08:51 by mhaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#GENERAL VARIABLES
NAME_SERVER := server
NAME_CLIENT := client
NAME_SERVER_BONUS := server_bonus
NAME_CLIENT_BONUS := client_bonus

RM := /bin/rm -rf

#COMPILATION VARIABLES
CFLAGS ?= -Wall -Wextra -Werror
AR := ar -crs

#DIRS AND FILES
INC_DIRS		:=	./includes ./libft_ext/includes
INCLUDES		:=	$(foreach D,$(INC_DIRS),-I$(D))
INC_FILES		:=	./includes/mini_talk.h ./includes/mini_talk_bonus.h

SRC_DIR			:=	./src
OBJ_DIR			:=	./obj

SERVER_C		:=	mt_server.c mt_utils.c
SERVER_C_BONUS	:=	mt_server_bonus.c mt_utils_bonus.c
CLIENT_C		:=	mt_client.c mt_utils.c
CLIENT_C_BONUS	:=	mt_client_bonus.c mt_utils_bonus.c

SERVER_OBJ			:=	$(addprefix $(OBJ_DIR)/,$(SERVER_C:.c=.o))
SERVER_OBJ_BONUS	:=	$(addprefix $(OBJ_DIR)/,$(SERVER_C_BONUS:.c=.o))
CLIENT_OBJ			:=	$(addprefix $(OBJ_DIR)/,$(CLIENT_C:.c=.o))
CLIENT_OBJ_BONUS	:=	$(addprefix $(OBJ_DIR)/,$(CLIENT_C_BONUS:.c=.o))

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
		@$(RM) $(NAME_SERVER_BONUS)
		@$(RM) $(NAME_CLIENT)
		@$(RM) $(NAME_CLIENT_BONUS)
		@$(RM) $(LIBFT_AR)

re:
		@$(MAKE) fclean
		@$(MAKE) all

bonus:	$(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

#RULES:
$(NAME_CLIENT): $(CLIENT_OBJ) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(CLIENT_OBJ) $(LIBFT_AR)

$(NAME_SERVER): $(SERVER_OBJ) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SERVER_OBJ) $(LIBFT_AR)

$(NAME_CLIENT_BONUS): $(CLIENT_OBJ_BONUS) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(CLIENT_OBJ_BONUS) $(LIBFT_AR)

$(NAME_SERVER_BONUS): $(SERVER_OBJ_BONUS) $(LIBFT_AR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SERVER_OBJ_BONUS) $(LIBFT_AR)

$(LIBFT_AR):
		@$(MAKE) -C $(LIBFT_DIR) -j

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

#OTHER:
.PHONY:
		all client server clean fclean re bonus