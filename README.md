# Typing Speed Tester (C Project)

**A console-based C program to improve typing speed, accuracy, and consistency through interactive practice and challenge modes.**

---

## Project Overview

The Typing Speed Tester allows users to practice typing in three modes:

- **Practice Mode:** Educational mode for learning specific words, phrases, and sentences. No time limit, designed for repeated practice to maximize accuracy. Users can now choose to quit mid-session if desired.  
- **Normal Mode:** Timed levels with lifelines. Difficulty increases progressively (words → phrases → sentences). Users gain extra seconds per level.  
- **Challenge Mode:** Accuracy-focused mode under time pressure. Ends immediately after the first mistake, ideal for advanced users.  

Scores are permanently stored in `scoreboard.txt`, and each mode loads data from files in the `data/` folder.

---

## Features

- **Practice Mode**
  - Sequential practice to improve accuracy.
  - Supports saving and loading custom practice text.
  - Users can quit the session at any point.

- **Normal Mode**
  - Randomized selection of words/phrases for unpredictability.
  - Timed levels with lifelines.
  - Timer adds 10 seconds per level.

- **Challenge Mode**
  - High-difficulty typing.
  - Ends immediately on the first mistake.

- **Scoreboard**
  - Tracks username, time taken, levels completed, and words per minute (WPM).
  - Saved permanently in `scoreboard.txt`.

---

## Project Structure

Typing_Speed_Tester_in_C/
│
├─ src/
│ ├─ main.c               # Displays menu and calls different modes
│ ├─ file_handler.c       # Implements file save/load functions
│ ├─ practice_mode.c      # Logic for practice mode
│ ├─ normal_mode.c        # Logic for normal mode (levels, timer, lifelines)
│ ├─ challenge_mode.c     # Logic for challenge mode (accuracy focus)
│ └─ scoreboard.c         # Handles saving scores to scoreboard.txt
│
├─ include/
│ ├─ file_handler.h       # Function declarations for file operations
│ ├─ modes.h              # Function declarations for different modes
│ └─ scoreboard.h         # Function declarations for scoreboard operations
│
├─ data/
│ ├─ practice_data.txt    # Pre-selected text for practice mode
│ ├─ default_data.txt     # Word/phrase data for normal mode
│ └─ hard_data.txt        # Word/phrase/sentence data for challenge mode
│
├─ Makefile               # Build configuration and compilation instructions
├─ README.md              # Project documentation
└─ scoreboard.txt         # Stores game scores permanently

Each folder and file is organized to separate **logic, headers, and data**, making the project modular and easy to extend.

---

## Quick Start

**Clone the repository:**

```bash
git clone https://github.com/yourusername/Typing_Speed_Tester_in_C.git
cd Typing_Speed_Tester_in_C