 # Nombre del ejecutable
TARGET = game

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
LDFLAGS = -lncurses   # <-- aquí le decimos que use ncurses

# Fuentes y objetos
SRCS = src/ball.c src/player.c src/game.c main.c
OBJS = $(SRCS:.c=.o)

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Regla para compilar los .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar objetos y ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

# Limpiar todo incluyendo archivos antiguos (opcional)
cleanall: clean
	rm -f src/a.out

# Phony targets
.PHONY: all clean cleanall
 
