#include "../includes/philo.h"

void	phil_eat(t_phil *phil)
{
	sem_wait(phil->args->deathsem);
	phil->time_of_death = gettimeinms() + phil->args->time_to_die;
	sem_post(phil->args->deathsem);
	sem_wait(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is eating\n", timestamp(phil), phil->name);
	sem_post(phil->args->output);
	if (phil->args->nbr_of_times_to_eat > 0 && phil->args->sym_on != 0)
	{	
		accurate_usleep(phil->args->time_to_eat);
		phil->args->nbr_of_times_to_eat--;
		if (phil->args->nbr_of_times_to_eat == 0 && phil->args->sym_on != 0)
		{
			sem_wait(phil->args->deathsem);
			phil->args->sym_on -= 1;
			sem_post(phil->args->deathsem);
		}
		return ;
	}
	if (phil->args->sym_on != 0)
		accurate_usleep(phil->args->time_to_eat);
}

void	phil_sleep(t_phil *phil)
{
	sem_wait(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is sleeping\n", timestamp(phil), phil->name);
	sem_post(phil->args->output);
	if (phil->args->sym_on != 0)
		accurate_usleep(phil->args->time_to_sleep);
}

void	phil_think(t_phil *phil)
{
	sem_wait(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d is thinking\n", timestamp(phil), phil->name);
	sem_post(phil->args->output);
}

void	phil_die(t_phil *phil)
{
	if (phil->args->sym_on == 0)
		return ;
	sem_wait(phil->args->deathsem);
	phil->args->sym_on = 0;
	sem_wait(phil->args->output);
	printf("%d %d died\n", timestamp(phil), phil->name);
	sem_post(phil->args->deathsem);
}

void	phil_take_fork(t_phil *phil)
{
	sem_wait(phil->args->forks);
	sem_wait(phil->args->output);
	if (phil->args->sym_on != 0)
		printf("%d %d has taken a fork\n", timestamp(phil), phil->name);
	sem_post(phil->args->output);
}
