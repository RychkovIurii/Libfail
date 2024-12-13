/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:13:52 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:35:08 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailopen.so fail_open.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailopen.so ./your_program

Simulates open always failing for a specific file.

*/

int	open(const char *pathname, int flags, ...)
{
	if (strstr(pathname, "forbidden_file"))
	{
		errno = EACCES;	// Simulate access denied
		return (-1);
	}

	// Call the original open function
	int (*original_open)(const char *, int, ...);
	original_open = dlsym(RTLD_NEXT, "open");
	return (original_open(pathname, flags));
}
