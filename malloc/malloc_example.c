/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:30:08 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:47:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int i;
	int	*arr;

	i = 0;
	arr = malloc(5 * sizeof(int));
	if (!arr)
	{
		printf("malloc failed\n");
		return (1);
	}
	while(i < 5)
	{
		printf("%d ", arr[i] = i + 1);
		i++;
	}
	free(arr);
	return (0);
}
