CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall -Wextra -std=c11
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17

SRC_C = src/main.c src/file_handler.c src/normal_mode.c src/challenge_mode.c src/scoreboard.c
SRC_CPP = src/practice_mode.cpp
OBJ = $(SRC_C:.c=.o) $(SRC_CPP:.cpp=.o)

typing-speed-tester: $(OBJ)
	$(CXX) $(OBJ) -o $@   # use g++ to link C + C++ together

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o typing-speed-tester
