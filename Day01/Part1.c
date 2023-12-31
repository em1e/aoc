/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:53:34 by vkettune          #+#    #+#             */
/*   Updated: 2023/12/01 20:24:03 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	combine(int first, int last)
{
	int	num = (first * 10) + last;
	return (num);
}

int	end(int j, char *line)
{
	while (line[j] != '\n')
		j++;
	return (j);
}

int	*find_value(int argc, char *argv[])
{
	int	j, sum = 0;
	int	first = -1;
	int	last = -1;
	int	i = 0;
	int	*res;

	while (argv[i] != NULL && i < argc) // while there are lines to decode
	{
		FILE *file = fopen("input.txt", "r");
		char line[1000];

		if (file == NULL)
		{
			printf("Failed to open file");
			i++;
			continue;
		}
		while (fgets(line, sizeof(line), file) != NULL)
		{
			printf("%s", line);
			j = 0;
			while (first < 0 && line[j] != '\0') // find first num
			{
				if (line[j] >= '0' && line[j] <= '9')
					first = line[j] - '0';
				else
					j++;
			}
			printf("first: %d\n", first);
			j = end(j, line) - 1;
			while (last < 0 && j >= 0) // find last num
			{
				if (line[j] >= '0' && line[j] <= '9')
				{
					last = line[j] - '0';
					break ;
				}
				else
					j--;
			}
			printf("Last: %d\n", last);
			if (first >= 0 && last >= 0)
				sum += combine(first, last); // add num from line to the final sum
			first = -1;
			last = -1;
			printf("Sum: %d\n", sum);
		}
		fclose(file); // close the file
		i++;
	}
	if (!(res = (int *)malloc(sizeof(int))))
		return (NULL);
	*res = sum;
	return (res);
}

int	main(int argc, char *argv[])
{
	int	*sum = find_value(argc, argv);
	printf("The sum of all calibration values is %d\n", *sum);
	free(sum);
	return (0);
}
