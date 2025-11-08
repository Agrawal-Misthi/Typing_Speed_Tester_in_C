# =======================
# Compiler & Flags
# =======================
CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall -Wextra -std=c11
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17

# =======================
# Desktop build sources
# =======================
SRC_C = src/main.c src/file_handler.c src/normal_mode.c src/challenge_mode.c src/scoreboard.c
SRC_CPP = src/practice_mode.cpp
OBJ = $(SRC_C:.c=.o) $(SRC_CPP:.cpp=.o)

# =======================
# ===== Desktop Build =====
# =======================
typing-speed-tester: $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================
# ===== Clean Build =====
# =======================
clean:
	rm -f src/*.o typing-speed-tester web/cgi-bin/web_interface.cgi web/cgi-bin/*.o

# =======================
# ===== Build CGI Web Interface =====
# =======================
WEB_OUTPUT = web/cgi-bin/web_interface.cgi

cgi:
	# Step 2: Compile C files as C
	$(CC) $(CFLAGS) -c web/cgi-bin/web_interface.c -o web/cgi-bin/web_interface.o
	$(CC) $(CFLAGS) -c src/file_handler.c -o src/file_handler.o
	$(CC) $(CFLAGS) -c src/normal_mode.c -o src/normal_mode.o
	$(CC) $(CFLAGS) -c src/challenge_mode.c -o src/challenge_mode.o
	$(CC) $(CFLAGS) -c src/scoreboard.c -o src/scoreboard.o

	# Step 3: Compile C++ files as C++
	$(CXX) $(CXXFLAGS) -c src/practice_mode.cpp -o src/practice_mode.o

	# Step 4: Link everything with g++
	$(CXX) $(CXXFLAGS) \
	    web/cgi-bin/web_interface.o \
	    src/file_handler.o \
	    src/normal_mode.o \
	    src/challenge_mode.o \
	    src/scoreboard.o \
	    src/practice_mode.o \
	    -o $(WEB_OUTPUT)

	# Make executable
	chmod +x $(WEB_OUTPUT)