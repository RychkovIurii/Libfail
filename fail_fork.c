/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:23:47 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:35:41 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailfork.so fail_fork.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailfork.so ./your_program

Simulates a failure every other call.

*/

static int	fork_count = 0;

pid_t	fork(void)
{
	fork_count++;
	if (fork_count % 2 == 0)
	{
		errno = EAGAIN; // Simulate process limit reached
		return (-1);
	}

	// Call the original fork
	pid_t (*original_fork)(void);
	original_fork = dlsym(RTLD_NEXT, "fork");
	return (original_fork());
}
