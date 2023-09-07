

NAME    = minishell
CC 		= gcc -Wall -Wextra -Werror -g3
CFLAGS 	= -I /inc/minishell.h

LIBFT  	= ./inc/libft/
LIBFLAGS = -lreadline
SRCS 	= $(wildcard ./src/*/*.c) 
OBJS 	= $(SRCS:.c=.o)
OBJS_T	= $(wildcard ./src/*/*.o)

SUBM_STATE := $(shell find inc/libft -type f)

#NC		:= \033[m
#RED 	:= \033[0;31m
#BLUE 	:= \033[0;34m
#PURPLE	:= \033[0;35m
#WHCOLOR	:= \033[0;40m
B_GREEN	:= \033[1;32m
GREEN 	:= \033[0;33m
B_BLUE 	:= \033[1;34m
B_RED	:= \033[1;31m

all: $(SUBM_FLAG) libft $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@echo "____!!!$(BLUE)----- Compiling Libft------$(NC)"
	@$(MAKE) -C $(LIBFT)
	@echo "Compilation of Libft:	\033[1;32mOK\033[m"


$(NAME): $(OBJS)  
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) $(LIBFT)libft.a  -o   $(NAME)
	@echo "$(B_BLUE) ~Compilation of minishell:	\033[1;32mSUCCESS\033[m"

clean:
	@echo "$(GREEN)♻️ ${B_GREEN} .....TRASHING ALL OBJECTS..... $(GREEN)♻️ "
	@rm -f $(OBJS_T)
	@$(MAKE) -C $(LIBFT) clean
#	@sleep 0.5
	@echo "$(B_RED)Done."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(GREEN)♻️ ${B_GREEN} .....cleaning the rest.....  $(GREEN)♻️ "
	@echo "$(B_RED)Done."
	@echo "$(GREEN)♻️ ${B_GREEN} !TOUT PROPRE! $(GREEN)♻️ "
		
re: fclean all

.phony: all libft clean fclean
