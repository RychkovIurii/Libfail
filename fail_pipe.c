/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:26:39 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:38:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailpipe.so fail_pipe.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailpipe.so ./your_program

Simulates a failure every 3rd call.

*/

static int	pipe_count = 0;

int	pipe(int pipefd[2])
{
	pipe_count++;
	if (pipe_count % 3 == 0)
	{
		errno = EMFILE;	// Simulate too many open files
		return (-1);
	}

	// Call the original pipe
	int (*original_pipe)(int[2]);
	original_pipe = dlsym(RTLD_NEXT, "pipe");
	return (original_pipe(pipefd));
}
