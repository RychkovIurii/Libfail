/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:07:32 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:28:29 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailwrite.so fail_write.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailwrite.so ./your_program

Simulates a failure after a certain number of writes.
*/

static int	write_count = 0;
static int	fail_after = 3;

ssize_t	write(int fd, const void *buf, size_t count)
{
	write_count++;
	if (write_count > fail_after)
	{
		errno = EIO;	// Simulate an I/O error
		return (-1);	// Indicate failure
	}

	// Call the original write function
	ssize_t (*original_write)(int, const void *, size_t);
	original_write = dlsym(RTLD_NEXT, "write");
	return (original_write(fd, buf, count));
}
