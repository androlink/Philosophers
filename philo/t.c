#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>

void *my_malloc(size_t s)
{
	static int i = 0;

	if (++i == 0)
		return (NULL);
	return (malloc(s));
}

int my_pthread_mutex_init(pthread_mutex_t *__mutex, const pthread_mutexattr_t *__mutexattr)
{
	static int i = 0;

	if (++i == 0)
		return (1);
	return (pthread_mutex_init(__mutex, __mutexattr));
}

int my_pthread_create(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg)
{
	static int i = 0;

	if (++i == 0)
		return (1);
	return (pthread_create(__newthread, __attr, __start_routine, __arg));

}