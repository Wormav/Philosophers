# Nom du programme
NAME = philo

# Variables pour les commandes
CC = cc

CFLAGS = -Wall -Wextra -Werror

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Fichiers sources
SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/utils_2.c \
		$(SRC_DIR)/utils/time.c \
		$(SRC_DIR)/parsing/overflow.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/valid_arg.c \
		$(SRC_DIR)/philos/philos_gestion.c \
		$(SRC_DIR)/philos/routine.c \
		$(SRC_DIR)/philos/routine_utils.c \
		$(SRC_DIR)/philos/print_action.c \
		$(SRC_DIR)/sim/sim_init.c \
		$(SRC_DIR)/memory/free.c

# Génération automatique des fichiers objets
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Couleurs et emojis pour le terminal
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
RESET = \033[0m

SUCCESS_EMOJI = ✅
CLEAN_EMOJI = 🗑️
BUILD_EMOJI = 🛠️

# Headers
HEADERS = $(INC_DIR)/philo.h

# Cible principale
all: $(OBJ_DIR) $(NAME)

# Création des répertoires nécessaires pour les objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/utils

# Compilation du binaire
$(NAME): $(OBJS)
	@echo "$(YELLOW)$(BUILD_EMOJI)  Compilation en cours$(RESET)..."
	@sleep 0.5
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(SUCCESS_EMOJI) Compilation réussie: $(NAME)$(RESET)"

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D) # Crée les sous-répertoires dans obj si nécessaire
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(CLEAN_EMOJI)  Fichiers objets supprimés$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(CLEAN_EMOJI)  $(NAME) supprimé$(RESET)"

# Reconstruction
re: fclean all

.PHONY: all clean fclean re
