#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>

#ifndef CPPGEN_PATH
# error "Define CPPGEN_PATH with -DCPPGEN_PATH=\\\"/path/to/cppgen\\\""
#endif

char *ft_substring(const char *s, int start, int end) {
	int i = 0;
	char *substr;

	if (end < start || start < 0 || end < 0)
		return NULL;
	substr = malloc(end - start + 1);
	if (!substr)
		return NULL;
	while (start < end)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return substr;
}

char **ft_split(const char *s, char c) {
	int j = 0, count = 0;
	char **array;

	for (int k = 0; s[k];) {
		while (s[k] == c) k++;
		if (s[k]) count++;
		while (s[k] && s[k] != c) k++;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return NULL;
	for (int k = 0; j < count;) {
		while (s[k] == c) k++;
		int start = k;
		while (s[k] && s[k] != c) k++;
		array[j++] = ft_substring(s, start, k);
	}
	array[j] = NULL;
	return array;
}

char *sanitize_string(const char *input) {
	while (isspace(*input))
		input++;
	int len = strlen(input);
	while (len > 0 && isspace(input[len - 1]))
		len--;
	char *result = malloc(len * 3 + 1);
	if (!result)
		return NULL;
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (input[i] == ' ' || input[i] == '\t') {
			result[j++] = '\\';
			result[j++] = '\\';
		}
		result[j++] = input[i];
	}
	result[j] = '\0';
	return result;
}

char *strjoin_multi(const char *first, va_list args) {
	va_list copy;
	const char *s;
	int total_len = strlen(first);
	va_copy(copy, args);
	while ((s = va_arg(copy, const char *)))
		total_len += strlen(s);
	va_end(copy);

	char *result = malloc(total_len + 1);
	if (!result)
		return NULL;

	result[0] = '\0';
	strcat(result, first);
	while ((s = va_arg(args, const char *)))
		strcat(result, s);
	return result;
}

int system_multistr(const char *first, ...) {
	va_list args;
	char *cmd;

	va_start(args, first);
	cmd = strjoin_multi(first, args);
	va_end(args);

	if (!cmd)
		return -1;

	int ret = system(cmd);
	free(cmd);
	return ret;
}

int main(int argc, char **argv) {
	char user_input[1024];

	if (argc != 2) {
		printf("Usage: cppgen folder_name\n");
		return 1;
	}

	initscr();
	cbreak();
	noecho();
	clear();

	mkdir(argv[1], 0755);
	chdir(argv[1]);
	mkdir("src", 0755);
	mkdir("include", 0755);
	system_multistr("cp ", CPPGEN_PATH, "/resources/Makefile ./", NULL);
	system_multistr("cp ", CPPGEN_PATH, "/resources/main.cpp ./src", NULL);

	printw("Enter program name\n> ");
	echo();
	getnstr(user_input, sizeof(user_input) - 1);
	clear();
	noecho();

	char *program_name = sanitize_string(user_input);
	system_multistr("sed -i 's/PROGRAM_NAME/", program_name, "/' Makefile", NULL);
	free(program_name);

	printw("Enter class names (space-separated) or leave blank to skip\n> ");
	echo();
	getnstr(user_input, sizeof(user_input) - 1);
	clear();
	noecho();

	int only_spaces = 1;
	for (int i = 0; user_input[i]; i++)
		if (!isspace(user_input[i]))
			only_spaces = 0;
	if (only_spaces) {
		endwin();
		return 0;
	}

	char **classes = ft_split(user_input, ' ');
	for (int i = 0; classes[i]; i++) {
		system_multistr("cp ", CPPGEN_PATH, "/resources/Class.cpp ./src", NULL);
		system_multistr("cp ", CPPGEN_PATH, "/resources/Class.hpp ./include", NULL);
		classes[i][0] = toupper(classes[i][0]);
		system_multistr("mv ./include/Class.hpp ./include/", classes[i], ".hpp", NULL);
		system_multistr("mv ./src/Class.cpp ./src/", classes[i], ".cpp", NULL);
		system_multistr("sed -i 's/Class/", classes[i], "/g' ./src/", classes[i], ".cpp", NULL);
		system_multistr("sed -i 's/Class/", classes[i], "/g' ./include/", classes[i], ".hpp", NULL);
	}

	refresh();
	endwin();
	return 0;
}
