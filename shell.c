#include "main.h"

/**
 * execute - executes a program passed to it
 * @argv: the string of command and parameters
 *
 * Return: void
 */
void execute(char **argv)
{
	int status = 0, stat;
	pid_t child_pid;

	status = access(argv[0], F_OK);
	if (status == -1)
	{
		perror("No such file or directory\n");
		return;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
	perror("Error: running command\n");
	return;
	}
	if (child_pid == 0)
	{
		argv[1] = NULL;
		execve(*argv, argv, NULL);
	}
	else
		wait(&stat);
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
	int i = 0, status;

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
