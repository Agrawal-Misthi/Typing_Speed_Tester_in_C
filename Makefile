CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11   # Added some common warnings and set C standard

SRC = src/main.c src/file_handler.c src/practice_mode.c src/normal_mode.c src/challenge_mode.c src/scoreboard.c
OBJ = $(SRC:.c=.o)

typing-speed-tester: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o typing-speed-tester