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
		usleep(100);
}

int	join_phils_threads(t_phil *phil)
{
	return (pthread_detach(phil->thread));
}

void	main_cycle(t_phil *phils, unsigned long int nbr_of_phils)
{
	unsigned long int	i;

	usleep(50);
	while (1)
	{
		i = 0;
		while (i < nbr_of_phils)
		{
			if (phils[i].args->sym_on == 0)
				return ;
			if (check_phil(&phils[i]) == 0 && phils[i].args->sym_on != 0
				&& phils[i].nbr_of_times_to_eat != 0)
			{	
				phil_die(&phils[i]);
				return ;
			}
			i++;
		}
	}
}
