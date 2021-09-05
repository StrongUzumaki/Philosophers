#include "../includes/philo.h"

int	timestamp(t_phil *phil)
{
	return (gettimeinms() - phil->args->start_of_sim);
}

int	gettimeinms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	accurate_usleep(unsigned long int time)
{
	int	res;

	res = gettimeinms() + time;
	while (gettimeinms() < res)
	{
		usleep(100);
	}
}

int	check_args(t_args *args)
{
	if (args->nbr_of_phils < 0)
		return (0);
	if (args->time_to_die < 0)
		return (0);
	if (args->time_to_eat < 0)
		return (0);
	if (args->time_to_sleep < 0)
		return (0);
	return (1);
}

void	unlink_all(void)
{
	sem_unlink("deathsem");
	sem_unlink("forks");
	sem_unlink("take_two");
	sem_unlink("output");
}
