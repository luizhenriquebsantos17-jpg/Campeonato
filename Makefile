CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c time.c bd_times.c partida.c bd_partidas.c csv_utils.c
OBJS = $(SRCS:.c=.o)
TARGET = campeonato

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
