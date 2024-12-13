/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_waitpid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:31:52 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:39:53 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailwaitpid.so fail_waitpid.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailwaitpid.so ./your_program

Simulates failure for a specific executable.

*/

pid_t	waitpid(pid_t pid, int *status, int options)
{
	if (pid == 1234)
	{ // Simulate failure for a specific PID
		errno = ECHILD; // Simulate no child processes
		return (-1);
	}

	// Call the original waitpid
	pid_t (*original_waitpid)(pid_t, int *, int);
	original_waitpid = dlsym(RTLD_NEXT, "waitpid");
	return (original_waitpid(pid, status, options));
}
