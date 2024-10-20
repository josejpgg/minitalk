LIBFT_NAME := libft.a
LIBFT_GH := https://github.com/josejpgg/libft_increment.git
LIBFT_PATH := ./lib/libft/
FLAGS = 
FLAGS = -Wall -Werror -Wextra
# FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
SOURCE := mt_client.c mt_server.c
COMPILE := ${SOURCE:.c=.o}
SOURCE_BONUS := mt_client_bonus.c mt_server_bonus.c
COMPILE_BONUS := ${SOURCE_BONUS:.c=.o}

all: lib client server

%.o: %.c
	cc $(FLAGS) -c $< -o $@

client: $(COMPILE)
	cc mt_client.o $(LIBFT_NAME) -o $@

server: $(COMPILE)
	cc mt_server.o $(LIBFT_NAME) -o $@

bonus: lib $(COMPILE_BONUS)
	cc mt_client_bonus.o $(LIBFT_NAME) -o client
	cc mt_server_bonus.o $(LIBFT_NAME) -o server

lib:
	@make -C $(LIBFT_PATH)
	@mv $(LIBFT_PATH)/$(LIBFT_NAME) .

clean:
	@rm -rf $(COMPILE)
	@rm -rf $(COMPILE_BONUS)
	@make clean -C $(LIBFT_PATH)

fclean:
	@rm -rf $(LIBFT_NAME)
	@rm -rf client server
	@make fclean -C $(LIBFT_PATH)

re: fclean clean lib all

libft:
	@if [ ! -d "./lib" ]; then \
		mkdir -p lib; \
	fi
	@if [ -d "./lib/libft" ]; then \
		rm -rf ./lib/libft; \
	fi
	git clone $(LIBFT_GH) $(LIBFT_PATH)

leaksMac:
	export MallocStackLogging=1
	leaks --atExit --list -- ./client 85510 "99 0 25 -38 10 7 42"

leaksCampus:
	valgrind --leak-check=yes ./client 85510 "99 0 25 -38 10 7 42"

.PHONY: all clean fclean re lib libft leaksMac leaksCampus
