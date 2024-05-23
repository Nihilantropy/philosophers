NAME		= philo

PHILO_DIR	= ./srcs
PHILO_HEAD	= ./include

SRCS		= main.c main_utils.c checks.c checks_utils.c init_table.c create_list.c create_list_utils.c routine_philo.c routine_observer.c \
				routine_observer_utils.c routine_actions.c routine_actions_utils.c

OBJS		= $(patsubst %.c, $(PHILO_DIR)/%.o, $(SRCS))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread -g #-fsanitize=thread
RM = rm -f

# Include directory for header files
INC 		= -I$(PHILO_HEAD)

# Compilation rule for the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


# Rule to compile object files
$(PHILO_DIR)/%.o: $(PHILO_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@


all:		$(NAME)

clean:
			$(RM) $(OBJS)


fclean:		clean
			$(RM) $(NAME)

re:			fclean all

rec:		clean all

test:
			./$(NAME) 2 800 200 200 5


.PHONY:		all clean fclean re rec test