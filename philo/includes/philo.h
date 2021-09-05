#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef struct s_args
{
	int					start_of_sim;
	int					nbr_of_phils;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					nbr_of_times_to_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*deathlock;
	int					sym_on;
	pthread_mutex_t		*output;
}				t_args;

typedef struct s_phil
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_args				*args;
	int					time_of_death;
	int					nbr_of_times_to_eat;
	int					name;
}				t_phil;

void				free_all(t_args *args, t_phil *phils);
int					init_phils(t_phil *phils, t_args *args);
int					check_phil(t_phil *phil);
int					timestamp(t_phil *phil);
void				init_one_phil(t_phil *phil, int phil_num, t_args *args);
void				*pfil_odd_case(void *arg);
void				*pfil_even_case(void *arg);
void				main_cycle(t_phil *phils, unsigned long int nbr_of_phils);
int					join_phils_threads(t_phil *phil);
void				accurate_usleep(unsigned long int time);
void				phil_took_fork(t_phil *phil);
void				phil_die(t_phil *phil);
void				phil_think(t_phil *phil);
void				phil_sleep(t_phil *phil);
void				phil_eat(t_phil *phil);
void				accurate_usleep(unsigned long int time);
int					gettimeinms(void);
int					ft_atoi(const char *ptr);
#endif
