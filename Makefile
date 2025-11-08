CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall -Wextra -std=c11
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17

SRC_C = src/main.c src/file_handler.c src/normal_mode.c src/challenge_mode.c src/scoreboard.c
SRC_CPP = src/practice_mode.cpp
OBJ = $(SRC_C:.c=.o) $(SRC_CPP:.cpp=.o)

# ===== Normal desktop build =====
typing-speed-tester: $(OBJ)
	$(CXX) $(OBJ) -o $@   # use g++ to link C + C++ together

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o typing-speed-tester web/cgi-bin/web_interface.cgi


# ===== New: Build CGI Web Interface =====
WEB_SRC = web/cgi-bin/web_interface.c \
          src/file_handler.c \
          src/practice_mode.cpp \
          src/normal_mode.c \
          src/challenge_mode.c \
          src/scoreboard.c

WEB_OUTPUT = web/cgi-bin/web_interface.cgi

cgi:
	$(CXX) $(CXXFLAGS) -o $(WEB_OUTPUT) $(WEB_SRC)
	chmod +x $(WEB_OUTPUT)