NAME	= cppgen
CC		= cc
SRC		= cppgen.c
OBJ		= $(SRC:.c=.o)
CPPGEN_PATH = $(shell pwd)
CFLAGS = -Wall -Wextra -Werror -DCPPGEN_PATH=\"$(CPPGEN_PATH)\"

GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0m

all: $(NAME) alias
	@:

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lncurses -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

alias:
	@ADDED=0; \
	ALIAS_LINE='alias cppgen=\"$(CPPGEN_PATH)/$(NAME)\"'; \
	for file in $$HOME/.zshrc $$HOME/.bashrc; do \
		if [ -f $$file ]; then \
			if ! grep -qxF "$$ALIAS_LINE" $$file; then \
				echo "$$ALIAS_LINE" >> $$file; \
				ADDED=1; \
			fi; \
		fi; \
	done; \
	if [ $$ADDED -eq 1 ]; then \
		printf "$(GREEN)✔ Alias added to your shell config.$(RESET)\n"; \
		printf "$(YELLOW)➡ Run: source ~/.zshrc or source ~/.bashrc$(RESET)\n"; \
		printf "$(YELLOW)➡ Then use the command: cppgen $(RESET)\n"; \
	else \
		printf "$(GREEN)✔ Alias already present. You can use: cppgen folder_name$(RESET)\n"; \
	fi
