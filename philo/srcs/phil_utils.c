#include "../includes/philo.h"

void	*pfil_even_case(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (phil->args->sym_on != 0 && phil->args->nbr_of_times_to_eat != 0)
	{
		if (phil->right_fork != phil->left_fork)
		{
			pthread_mutex_lock(phil->right_fork);
			phil_took_fork(phil);
			pthread_mutex_lock(phil->left_fork);
			phil_took_fork(phil);
			phil_eat(phil);
			pthread_mutex_unlock(phil->right_fork);
			pthread_mutex_unlock(phil->left_fork);
		}
		phil_sleep(phil);
		phil_think(phil);
		usleep(50);
	}
	return (NULL);
}

void	*pfil_odd_case(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (phil->args->sym_on != 0 && phil->args->nbr_of_times_to_eat != 0)
	{
		if (phil->right_fork != phil->left_fork)
		{
			pthread_mutex_lock(phil->left_fork);
			phil_took_fork(phil);
			pthread_mutex_lock(phil->right_fork);
			phil_took_fork(phil);
			phil_eat(phil);
			pthread_mutex_unlock(phil->left_fork);
			pthread_mutex_unlock(phil->right_fork);
		}	
		phil_sleep(phil);
		phil_think(phil);
		usleep(50);
	}
	return (NULL);
}

void	init_one_phil(t_phil *phil, int phil_num, t_args *args)
{
	phil->args = args;
	phil->left_fork = &args->forks[phil_num];
	phil->name = phil_num + 1;
	phil->time_of_death = gettimeinms() + args->time_to_die;
	phil->nbr_of_times_to_eat = args->nbr_of_times_to_eat;
	if (phil_num < args->nbr_of_phils - 1)
		phil->right_fork = &args->forks[phil_num + 1];
	else
		phil->right_fork = &args->forks[0];
	if (!(phil_num % 2))
		pthread_create(&phil->thread, NULL, &pfil_odd_case, phil);
	else
		pthread_create(&phil->thread, NULL, &pfil_even_case, phil);
}

int	check_phil(t_phil *phil)
{
	int	res;

	pthread_mutex_lock(phil->args->deathlock);
	res = phil->time_of_death < gettimeinms();
	pthread_mutex_unlock(phil->args->deathlock);
	return (!res);
}

int	init_phils(t_phil *phils, t_args *args)
{
	int	i;

	i = -1;
	phils = malloc(sizeof(t_phil) * (args->nbr_of_phils));
	if (phils == NULL)
		return (-1);
	i = -1;
	while (++i < args->nbr_of_phils)
		init_one_phil(&phils[i], i, args);
	i = -1;
	while (++i < args->nbr_of_phils)
		if (join_phils_threads(&phils[i]) != 0)
			return (0);
	args->start_of_sim = gettimeinms();
	main_cycle(phils, args->nbr_of_phils);
	usleep(args->time_to_die * 2);
	free_all(args, phils);
	return (1);
}	
