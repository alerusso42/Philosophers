NAME = philo
OBJ_DIR = obj_dir
SRC = 	main.c \
		error_message.c \
		manage_data/init_thread.c \
		manage_data/memory.c \
		manage_data/parsing.c \
		utils/debug.c \
		utils/ft_atoi.c \
		utils/ft_calloc.c \
		utils/printf_light.c \
		utils/printf_fd.c \
		utils/time.c \
		routine/eat.c \
		routine/death.c \
		routine/monitor.c \
		routine/print.c  \
		routine/routine.c \

OBJ    = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
COMP = cc -Wall -Wextra -Werror
LFLAGS = -lpthread


$(NAME) : $(OBJ) $(OBJ_DIR)
	$(COMP) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "\n$(NAME) done!!"

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(COMP) -c $< -o $@

$(OBJ_DIR):
	mkdir -p ${OBJ_DIR}/debug
	mkdir -p ${OBJ_DIR}/manage_data
	mkdir -p ${OBJ_DIR}/routine
	mkdir -p ${OBJ_DIR}/utils

clean: 
	@rm -f $(OBJ) $(ALL) $(NAME_BONUS) *.out *.gdb  *.supp *.txt *.sh
	@rm -rf $(OBJ_DIR)

clear: 
	clear

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

debug: 
	$(shell cd debug && make debug)

.PHONY: all clean fclean re bonus debug supp
