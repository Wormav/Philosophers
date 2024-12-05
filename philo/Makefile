# Nom du programme
NAME = philo

# Variables pour les commandes
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Fichiers sources et objets
SRCS = $(SRC_DIR)/main.c
OBJS = $(OBJ_DIR)/main.o

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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)$(BUILD_EMOJI)  Compilation en cours$(RESET)..."
	@sleep 0.5
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(SUCCESS_EMOJI) Compilation réussie : $(NAME)$(RESET)"

# Compilation des fichiers objets
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	@echo "$(YELLOW)$(BUILD_EMOJI)  Compilation : $<$(RESET)"
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
