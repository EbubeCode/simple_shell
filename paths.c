#include "main.h"

/**
 * get_path - gets an array of the directories in path variable
 *
 * Return: duplicate of  PATH
 */
char *get_path(void)
{
	char *a;
	int i = 0;

	while (environ[i])
	{
		a = environ[i];
		if (*a == 'P' && a[1] == 'A' && a[2] == 'T' && a[3] == 'H' && a[4] == '=')
		{
			a += 5;
			return (_strdup(a));
		}
		else
			i++;
	}
	return (NULL);
}

/**
 * compare - compares the file name of files to if they are equall
 * @f1: first file
 * @f2: second file
 *
 * Return: 1 on successfull match else 0
 */
int compare(char *f1, char *f2)
{
	int i, j = 0;

	for (i = 0; f1[i] != '\0' && f2[j] != '\0'; i++)
	{
		if (f1[i] != f2[j++])
			return (0);
	}
	if (i != j || f1[i] != '\0' || f2[j] != '\0')
		return (0);
	return (1);
}

/**
 * search_path - searches the path variable for a file
 * @file: name of file to look for
 *
 * Return: full path of file
 */
char *search_path(char *file)
{
	char **args, *a;
	DIR *dir;
	struct dirent *entity;
	char *temp;
	int i;

	a = get_path();
	if (a != NULL)
	{
		args = split_command(a, ":");
		for (i = 0; args[i] != NULL; i++)
		{
			dir = opendir(args[i]);
			if (dir == NULL)
				continue;
			while ((entity = readdir(dir)) != NULL)
			{
				if (entity->d_type != DT_REG)
					continue;
				if (compare(entity->d_name, file))
				{
					closedir(dir);
					temp = str_concat("/", file);
					file = str_concat(args[i], temp);
					free(a);
					free(temp);
					free(args);
					return (file);
				}
			}
			closedir(dir);

		}
		free(a);
		free(args);
	}
	return (NULL);
}
