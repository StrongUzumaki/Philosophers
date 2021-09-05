#include "../includes/philo.h"

int	init_args(int argc, char *argv[], t_args *args)
{
	if (argc < 5 || argc > 6)
		return (0);
	args->nbr_of_phils = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->sym_on = 1;
	args->cur_phil = 0;
	args->deathsem = sem_open("deathsem", O_CREAT, 0777, 1);
	args->forks = sem_open("forks", O_CREAT, 0777, args->nbr_of_phils);
	args->take_two = sem_open("take_two", O_CREAT, 0777, 1);
	args->output = sem_open("output", O_CREAT, 0777, 1);
	args->start_of_sim = gettimeinms();
	if (argc == 6)
		args->nbr_of_times_to_eat = ft_atoi(argv[5]);
	else
		args->nbr_of_times_to_eat = -1;
	return (check_args(args));
}

void	fork_all(pid_t *phil_pids, t_args *args)
{
	int	pid;

	args->start_of_sim = gettimeinms();
	while (args->cur_phil < args->nbr_of_phils)
	{
		pid = fork();
		if (pid == 0)
		{
			free(phil_pids);
			phil_process(args);
		}
		else
			phil_pids[args->cur_phil] = pid;
		args->cur_phil++;
	}
}

void	wait_all(pid_t *phil_pids, t_args *args)
{
	int	i;
	int	status;

	i = 0;
	while (i < args->nbr_of_phils)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != FULL)
		{
			i = -1;
			while (++i < args->nbr_of_phils)
				kill(phil_pids[i], SIGQUIT);
			sem_post(args->output);
			return ;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args	args;
	pid_t	*phil_pids;

	unlink_all();
	if (!init_args(argc, argv, &args))
	{
		printf("args not valid\n");
		return (1);
	}
	phil_pids = malloc(sizeof(pid_t) * args.nbr_of_phils);
	if (phil_pids == NULL)
	{
		printf("malloc error\n");
		return (1);
	}
	fork_all(phil_pids, &args);
	wait_all(phil_pids, &args);
	free(phil_pids);
	return (0);
}
