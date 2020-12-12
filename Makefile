NAME = program
GREEN = \033[32;1;1m
YELLOW = \033[33;1;1m
RESET = \033[0m

FILES = src/main.c src/stack.c src/trie.c src/utils.c  src/dawg.c src/construct.c
OBJ = $(FILES:.c=.o)

all: $(NAME) 

$(NAME):  $(OBJ)
	@echo "$(YELLOW) Compiling... $(RESET)"
	@gcc -Wall -Wextra -Werror $(OBJ) -o $(NAME)
	@make clean
	@echo "Program name: $(GREEN) $@ $(RESET)"

$(OBJ): %.o : %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	@echo "$(YELLOW) Cleaning Objects... $(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN) Done. $(RESET)"
	@echo ""

fclean: clean
	@echo "$(YELLOW) Cleaning Project... $(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN) Done. $(RESET)"
	@echo ""

re: fclean  $(NAME)