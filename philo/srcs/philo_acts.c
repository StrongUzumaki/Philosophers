#include "../includes/philo.h"

void	phil_eat(t_phil *phil)
{
	pthread_mutex_lock(phil->args->deathlock);
	phil->time_of_death = gettimeinms() + phil->args->time_to_die;
	pthread_mutex_unlock(phil->args->deathlock);
	pthread_mutex_lock(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is eating\n", timestamp(phil), phil->name);
	pthread_mutex_unlock(phil->args->output);
	if (phil->nbr_of_times_to_eat > 0 && phil->args->sym_on != 0)
	{	
		accurate_usleep(phil->args->time_to_eat);
		phil->nbr_of_times_to_eat--;
		if (phil->nbr_of_times_to_eat == 0 && phil->args->sym_on != 0)
		{
			pthread_mutex_lock(phil->args->deathlock);
			phil->args->sym_on -= 1;
			pthread_mutex_unlock(phil->args->deathlock);
		}
		return ;
	}
	if (phil->args->sym_on != 0)
		accurate_usleep(phil->args->time_to_eat);
}

void	phil_sleep(t_phil *phil)
{
	pthread_mutex_lock(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is sleeping\n", timestamp(phil), phil->name);
	pthread_mutex_unlock(phil->args->output);
	if (phil->args->sym_on != 0)
		accurate_usleep(phil->args->time_to_sleep);
}

void	phil_think(t_phil *phil)
{
	pthread_mutex_lock(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is thinking\n", timestamp(phil), phil->name);
	pthread_mutex_unlock(phil->args->output);
}

void	phil_die(t_phil *phil)
{
	if (phil->args->sym_on == 0)
		return ;
	pthread_mutex_lock(phil->args->output);
	printf("%d %d died\n", timestamp(phil), phil->name);
	pthread_mutex_unlock(phil->args->output);
	pthread_mutex_lock(phil->args->deathlock);
	phil->args->sym_on = 0;
	pthread_mutex_unlock(phil->args->deathlock);
}

void	phil_took_fork(t_phil *phil)
{
	pthread_mutex_lock(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d has taken a fork\n", timestamp(phil), phil->name);
	pthread_mutex_unlock(phil->args->output);
}
