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
	char *file = NULL;
	pid_t child_pid;

	status = access(argv[0], F_OK | X_OK);
	if (status == -1)
	{
		file = search_path(argv[0]);
		if (file != NULL)
			status = access(file, F_OK | X_OK);
		if (file == NULL || status == -1)
		{
			perror("Error");
			return;
		}
		argv[0] = file;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return;
	}
	if (child_pid == 0)
	{
		status = execve(argv[0], argv, NULL);
		if (status == -1)
			perror("Error");
	}
	else
	{
		wait(&stat);
		free(file);
	}
}

/**
 * main - Entry point of application
 *
 * Return: 0 sucess
 */
int main(void)
{
	char *prompt = NULL, *a = NULL, **av = NULL;
	size_t n = 0;
	ssize_t read;
	int status = 0, piped = 1;

	do {
		if (!isatty(STDIN_FILENO))
			piped = 0;
		else
			write(STDOUT_FILENO, "$ ", 2);
		read = getline(&prompt, &n, stdin);
		if (read == -1)
		{
			free(prompt);
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (prompt != NULL)
		{
			a = prompt;
			while (*a != '\n')
				a++;
			*a = '\0';
			av = split_command(prompt, " ");
			if (av != NULL)
			{
				status = handle_builtin(av);
				if (status == 0)
					execute(av);
				else if (status == 1)
					piped = 0;
			}
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		n = 0;
		free(prompt);
		free(av);
	} while (piped);
	return (0);
}
