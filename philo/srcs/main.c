#include "../includes/philo.h"

int	check_args(t_args *args)
{
	if (args->nbr_of_phils <= 0)
		return (0);
	if (args->time_to_die <= 0)
		return (0);
	if (args->time_to_eat <= 0)
		return (0);
	if (args->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	safe_allocs(t_args *args)
{
	args->output = malloc(sizeof(pthread_mutex_t));
	args->deathlock = malloc(sizeof(pthread_mutex_t));
	args->forks = malloc(sizeof(pthread_mutex_t) * (args->nbr_of_phils));
	if (args->output == NULL || args->deathlock == NULL
		|| args->forks == NULL)
	{
		if (args->output != NULL)
			free(args->output);
		if (args->deathlock != NULL)
			free(args->deathlock);
		if (args->forks != NULL)
			free(args->forks);
		return (-1);
	}
	return (1);
}

int	init_args(int argc, char *argv[], t_args *args)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	if (safe_allocs(args) == -1)
		return (-1);
	args->start_of_sim = gettimeinms();
	args->nbr_of_phils = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->sym_on = args->nbr_of_phils;
	pthread_mutex_init(args->output, NULL);
	pthread_mutex_init(args->deathlock, NULL);
	i = -1;
	while (++i < args->nbr_of_phils)
		pthread_mutex_init(&args->forks[i], NULL);
	if (argc == 6)
		args->nbr_of_times_to_eat = ft_atoi(argv[5]);
	else
		args->nbr_of_times_to_eat = -1;
	return (check_args(args));
}

void	free_all(t_args *args, t_phil *phils)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(args->output);
	pthread_mutex_destroy(args->deathlock);
	while (++i < args->nbr_of_phils)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(args->output);
		pthread_mutex_destroy(args->deathlock);
	}
	free(args->output);
	free(args->deathlock);
	free(args->forks);
	free(phils);
}

int	main(int argc, char *argv[])
{
	t_phil	*phils;
	t_args	args;

	phils = NULL;
	if (!init_args(argc, argv, &args))
	{
		printf("args not valid\n");
		return (1);
	}
	if (!init_phils(phils, &args))
	{
		printf("phils init error\n");
		return (1);
	}
	return (0);
}
