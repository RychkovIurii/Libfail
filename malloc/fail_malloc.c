/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:37:45 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:25:19 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailmalloc.so fail_malloc.c

Preload the library and run your program:
LD_PRELOAD=./libfailmalloc.so ./your_program

*/

void	*malloc(size_t size)
{
	return (NULL); // Always fail
}

/* 
static int	fail_after = 3; // Fail after 3 successful allocations
static int	allocation_count = 0;

void	*malloc(size_t size)
{
	allocation_count++;
	if (allocation_count > fail_after)
	{
		return NULL; // Simulate failure
	}
	return __libc_malloc(size); // Use the original malloc
} */
