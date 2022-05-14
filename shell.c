#include "main.h"

/**
 * execute - executes a program passed to it
 * @argv: the string of command and parameters
 *
 * Return: void
 */
void execute(char **argv)
{
	int status = 0;

	status = execve(argv[0], argv, NULL);
	if (status == -1)
		write(STDOUT_FILENO, "No such file or directory\n",
				26);
}

/**
 * main - Entry point of application
 *
 * Return: 0 sucess
 */
int main(void)
{
	char *prompt = NULL, *a, **av;
	size_t n = 0;
	ssize_t read;
	int i = 0;

	do {
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		read = getline(&prompt, &n, stdin);
		a = prompt;
		while (*a != '\n')
			a++;
		*a = '\0';
		av[0] = prompt;
		if (read != -1)
			execute(av);
		else
			write(STDOUT_FILENO, "\n", 1);
		free(prompt);
		n = 0;
	} while (1);
}
