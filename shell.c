#include "main.h"

/**
 * execute - executes a program passed to it
 * @argv: the string of command and parameters
 * @progname: program name
 *
 * Return: void
 */
void execute(char **argv, char *progname)
{
	int status = 0, stat;
	char *file;
	pid_t child_pid;

	status = access(argv[0], F_OK);
	if (status == -1)
	{
		file = search_path(argv[0]);
		if (file == NULL)
		{
			write(STDOUT_FILENO, progname, 8);
			write(STDOUT_FILENO, ": No such file or directory\n",
					30);
			return;
		}
		argv[0] = file;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: running command\n");
		return;
	}
	if (child_pid == 0)
	{
		execve(argv[0], argv, NULL);
	}
	else
		wait(&stat);
}

/**
 * main - Entry point of application
 * @ac: number of commandline args
 * @arv: array of command line
 *
 * Return: 0 sucess
 */
int main(__attribute__((unused)) int ac, char *arv[])
{
	char *prompt = NULL, *a, **av;
	size_t n = 0;
	ssize_t read;
	int status = 0;

	do {
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		read = getline(&prompt, &n, stdin);
		if (read == -1)
			break;
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
					execute(av, arv[0]);
				else if (status == 1)
					break;
			}
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		n = 0;
		free(prompt);
		free(av);
	} while (1);
	free(prompt);
	if (status != 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
