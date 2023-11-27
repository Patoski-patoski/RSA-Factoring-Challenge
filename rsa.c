#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * gcd-  function calculates the Greatest Common Divisor (GCD) of two numbers
 * @a: the first number number
 * @b: the second
 *
 * Return: the prime number
 **/

long int gcd(long int a, long int b)
{
	while (b != 0)
	{
		long int temp;

		temp = b;
		b = a % b;
		a = temp;
	}
	return (a);
}

/**
 * pollardsRhoFormula- a function that  uses Pollard's rho algorithm
 * to find a non-trivial factor of n.
 * It then calculates the other factor by dividing n by the found factor.
 *
 * @n: the number
 * Return: the non-trivial factor of n found by the algorithm.
 *
 **/

long int pollardsRhoFormula(long int n)
{
	long int x = 2, y = 2, d = 1;
	long int c = 1;

	while (d == 1)
	{
		x = (x * x + c) % n;
		y = (y * y + c) % n;
		y = (y * y + c) % n;

		d = gcd(abs(x - y), n);
	}
	return (d);
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
	long int p, q;
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
			p = pollardsRhoFormula(n);
			q = n / p;
			fprintf(stdout, "%ld=%ld*%ld\n", n, p, q);
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
