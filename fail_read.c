/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:11:44 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:34:59 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailread.so fail_read.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailread.so ./your_program

Simulates a failure after a certain number of reads.

*/

static int	read_count = 0;
static int	fail_after = 3;

ssize_t	read(int fd, void *buf, size_t count)
{
	read_count++;
	if (read_count > fail_after)
	{
		errno = EIO;	// Simulate an I/O error
		return (-1);	// Indicate failure
	}

	// Call the original read function
	ssize_t (*original_read)(int, void *, size_t);
	original_read = dlsym(RTLD_NEXT, "read");
	return (original_read(fd, buf, count));
}
