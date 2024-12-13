/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_pthread_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 06:26:10 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/13 06:40:19 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

/*

Compile override as a shared library:
gcc -shared -fPIC -o libfailpthread.so fail_pthread.c -ldl

Preload the library and run your program:
LD_PRELOAD=./libfailpthread.so ./your_program

Simulates a failure after a certain number of successful thread creations.
*/

static int	thread_count = 0;
static int	fail_after = 2;

int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
	thread_count++;
	if (thread_count > fail_after)
	{
		return (EAGAIN); // Simulate thread limit reached
	}

	// Call the original pthread_create
	int (*original_pthread_create)(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);
	original_pthread_create = dlsym(RTLD_NEXT, "pthread_create");
	return (original_pthread_create(thread, attr, start_routine, arg));
}
