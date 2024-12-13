/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:29:27 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:36:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfaildup2.so fail_dup2.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfaildup2.so ./your_program

Simulates a failure when duplicating a file descriptor.

*/

int	dup2(int oldfd, int newfd)
{
	if (oldfd == 0)
	{ // Fail for stdin duplication as an example
		errno = EBADF; // Simulate bad file descriptor
		return (-1);
	}

	// Call the original dup2
	int (*original_dup2)(int, int);
	original_dup2 = dlsym(RTLD_NEXT, "dup2");
	return (original_dup2(oldfd, newfd));
}
