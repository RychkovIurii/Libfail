/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:30:12 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:37:13 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailexecve.so fail_execve.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailexecve.so ./your_program

Simulates failure for a specific executable.

*/

int	execve(const char *pathname, char *const argv[], char *const envp[])
{
	if (strstr(pathname, "forbidden_exec"))
	{
		errno = ENOENT; // Simulate file not found
		return (-1);
	}

	// Call the original execve
	int (*original_execve)(const char *, char *const[], char *const[]);
	original_execve = dlsym(RTLD_NEXT, "execve");
	return (original_execve(pathname, argv, envp));
}
