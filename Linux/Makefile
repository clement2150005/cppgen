NAMES    = cppgen cppclass
CC       = cc
SRCS     = cppgen.c cppclass.c
OBJS     = $(SRCS:.c=.o)
CPPGEN_PATH = $(shell pwd)
CFLAGS   = -Wall -Wextra -Werror -DCPPGEN_PATH=\"$(CPPGEN_PATH)\"
LDFLAGS  = -lncurses

GREEN    = \033[0;32m
YELLOW   = \033[1;33m
RESET    = \033[0m

all: $(NAMES) alias

$(NAMES): %: %.o
	$(CC) $< -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAMES)

re: fclean all

alias:
	@ADDED=0; \
	for name in $(NAMES); do \
		ALIAS_LINE="alias $$name='$(CPPGEN_PATH)/$$name'"; \
		for file in $$HOME/.zshrc $$HOME/.bashrc; do \
			if [ -f $$file ]; then \
				if ! grep -qxF "$$ALIAS_LINE" $$file; then \
					echo "$$ALIAS_LINE" >> $$file; \
					ADDED=1; \
				fi; \
			fi; \
		done; \
	done; \
	if [ $$ADDED -eq 1 ]; then \
		printf "$(GREEN)✔ Aliases added to your shell config.$(RESET)\n"; \
		printf "$(YELLOW)➡ Run: source ~/.zshrc or source ~/.bashrc$(RESET)\n"; \
		printf "$(YELLOW)➡ Then use the commands: cppgen / cppclass$(RESET)\n"; \
	else \
		printf "$(GREEN)✔ Aliases already present. You can use: cppgen / cppclass$(RESET)\n"; \
	fi

.PHONY: all clean fclean re alias
