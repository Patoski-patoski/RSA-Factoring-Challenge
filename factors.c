#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/**
 * toFindP - a function to find the smallest positive divisor of a number > 1
 * @num: the number to find the smallest divisor for
 * Return: the smallest divisor greater than 1 if it exists,
 * 0 if num is less than or equal to 2
 *
 **/

int toFindP(long long int num)
{
	int i = 2;

	if (num <= i)
		return (0);

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
 * Return: the quotient when num is divided by its smallest positive
 * divisor reater than 1, If num is less than or equal to 2, returns num.
 *
 **/

int toFindQ(long int num)
{
	int p = toFindP(num);
	int q = num / p;

	return (q);
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
	(void)argc;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	FILE *fptr;
	long int n;
	int p, q;

	fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		fprintf(stdout, " Unable to Open File\n");
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, fptr)) != -1)
	{
		char *token = NULL;
		char *delim = "\n";

		token = strtok(line, delim);
		while (token != NULL)
		{
			n = atoll(token);
			p = toFindP(n);
			q = toFindQ(n);

			fprintf(stdout, "%ld = %d * %d\n", n, q, p);
			token = strtok(NULL, delim);
		}
	}

	puts("");
	fclose(fptr);
	free(line);
	return (0);
}
