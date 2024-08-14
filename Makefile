NAME = philosophers
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = $(wildcard source/*.c) $(wildcard libft/*.c)
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/source/%.o: source/%.c | $(OBJ_DIR)/source
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/libft/%.o: libft/%.c | $(OBJ_DIR)/libft
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/source $(OBJ_DIR)/libft

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
