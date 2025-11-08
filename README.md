# Typing Speed Tester (C Project)

**A console and web-based C program to improve typing speed, accuracy, and consistency through interactive practice, normal, and challenge modes.**

## Project Overview
    The Typing Speed Tester provides three distinct modes for improving typing skills:

**Practice Mode:** 
    Educational mode for learning specific words, phrases, and sentences.
    No time limit. 
    Users can quit mid-session or save custom practice text.

**Normal Mode:** 
    Timed levels with lifelines. Difficulty increases progressively (words → phrases → sentences). 
    Users gain extra seconds per correct entry.

**Challenge Mode:** 
    High-pressure accuracy mode. Ends immediately after the first mistake, ideal for advanced users.
    Scores are permanently stored in `scoreboard.txt`, and each mode loads data from text files in the `data/` folder.

## Features
  - **Practice Mode**
    - Sequential practice for accuracy improvement.
    - Supports saving/loading custom practice text.
    - Users can quit the session anytime.

  - **Normal Mode**
    - Randomized word/phrase selection for unpredictability.
    - Timed levels with lifelines.
    - Timer rewards extra seconds per correct entry.
    - Web interface supported via CGI.

  - **Challenge Mode**
    - Accuracy-focused, high-difficulty typing.
    - Ends on the first mistake.
  
  - **Scoreboard**
    - Tracks username, levels completed, time taken, words per minute (WPM), and accuracy.
    - Scores are permanently saved in scoreboard.txt.
    - Separate scoreboard views for each mode.
  
  
  ## Project Structure
  
  Typing_Speed_Tester_in_C/
  │
  ├─ src/                    # C source code
  │ ├─ main.c                # Displays menu and calls different modes
  │ ├─ file_handler.c        # Implements file save/load functions
  │ ├─ practice_mode.c       # Logic for practice mode
  │ ├─ normal_mode.c         # Logic for normal mode (timer, levels, lifelines)
  │ ├─ challenge_mode.c      # Logic for challenge mode (accuracy-focused)
  │ └─ scoreboard.c          # Handles saving and displaying scores
  │
  ├─ include/                # Header files
  │ ├─ file_handler.h        # File operation declarations
  │ ├─ modes.h               # Mode function declarations
  │ └─ scoreboard.h          # Scoreboard function declarations
  │
  ├─ data/                   # Data files for the typing tests
  │ ├─ practice_data.txt     # Pre-selected text for practice mode
  │ ├─ default_data.txt      # Word/phrase data for normal mode
  │ └─ hard_data.txt         # Word/phrase/sentence data for challenge mode
  │
  ├─ web/                    # Web interface files
  │ ├─ index.html            # Home page with links to all modes
  │ ├─ practice.html         # Web interface for practice mode
  │ ├─ normal.html           # Web interface for normal mode
  │ ├─ challenge.html        # Web interface for challenge mode
  │ ├─ scoreboard.html       # View scoreboard
  │ └─ cgi-bin/              # Folder for actual CGI scripts
  │     └─ web_interface.c   # Handles CGI requests for web-based Normal Mode
  │
  ├─ Makefile                # Build configuration and compilation instructions
  ├─ README.md               # Project documentation
  └─ scoreboard.txt          # Stores game scores permanently