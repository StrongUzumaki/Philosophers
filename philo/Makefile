CC		:= gcc 
CFLAGS		:=  -Wall -Wextra -Werror -pthread	
NAME		:=	philo
OBJS		:=	srcs/main.o \
				srcs/ft_atoi.o \
				srcs/philo_acts.o	\
				srcs/phil_utils.o	\
				srcs/threads_utils.o

deps 		:= $(patsubst %.o,%.d,$(OBJS))

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
-include $(deps)

DEPSFLAGS 	= -MMD -MF $(@:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(DEPSFLAGS) -o $(<:.c=.o)

clean:
	rm -f $(OBJS) $(deps)
	

fclean: clean 
	rm -f $(NAME)

re: fclean all

