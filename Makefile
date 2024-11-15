# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 11:23:50 by rcesar-d          #+#    #+#              #
#    Updated: 2024/11/15 14:43:04 by rcesar-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			=	server
CLIENT			=	client
SERVER_BONUS	=	server_bonus
CLIENT_BONUS	=	client_bonus

INC		=	inc/
SRC		=	src/
OBJ		=	obj/
LIBFT	=	./libft/libft.a

CC		=	@cc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f

SERVER_SRC			=	$(SRC)server.c
CLIENT_SRC			=	$(SRC)client.c
SERVER_BONUS_SRC	=	$(SRC)server_bonus.c
CLIENT_BONUS_SRC	=	$(SRC)client_bonus.c

SERVER_OBJ			=	$(OBJ)server.o
CLIENT_OBJ			=	$(OBJ)client.o
SERVER_BONUS_OBJ	=	$(OBJ)server_bonus.o
CLIENT_BONUS_OBJ	=	$(OBJ)client_bonus.o

all:		$(CLIENT) $(SERVER)

bonus:		$(CLIENT_BONUS) $(SERVER_BONUS)

$(LIBFT):
			@make -s -C ./libft

$(SERVER):	$(SERVER_OBJ) $(LIBFT)
			@echo "\033[31mCompiling server...\033[0m"
			$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)
			@echo "\033[32mServer compiled successfully\033[0m"

$(SERVER_BONUS):	$(SERVER_BONUS_OBJ) $(LIBFT)
			@echo "\033[31mCompiling server_bonus...\033[0m"
			$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(LIBFT) -o $(SERVER_BONUS)
			@echo "\033[32mServer_bonus compiled successfully\033[0m"

$(CLIENT):	$(CLIENT_OBJ) $(LIBFT)
			@echo "\033[31mCompiling client...\033[0m"
			$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)
			@echo "\033[32mClient compiled successfully\033[0m"

$(CLIENT_BONUS):	$(CLIENT_BONUS_OBJ) $(LIBFT)
			@echo "\033[31mCompiling client_bonus...\033[0m"
			$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LIBFT) -o $(CLIENT_BONUS)
			@echo "\033[32mClient_bonus compiled successfully\033[0m"

$(SERVER_OBJ):	$(SERVER_SRC)
			@mkdir -p $(OBJ)
			$(CC) $(CFLAGS) -I$(INC) -c $(SERVER_SRC) -o $(SERVER_OBJ)

$(SERVER_BONUS_OBJ):	$(SERVER_BONUS_SRC)
			@mkdir -p $(OBJ)
			$(CC) $(CFLAGS) -I$(INC) -c $(SERVER_BONUS_SRC) -o $(SERVER_BONUS_OBJ)

$(CLIENT_OBJ):	$(CLIENT_SRC)
			@mkdir -p $(OBJ)
			$(CC) $(CFLAGS) -I$(INC) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

$(CLIENT_BONUS_OBJ):	$(CLIENT_BONUS_SRC)
			@mkdir -p $(OBJ)
			$(CC) $(CFLAGS) -I$(INC) -c $(CLIENT_BONUS_SRC) -o $(CLIENT_BONUS_OBJ)

clean:
			@$(RM) -r $(OBJ)
			@echo "\033[31mCleaning object files...\033[0m"
			@make -s clean -C ./libft
			@echo "\033[32mDone!\033[0m"

fclean:		clean
			@$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
			@echo "\033[31mCleaning executables...\033[0m"
			@make -s fclean -C ./libft
			@echo "\033[32mDone!\033[0m"

re:			fclean all
			@echo "\033[31mRebuilding...\033[0m"
			@echo "\033[32mDone!\033[0m"