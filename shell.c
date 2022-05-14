#include "main.h"

/**
 * main - Entry point of application
 *
 * Return: 0 sucess
 */
int main(void)
{
	char *prompt = NULL;
	size_t n = 0;
	ssize_t read;

	do {
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		read = getline(&prompt, &n, stdin);
		if (read != -1)
			write(STDOUT_FILENO, prompt, read);
		else
			write(STDOUT_FILENO, "\n", 1);
	} while (1);
}
