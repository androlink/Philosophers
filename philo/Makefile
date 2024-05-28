NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I . -g #-fsanitize=thread
LFLAGS = -l pthread 
DFLAGS = -MMD -MP

SFLIES :=	activities.c \
			check_val.c \
			destroy.c \
			fork.c \
			god.c \
			init.c \
			life.c \
			philo.c \
			quit.c \
			utils.c

DFILES = $(SFLIES:%.c=%.d)
OFILES = $(SFLIES:%.c=%.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) -o $@ $(CFLAGS) $(DFLAGS) $(OFILES) $(LFLAGS)

-include $(DFILES)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(DFLAGS)

clean:
	rm -f $(OFILES) $(DFILES)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) $(NAME)

.PHONY	:	all	fclean	clean	re
