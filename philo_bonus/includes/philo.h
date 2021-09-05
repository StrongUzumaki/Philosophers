#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# define FULL 1

typedef struct s_args
{
	int		start_of_sim;
	int		nbr_of_phils;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		nbr_of_times_to_eat;
	int		cur_phil;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*take_two;
	sem_t	*deathsem;
	int		sym_on;
}				t_args;

typedef struct s_phil
{
	pthread_t	thread;
	t_args		*args;
	int			time_of_death;
	int			name;
}				t_phil;

int		timestamp(t_phil *phil);
void	unlink_all(void);
int		check_args(t_args *args);
void	phil_process(t_args	*args);
int		check_phil(t_phil *phil);
int		join_phils_threads(t_phil *phil);
void	init_one_phil(t_phil *phil, t_args *args);
void	*phil_life_cycle(void *arg);
void	phil_take_fork(t_phil *phil);
void	phil_die(t_phil *phil);
void	phil_think(t_phil *phil);
void	phil_sleep(t_phil *phil);
void	phil_eat(t_phil *phil);
void	accurate_usleep(unsigned long int time);
int		gettimeinms(void);
int		ft_atoi(const char *ptr);
#endif
