#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * toFindP - a function to find the smallest positive divisor of a number > 1
 * @num: the number to find the smallest divisor for
 * Return: the smallest divisor greater than 1 if it exists,
 * 0 if num is less than or equal to 2
 *
 **/

int toFindP(long int num)
{
	int i;

	if (num <= 2)
		return (0);

	i = 2;
	while (i <= num)
	{
		if ((num % i) == 0)
			return (i);
		i++;
	}
	return (num);
}

/**
 * toFindQ - a function to find the quotient when a number
 * is divided by its smallest positive divisor greater than 1
 *
 * @num: the number to find the quotient for
 * @p: the smallest divisor
 * Return: the quotient when num is divided by its smallest positive
 * divisor reater than 1, If num is less than or equal to 2, returns num.
 *
 **/

int toFindQ(long int num, int p)
{
	if (num <= 2)
		return (num);

	return (num / p);
}

/**
 * main- the entry point of the program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 success
 *
 **/

int main(int argc, char *argv[])
{
	int p, q;
	ssize_t nread;
	long int n;
	FILE *fptr;
	char *line = NULL;
	size_t len = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		fprintf(stdout, " Unable to Open File: %s\n", argv[1]);
		return (EXIT_SUCCESS);
	}
	while ((nread = getline(&line, &len, fptr)) != -1)
	{
		char *token = NULL, *delim = "\n";

		token = strtok(line, delim);
		while (token != NULL)
		{
			n = atoll(token);
			p = toFindP(n);
			q = toFindQ(n, p);
			fprintf(stdout, "%ld=%d*%d\n", n, q, p);
			token = strtok(NULL, delim);
		}
	}
	if (nread == -1)
	{
		free(line);
		exit(EXIT_FAILURE);
	}
	free(line);
	fclose(fptr);
	return (EXIT_SUCCESS);
}
