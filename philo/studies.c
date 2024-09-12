#include "philo.h"

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int index;

	index = *(int *)arg;
	printf("prime %d: %d\n", index, primes[index]);
	free(arg);
}

int main(int argc, char **argv)
{
	int i; // local variable to the main function
	int *a;
	pthread_t th[10];

	i = 0;
	while (i < 10)
	{
		a = (int *)malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return (printf("treta 1\n"), 1);
		i++;
		//printf("index: %d\n", *a);
	}
	i = 0;
	while (i < 10)
	{
		//sleep(1);
		if (pthread_join(th[i], NULL) != 0)
			return (printf("treta 2\n"), 1);
	}
	return (0);
}

//------------------------------------//

/* pthread_mutex_t	mutex; // cannot use global variables -> use structs
int	mails = 0;

void *routine()
{
	int	i;
	//int	mails;

	i = 0;
	//mails = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int argc, char **argv)
{
	//pthread_mutex_t	mutex;
	pthread_t		*th;
	int				i;

	th = (pthread_t *)malloc(sizeof(pthread_t) * 4);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		i++;
		printf("thread %d has started\n", i);
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
		printf("thread %d has joined\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Mails: %d\n", mails);
	return (0);
} */

//------------------------------------//

/* int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL); //wait function for threads
	pthread_join(t2, NULL);
	return (0);
} */
