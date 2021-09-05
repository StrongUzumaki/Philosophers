#include "../includes/philo.h"

void	*phil_life_cycle(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (phil->args->sym_on != 0)
	{
		sem_wait(phil->args->take_two);
		phil_take_fork(phil);
		phil_take_fork(phil);
		sem_post(phil->args->take_two);
		phil_eat(phil);
		sem_post(phil->args->forks);
		sem_post(phil->args->forks);
		if (phil->args->nbr_of_times_to_eat == 0)
		{
			sem_wait(phil->args->deathsem);
			phil->args->sym_on = 0;
			sem_post(phil->args->deathsem);
			return (NULL);
		}
		phil_sleep(phil);
		phil_think(phil);
		usleep(50);
	}
	return (NULL);
}

void	init_one_phil(t_phil *phil, t_args *args)
{
	phil->args = args;
	phil->time_of_death = gettimeinms() + args->time_to_die;
	phil->name = args->cur_phil + 1;
	pthread_create(&phil->thread, NULL, &phil_life_cycle, phil);
}

int	join_phils_threads(t_phil *phil)
{
	return (pthread_join(phil->thread, NULL));
}

int	check_phil_is_dead(t_phil *phil)
{
	int	res;

	sem_wait(phil->args->deathsem);
	res = phil->time_of_death < gettimeinms();
	sem_post(phil->args->deathsem);
	return (res);
}

void	phil_process(t_args	*args)
{
	t_phil	phil;

	init_one_phil(&phil, args);
	while (phil.args->sym_on != 0)
	{
		if (check_phil_is_dead(&phil))
		{	
			phil_die(&phil);
			exit(0);
		}
	}
	pthread_join(phil.thread, NULL);
	exit(FULL);
}
